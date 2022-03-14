#version 460 core

// Inputs 
in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_worldspace;

// Outputs
out vec4 FragColor;

// Uniforms
// Material
uniform vec3 Albedo;
uniform float Metallic;
uniform float Roughness;
uniform float AO;

// Lights
uniform samplerBuffer LightPositions_worldspace;	// Vec3
uniform samplerBuffer LightColors;					// Vec3

// Camera
uniform vec3 CameraPosition;

struct Light
{
	vec3 LightPosition_worldspace;
	vec3 LightColor;
	float LightPower;
};

const float PI = 3.14159265359;

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
	float a = roughness * roughness;
	float a2 = a * a;
	float NdotH = max(dot(N, H), 0.0);
	float NdotH2 = NdotH * NdotH;
	
	float nom = a2;
	float denom = (NdotH2 * (a2 - 1.0) + 1.0);
	denom = PI * denom * denom;

	return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
	float r = (roughness + 1.0);
	float k = (r * r) / 8.0;

	float nom = NdotV;
	float denom = NdotV * (1.0 - k) + k;

	return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
	float NdotV = max(dot(N, V), 0.0);
	float NdotL = max(dot(N, L), 0.0);
	float ggx2 = GeometrySchlickGGX(NdotV, roughness);
	float ggx1 = GeometrySchlickGGX(NdotL, roughness);
	return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
	return F0 + (1.0 - F0) - pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

void main()
{
	vec3 N = normalize(Normal_worldspace);
	vec3 V = normalize(CameraPosition - Position_worldspace);

	vec3 F0 = vec3(0.04);
	F0 = mix(F0, Albedo, Metallic);

	// Reflectance equation
	vec3 Lo = vec3(0.0);
	for(int i = 0; i < textureSize(LightPositions_worldspace); ++i)
	{
		vec3 light_position = texelFetch(LightPositions_worldspace, i).rgb;
		vec3 light_color = texelFetch(LightColors, i).rgb;

		vec3 L = normalize(light_position - Position_worldspace);
		vec3 H = normalize(V + L);
		float distance = length(L);
		float attenuation = 1.0 / (distance * distance);
		vec3 radiance = light_color * attenuation;

		// Cook-Torrance BRDF
		float NDF = DistributionGGX(N, H, Roughness);
		float G = GeometrySmith(N, V, L, Roughness);
		vec3 F = fresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);

		vec3 numerator = NDF * G * F;
		float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001; // 0.0001 to prevent divide by 0
		vec3 specular = numerator / denominator;

		// kS is equal to Fresnel
		vec3 kS = F;
		// for energy conservation, the diffuse and specular light can't 
		// be above 1.0 (unless the surface emits light) to preserive this 
		// relationship the diffuse component (kD) should equal 1.0 - kS.
		vec3 kD = vec3(1.0) -  kS;
		// multiply by kD by the inverse metalness such that only non-metals have
		// diffuse lighting, or a linear blend if partly metal (pure metals
		// have no diffuse  light).
		kD *= 1.0 - Metallic;

		// scale light by NdotL
		float NdotL = max(dot(N, L), 0.0);

		// add outgoing radiance to Lo
		Lo += (kD * Albedo / PI + specular) * radiance * NdotL;
	}
	
	// Ambient lighting 
	vec3 ambient = vec3(0.03) * Albedo * AO;
	vec3 color = ambient + Lo;

	// HDR tonemapping
	color = color / (color + vec3(1.0));
	// Gamma correct
	color = pow(color, vec3(1.0 / 2.2));
	FragColor = vec4(color, 1.0);
}