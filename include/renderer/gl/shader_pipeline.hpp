#pragma once

#include <array>

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>

#include <renderer/gl/shader_program.hpp>


namespace gfx::gl
{
	class ShaderPipeline
	{
	public:
		using  TargetFlags = ShaderProgram::TargetFlags;

		ShaderPipeline() noexcept;
		ShaderPipeline(const ShaderPipeline& other) = delete;
		ShaderPipeline(ShaderPipeline&& other) noexcept;

		ShaderPipeline& operator=(const ShaderPipeline& other) = delete;
		ShaderPipeline& operator=(ShaderPipeline&& other) noexcept;

		template<typename T>
		bool setUniform(const std::string& name, const std::vector<T>& vs);

		template<typename T>
		long long setUniform(const std::string& name, const T& v)
		{
			unsigned int uniform_loc;
			for (const auto prog : m_programs)
			{
				if 
			}
		}

		template<typename T>
		long long setUniform(const std::string& name, const T& v)

		bool setUniform(const std::string& name, float v) const noexcept;
		bool setUniform(const std::string& name, const glm::vec2& v) const noexcept;
		bool setUniform(const std::string& name, const glm::vec3& v) const noexcept;


		bool attributeLocation(const std::string& attribute_name, unsigned int& binding_location) const noexcept;
		bool uniformLocation(const std::string& uniform_name, unsigned int& binding_location) const noexcept;
		TargetFlags flags() const noexcept;
		unsigned int id() const noexcept;

	private:
		std::array<ShaderProgram*, 5> m_programs;
		unsigned int m_id;
	};


}