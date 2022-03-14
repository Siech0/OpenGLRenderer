#include <renderer/gl/shader.hpp>

#include <stdexcept>
#include <string_view>
#include <fstream>
#include <utility>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gfx::gl
{
	Shader::Shader(Target target) noexcept :
		m_target(target),
		m_id(glCreateShader((GLenum)target))
	{ }

	Shader::Shader(Target target, const std::string& data) :
		m_target(target),
		m_id(glCreateShader((GLenum)target))
	{
		loadSource(data);
	}

	Shader::Shader(Shader&& other) noexcept
	{
		using std::swap;
		swap(m_id, other.m_id);
		swap(m_target, other.m_target);
	}

	Shader& Shader::operator=(Shader&& other) noexcept
	{
		using std::swap;
		swap(m_id, other.m_id);
		swap(m_target, other.m_target);
		return *this;
	}

	Shader::~Shader()
	{
		glDeleteShader(m_id);
	}

	void Shader::loadSource(const std::string& data)
	{

		const int shader_data_size = data.size();
		const char* const shader_data_ptr = data.data();
		glShaderSource(m_id, 1, &shader_data_ptr, &shader_data_size);
		glCompileShader(m_id);

#if !defined(NDEBUG) || defined(RENDER_ENABLE_SHADER_DEBUG)
		{
			int status, info_log_len;
			glGetShaderiv(m_id, GL_COMPILE_STATUS, &status);
			glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &info_log_len);
			if (!status)
			{
				if (info_log_len > 0)
				{
					std::string info_log;
					info_log.resize(info_log_len);
					glGetShaderInfoLog(m_id, info_log_len, nullptr, info_log.data());
					throw std::runtime_error(info_log);
				}
				else
				{
					throw std::runtime_error("unknown shader compilation error");
				}
			}
		}
#endif
	}

	Shader::Target Shader::target() const noexcept
	{
		return m_target;
	}

	unsigned int Shader::id() const noexcept
	{
		return m_id;
	}
}