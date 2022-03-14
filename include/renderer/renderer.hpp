#pragma once

#include <renderer/core/camera.hpp>
#include <renderer/core/vertex.hpp>
#include <renderer/gl/vertex_array.hpp>
#include <renderer/gl/buffer.hpp>
#include <renderer/gl/shader.hpp>
#include <renderer/gl/shader_program.hpp>
#include <renderer/gl/texture.hpp>

namespace gfx
{
	class Renderer
	{
	public:
		Renderer(int initial_width, int initial_height);
		Renderer(const Renderer&) = delete;
		Renderer(Renderer&& other) = default;

		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&& other) = default;

		void setViewport(int width, int height) noexcept;

		gfx::core::PerspectiveCamera& camera() noexcept;


		void render(float view_width, float view_height);
		
		// Getters that completely break encapsulation
		glm::vec3& lightPosition() noexcept { return m_lightPosition; }
		glm::vec3& lightColor() noexcept { return m_lightColor; }
		float& lightPower() noexcept { return m_lightPower; }
		float& modelAlpha() noexcept { return m_modelAlpha; }

	private:

		gfx::core::PerspectiveCamera m_camera;
		gfx::gl::VertexArray m_vao;
		gfx::gl::ShaderProgram m_shader;
		unsigned int m_vaoElements;

		glm::vec3 m_lightPosition = glm::vec3(0.0f, 2.0f, 1.0f);
		glm::vec3 m_lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
		float m_lightPower = 0.50;

		float m_modelAlpha = 1.0f;
	};
}