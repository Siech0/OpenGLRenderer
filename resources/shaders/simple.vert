#version 460 core

// Inputs
layout(location = 0) in vec3 VertexPosition_modelspace;
layout(location = 1) in vec2 VertexUV;
layout(location = 2) in vec3 VertexNormal_modelspace;

// Outputs
out vec2 UV;
out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;

// Uniforms
uniform mat4 MVP = mat4(1.0);
uniform mat4 M = mat4(1.0);
uniform mat4 V = mat4(1.0);
uniform vec3 LightPosition_worldspace = vec3(0.0, 3.0, 1.0);

void main()
{
	// Output position of the vertex in clipspace
	gl_Position = MVP * vec4(VertexPosition_modelspace, 1.0);

	// Position of the vertex in worldspace
	Position_worldspace = (M * vec4(VertexPosition_modelspace,1.0)).xyz;

	// Vector that goes from vertex to camera in cameraspace
	vec3 vertexPosition_cameraspace = ( V * M * vec4(VertexPosition_modelspace, 1.0)).xyz;
	EyeDirection_cameraspace = vec3(0.0, 0.0, 0.0) - vertexPosition_cameraspace;

	// Vector that goes from vertex to the light in cameraspace.
	vec3 LightPosition_cameraspace = (V * vec4(LightPosition_worldspace, 1.0)).xyz;
	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;

	// Normal of vertex in cameraspace
	Normal_cameraspace = ( V * M * vec4(VertexNormal_modelspace, 0.0)).xyz;


	// UV of the vertex
	UV = VertexUV;
}