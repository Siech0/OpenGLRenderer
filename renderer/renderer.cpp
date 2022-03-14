#include <renderer/renderer.hpp>

#include <iostream>
#include <vector>

#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include <renderer/core/obj_loader.hpp>
#include <renderer/core/tex_loader.hpp>
#include <renderer/core/shader_loader.hpp>

using namespace gfx::core;
using namespace gfx::gl;

namespace gfx
{
	Renderer::Renderer(int initial_width, int initial_height) 
	{
		// Setup viewport
		setViewport(initial_height, initial_height);

		// Setup shaders

		Shader vertex = shaderFromResource(Shader::Target::eVertex, "shaders/simple.vert");
		Shader fragment = shaderFromResource(Shader::Target::eFragment, "shaders/simple.frag");

		m_shader.attachShader(vertex);
		m_shader.attachShader(fragment);
		m_shader.link();
		m_shader.detachShader(vertex);
		m_shader.detachShader(fragment);
		m_shader.bind();

		// Setup Camera
		m_camera.setPosition(glm::vec3(0.0f, 0.0f, -5.0f));
		m_camera.lookAt(glm::vec3(0.0f, 0.0f, 0.0f));
		m_camera.setNear(0.1f);
		m_camera.setFar(100.0f);
		m_camera.setFov(glm::radians(60.0f));

		// Context setup
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glEnable(GL_CULL_FACE);
		glClearColor(0.15f, 0.15f, 0.15f, 1.0f);


		// Geometry setup
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		gfx::core::objFromResource("models/cow.obj", vertices, indices);

		Buffer vbo;
		m_vao.bindVertexBuffer(vbo, 0, sizeof(Vertex));
		vbo.bufferData(vertices, Buffer::Usage::eStreamDraw);

		Buffer ibo;
		m_vao.bindElementBuffer(ibo);
		ibo.bufferData(indices, Buffer::Usage::eStreamDraw);
		m_vaoElements = indices.size();

		m_vao.enableAttributes<Vertex>({ Attribute::ePosition , Attribute::eTexCoords, Attribute::eNormal});
	}

	void Renderer::setViewport(int width, int height) noexcept
	{
		glViewport(0, 0, width, height);
		m_camera.setAspect((float)width / (float)height);
	}

	void Renderer::render(float view_width, float view_height)
	{

		m_shader.bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		const auto matrix_id = m_shader.getUniform("MVP");
		const auto view_matrix_id = m_shader.getUniform("V");
		const auto model_matrix_id = m_shader.getUniform("M");
		const auto light_position_id = m_shader.getUniform("LightPosition_worldspace");
		const auto light_color_id = m_shader.getUniform("LightColor");
		const auto light_power_id = m_shader.getUniform("LightPower");
		const auto alpha_id = m_shader.getUniform("Alpha");
	
		glm::mat4 view_matrix = m_camera.viewMatrix();
		glm::mat4 perspective_matrix = m_camera.projectionMatrix();
		glm::mat4 translation = glm::mat4(1.0f);
		glm::mat4 rotation = glm::mat4(1.0f);
		glm::mat4 scale = glm::mat4(1.0f);
		glm::mat4 model_matrix = translation * scale * rotation;   
		glm::mat4 MVP = perspective_matrix * view_matrix * model_matrix;

		glUniformMatrix4fv(matrix_id, 1, GL_FALSE, glm::value_ptr(MVP));
		glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, glm::value_ptr(view_matrix));	
		glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, glm::value_ptr(model_matrix));

		glUniform3f(light_position_id, m_lightPosition.x, m_lightPosition.y, m_lightPosition.z);
		glUniform3f(light_color_id, m_lightColor.x, m_lightColor.y, m_lightColor.z);
		glUniform1f(light_power_id, m_lightPower);
		glUniform1f(alpha_id, m_modelAlpha);

		m_vao.bind();
		glDrawElements(GL_TRIANGLES, m_vaoElements, GL_UNSIGNED_INT, 0);

	}

	PerspectiveCamera& Renderer::camera() noexcept
	{
		return m_camera;
	}

}