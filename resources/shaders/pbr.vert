#version 450 core

// Inputs
layout(location = 0) in vec3 Position_modelspace;
layout(location = 1) in vec3 VertexUV;
layout(location = 2) in vec3 Normal_modelspace;

// Outputs
out vec3 Position_worldspace;
out vec2 UV;
out vec3 Normal_worldspace;

// Uniforms
uniform mat4 MVP;
uniform mat4 M;

void main()
{
	UV = VertexUV;
	Position_worldspace = vec3(Model * vec4(Position_modelspace, 1.0));
	Normal_modelspace = mat3(Model) * Normal_modelspace;

	gl_Position = MVP * vec4(Position_modelspace, 1.0);
}