#pragma once

#include <vector>
#include <string>

#include <tsl/robin_map.h>

#include <renderer/gl/shader.hpp>

namespace gfx::gl
{

	class ShaderProgram
	{
	public:
		enum class TargetFlags
		{
			eVertex = GL_VERTEX_SHADER_BIT,
			eFragment = GL_FRAGMENT_SHADER_BIT,
			eGeometry = GL_GEOMETRY_SHADER_BIT,
			eTesselationCtrl = GL_TESS_CONTROL_SHADER_BIT,
			eTesselationEval = GL_TESS_EVALUATION_SHADER_BIT,
			eCompute = GL_COMPUTE_SHADER_BIT
		};

		enum class Parameter
		{
			eBinaryRetrievable,
			eSeparable
		};

		ShaderProgram() noexcept;
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram(ShaderProgram&&) = default;

		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&&) = default;

		~ShaderProgram() noexcept;

		void attachShader(const Shader& shader) noexcept;
		void detachShader(const Shader& shader) noexcept;
		void link();

		void parameter(Parameter param, bool value) noexcept;


		int getUniform(const std::string& uniform_name) const;
		int getUniform(const char* uniform_name) const;

		void bind() const noexcept;
		void unbind() const noexcept;

		// Introspectiopn
		std::vector<std::string> getUniformNames() const;
		std::vector<std::string> getAttributeNames() const;

		// Getters
		TargetFlags flags() const noexcept;
		unsigned int id() const noexcept;

	private:
		tsl::robin_map<std::string, unsigned int> m_uniforms;
		TargetFlags m_flags;
		unsigned int m_id;
	};


	inline ShaderProgram::TargetFlags operator|(ShaderProgram::TargetFlags lhs, ShaderProgram::TargetFlags rhs)
	{
		return (ShaderProgram::TargetFlags)((GLenum)lhs | (GLenum)rhs);
	}

	inline ShaderProgram::TargetFlags operator|=(ShaderProgram::TargetFlags lhs, ShaderProgram::TargetFlags rhs)
	{
		lhs = (ShaderProgram::TargetFlags)((GLenum)lhs | (GLenum)rhs);
		return lhs;
	}

	inline ShaderProgram::TargetFlags operator&(ShaderProgram::TargetFlags lhs, ShaderProgram::TargetFlags rhs)
	{
		return (ShaderProgram::TargetFlags)((GLenum)lhs & (GLenum)rhs);
	}

	inline ShaderProgram::TargetFlags operator&=(ShaderProgram::TargetFlags& lhs, ShaderProgram::TargetFlags rhs)
	{
		lhs = (ShaderProgram::TargetFlags)((GLenum)lhs & (GLenum)rhs);
		return lhs;
	}
}