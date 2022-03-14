#version 460 core

// Inputs
in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

// Outputs
out vec4 Color;

// Uniforms
uniform vec3 LightPosition_worldspace = vec3(0.0, 3.0, 1.0);
uniform vec3 LightColor = vec3(1.0, 1.0, 1.0);
uniform float LightPower = 0.5;
uniform float Alpha = 1.0;

void main()
{
    // Material properties
    vec3 material_diffuse_color = vec3(1.0, 0.0, 0.0);
    vec3 material_ambient_color = vec3(0.1, 0.1, 0.1) * material_diffuse_color;
    vec3 material_specular_color = vec3(0.3, 0.3, 0.3);

    // Distance to light
    float distance = length(LightPosition_worldspace - Position_worldspace);

    // Normal of the computed fragment in camera space.
    vec3 n = normalize(Normal_cameraspace);
    // Direction of the light (from the fragment to the light)
    vec3 l = normalize(LightDirection_cameraspace);
    // Cosine of the angle between the normal and the light direction
    float cos_theta = clamp( dot(n, l), 0.0, 1.0);

    // Eye vector (towards camera)
    vec3 E = normalize(EyeDirection_cameraspace);
    // Direction in which the fragment reflects the light
    vec3 R = reflect(-l, n);
    // cosine of the angle between the eye vector and reflect vector
    float cos_alpha = clamp( dot(E, R), 0.0, 1.0);

    Color.rgb =
        // Ambient : simulates indirect lighting
        material_ambient_color +
        // Diffuse : 'color' of the object
        material_diffuse_color * LightColor * LightPower * cos_theta / (distance * distance) +
        // Specular : reflecting highlight
        material_specular_color * LightColor * LightPower * pow(cos_alpha, 5) / (distance * distance);
    // Basic transparency
    Color.a = Alpha;

}