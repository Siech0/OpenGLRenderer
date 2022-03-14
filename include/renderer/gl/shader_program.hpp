#pragma once

#include <vector>
#include <string>

#include <renderer/gl/shader.hpp>

namespace gfx::gl
{

	class ShaderProgram
	{
	public:
		ShaderProgram() noexcept;
		
		template<typename InputIt>
		ShaderProgram(InputIt begin, InputIt end)
		{
			attachShaders(begin, end);
		}

		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram(ShaderProgram&&) = default;

		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&&) = default;

		~ShaderProgram() noexcept;

		void attachShader(const Shader& shader) noexcept;
		void detachShader(const Shader& shader) noexcept;


		void link();

		int getUniform(const std::string& uniform_name) const;
		int getUniform(const char* uniform_name) const;

		void bind() const noexcept;
		void unbind() const noexcept;

		unsigned int id() const noexcept;

		// useful  debug info
		std::vector<std::string> getUniformNames() const;
		std::vector<std::string> getAttributeNames() const;

	private:
		unsigned int m_id;
	};
}