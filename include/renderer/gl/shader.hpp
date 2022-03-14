#pragma once

#include <string>
#include <stdexcept>

#include <glad/glad.h>


namespace gfx::gl
{
	class Shader
	{
	public:
		enum class Target : GLenum
		{
			eVertex = GL_VERTEX_SHADER,
			eFragment = GL_FRAGMENT_SHADER,
			eGeometry = GL_GEOMETRY_SHADER,
			eTesselationCtrl = GL_TESS_CONTROL_SHADER,
			eTesselationEval = GL_TESS_EVALUATION_SHADER,
			eCompute = GL_COMPUTE_SHADER
		};


		Shader(Target target) noexcept;
		Shader(Target target, const std::string& data);
		Shader(const Shader&) = delete; // No copies.
		Shader(Shader&&) noexcept;

		~Shader();

		Shader& operator=(const Shader&) = delete;
		Shader& operator=(Shader&&) noexcept;

		// State
		void loadSource(const std::string& data);

		// Methods
		Target target() const noexcept;
		unsigned int id() const noexcept;

	private:
		Target m_target;
		unsigned int m_id;
	};
}