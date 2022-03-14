#include <renderer/core/vertex.hpp>

#include <cmath>
#include <limits>

namespace gfx::core
{

	bool Vertex::operator==(const Vertex& other) const noexcept
	{
		constexpr auto EPSILON = std::numeric_limits<float>::epsilon();

		const auto compVec3 = [EPSILON](const glm::vec3& a, const glm::vec3& b)  noexcept -> bool
		{
			const auto diff = a - b;
			return std::abs(diff.x) < EPSILON && std::abs(diff.y) < EPSILON && std::abs(diff.z) < EPSILON;
		};

		const auto compVec2 = [EPSILON](const glm::vec2& a, const glm::vec2& b) noexcept -> bool
		{
			const auto diff = a - b;
			return std::abs(diff.x) < EPSILON && std::abs(diff.y) < EPSILON;
		};

		return compVec3(position, other.position) && compVec2(tex_coords, other.tex_coords) && compVec3(normal, other.normal);

	}

	gl::Type Vertex::baseType(gl::Attribute attr) noexcept
	{
		return gl::Type::eFloat;
	}

	unsigned int Vertex::attribIndex(gl::Attribute attr) noexcept
	{
		switch (attr)
		{
		case gl::Attribute::ePosition:
			return 0;
		case gl::Attribute::eTexCoords:
			return 1;
		case gl::Attribute::eNormal:
			return 2;
		default:
			return 0;
		}
	}

	int Vertex::size(gl::Attribute attr) noexcept
	{
		switch (attr)
		{
		case gl::Attribute::ePosition:
			return 3;
		case gl::Attribute::eTexCoords:
			return 2;
		case gl::Attribute::eNormal:
			return 3;
		default:
			return 0;
		}
	}

	gl::Type Vertex::type(gl::Attribute attr) noexcept
	{
		return gl::Type::eFloat;
	}

	gl::ssize_t Vertex::stride(gl::Attribute attr) noexcept
	{
		return sizeof(Vertex);
	}

	unsigned int Vertex::relativeOffset(gl::Attribute attr) noexcept
	{
		switch (attr)
		{
		case gl::Attribute::ePosition:
			return offsetof(Vertex, position);
		case gl::Attribute::eTexCoords:
			return offsetof(Vertex, tex_coords);
		case gl::Attribute::eNormal:
			return offsetof(Vertex, normal);
		default:
			return 0;
		}
	}

	bool Vertex::normalized(gl::Attribute attr) noexcept
	{
		return false;
	}

}