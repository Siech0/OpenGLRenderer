#include <renderer/gl/shader_program.hpp>

#include <iostream>

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace gfx::gl
{
	ShaderProgram::ShaderProgram() noexcept
	{
		m_id = glCreateProgram();
	}

	ShaderProgram::~ShaderProgram() noexcept
	{
		glDeleteProgram(m_id);
	}

	void ShaderProgram::attachShader(const Shader& shader) noexcept
	{
		glAttachShader(m_id, shader.id());
	}
	
	void ShaderProgram::detachShader(const Shader& shader) noexcept
	{
		glDetachShader(m_id, shader.id());
	}

	void ShaderProgram::link()
	{
		glLinkProgram(m_id);
#if !defined(NDEBUG) || defined(RENDERER_ENABLE_SHADER_PROGRAM_DEBUG)
		{
			int status, info_log_len;
			glGetProgramiv(m_id, GL_LINK_STATUS, &status);
			glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &info_log_len);
			if (!status)
			{
				if (info_log_len > 0)
				{
					std::string info_log;
					info_log.resize(info_log_len);
					glGetProgramInfoLog(m_id, info_log_len, nullptr, info_log.data());
					throw std::runtime_error(info_log);
				}
				else
				{
					throw std::runtime_error("unknown shader program link error");
				}
			}
		}
#endif
	}

	void ShaderProgram::parameter(ShaderProgram::Parameter param, bool value) noexcept
	{
		glProgramParameteri(m_id, (GLenum)param, value ? GL_TRUE : GL_FALSE);
	}

	int ShaderProgram::getUniform(const std::string& uniform_name) const
	{
		return getUniform(uniform_name.c_str());
	}

	int ShaderProgram::getUniform(const char* uniform_name) const
	{
		int val = glGetUniformLocation(m_id, uniform_name);
		if (val < 0)
			throw std::runtime_error(std::string("Unable to find uniform with name '") + uniform_name + "'");
		return val;
	}

	void ShaderProgram::bind() const noexcept
	{
		glUseProgram(m_id);
	}

	void ShaderProgram::unbind() const noexcept
	{
		glUseProgram(0);
	}

	std::vector<std::string> ShaderProgram::getUniformNames() const
	{
		int num_uniforms;
		std::vector<std::string> uniforms;
		glGetProgramiv(m_id, GL_ACTIVE_UNIFORMS, &num_uniforms);
		uniforms.reserve(num_uniforms);

		int max_name_len;
		glGetProgramiv(m_id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_name_len);
		std::string temp_name;
		temp_name.resize(max_name_len);

		for (int i = 0; i < num_uniforms; ++i)
		{
			int array_size;
			GLenum type;
			GLsizei actual_length;
			glGetActiveUniform(m_id, i, temp_name.size(), &actual_length, &array_size, &type, temp_name.data());

			uniforms.emplace_back(temp_name.data(), actual_length);
		}

		return uniforms;
	}

	std::vector<std::string> ShaderProgram::getAttributeNames() const
	{
		int num_attributes;
		std::vector<std::string> attributes;
		glGetProgramiv(m_id, GL_ACTIVE_ATTRIBUTES, &num_attributes);
		attributes.reserve(num_attributes);
		
		int max_name_len;
		glGetProgramiv(m_id, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &max_name_len);
		std::string temp_name;
		temp_name.resize(max_name_len);
		for (int i = 0; i < num_attributes; ++i)
		{
			int array_size;
			GLenum type;
			GLsizei actual_length;
			glGetActiveAttrib(m_id, i, temp_name.size(), &actual_length, &array_size, &type, temp_name.data());

			attributes.emplace_back(temp_name.data(), actual_length);
		}

		return attributes;
	}

	ShaderProgram::TargetFlags ShaderProgram::flags() const noexcept
	{
		return m_flags;
	}

	unsigned int ShaderProgram::id() const noexcept
	{
		return m_id;
	}

}