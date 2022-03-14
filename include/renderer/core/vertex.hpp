#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <renderer/gl/vertex_array.hpp>
#include <renderer/gl/types.hpp>

#include <renderer/utility/hash.hpp>

namespace gfx::core
{

	struct Vertex
	{

		struct Hasher
		{
			size_t operator()(const Vertex& obj) const
			{
				return gfx::util::hash_val(
					obj.position.x, obj.position.y, obj.position.z, 
					obj.tex_coords.x, obj.tex_coords.y, 
					obj.normal.x, obj.normal.y, obj.normal.z
				);
			}
		};

		Vertex(
			const glm::vec3& position_ = glm::vec3(0.0f, 0.0f, 0.0f),
			const glm::vec2& tex_coords_ = glm::vec2(0.0f, 0.0f),
			const glm::vec3& normal_ = glm::vec3(0.0f, 0.0f, 0.0f)
		) :
			position(position_)
		{}



		bool operator==(const Vertex& other) const noexcept;

		glm::vec3 position;
		glm::vec2 tex_coords;
		glm::vec3 normal;

		static gl::Type baseType(gl::Attribute attr) noexcept;
		static unsigned int attribIndex(gl::Attribute attr) noexcept;
		static int size(gl::Attribute attr) noexcept;
		static gl::Type type(gl::Attribute attr) noexcept;
		static gl::ssize_t stride(gl::Attribute attr) noexcept;
		static unsigned int relativeOffset(gl::Attribute attr) noexcept;
		static bool normalized(gl::Attribute attr) noexcept;
	};

}