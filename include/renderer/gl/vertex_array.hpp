#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>
#include <array>

#include <glad/glad.h>

#include <renderer/gl/buffer.hpp>
#include <renderer/gl/types.hpp>

namespace gfx::gl
{
	enum class Attribute
	{
		eColor,
		ePosition,
		eNormal,
		eTexCoords
	};

	class VertexArray
	{
	public:

		VertexArray() noexcept;
		VertexArray(const VertexArray& other) = delete;
		VertexArray(VertexArray&& other) noexcept;

		VertexArray& operator=(const VertexArray& other) = delete;
		VertexArray& operator=(VertexArray&& other) noexcept;

		~VertexArray() noexcept;

		void bind() const noexcept;
		void unbind() const noexcept;

		void bindVertexBuffer(const Buffer& buf, ptrdiff_t offset, ssize_t stride, unsigned int binding_index = 0) noexcept;
		void bindElementBuffer(const Buffer& buf) noexcept;

		void enableAttribute(unsigned int attrib_index) noexcept;
		void disableAttribute(unsigned int attrib_index) noexcept;

		void formatAttribute(unsigned int attrib_index, int size, Type type, bool normalized, ssize_t relative_offset) noexcept;
		void formatAttributeI(unsigned int attrib_index, int size, Type type, ssize_t relative_offset) noexcept;
		void formatAttributeL(unsigned int attrib_index, int size, Type type, ssize_t relative_offset) noexcept;
		void bindAttribute(unsigned int attrib_index, unsigned int binding_index = 0) noexcept;


		template<typename Vertex>
		void enableAttributes(const std::vector<Attribute>& attrs, unsigned int binding_index = 0) 
		{
			for (const auto attr : attrs)
			{
				enableAttribute<Vertex>(attr, binding_index);
			}
		}

		template<typename Vertex, size_t N>
		void enableAttributes(const std::array<Attribute, N>& attrs, unsigned int binding_index = 0)
		{
			for (const auto attr : attrs)
			{
				enableAttribute<Vertex>(attr, binding_index);
			}
		}

		template<typename Vertex>
		void enableAttribute(Attribute attr, unsigned int binding_index = 0)
		{
			enableAttribute(Vertex::attribIndex(attr));

			auto base_type = Vertex::baseType(attr);
			if (base_type == Type::eFloat)
				formatAttribute(Vertex::attribIndex(attr), Vertex::size(attr), Vertex::type(attr), Vertex::normalized(attr), Vertex::relativeOffset(attr));
			else if (base_type == Type::eDouble)
				formatAttributeL(Vertex::attribIndex(attr), Vertex::size(attr), Vertex::type(attr), Vertex::relativeOffset(attr));
			else if (base_type == Type::eInt)
				formatAttributeI(Vertex::attribIndex(attr), Vertex::size(attr), Vertex::type(attr), Vertex::relativeOffset(attr));
			else
				throw std::invalid_argument("vertex base type is not of Type::eFloat, Type::eDouble, Type::eInt");

			bindAttribute(Vertex::attribIndex(attr), binding_index);
		}

		template<typename Vertex>
		void disableAttributes(const std::vector<Attribute>& attrs, unsigned int binding_index = 0)
		{
			for (const auto attr : attrs)
			{
				disableAttribute<Vertex>(attr, binding_index);
			}
		}

		template<typename Vertex, size_t N>
		void disableAttributes(const std::array<Attribute, N>& attrs, unsigned int binding_index = 0)
		{
			for (const auto attr : attrs)
			{
				disableAttribute<Vertex>(attr, binding_index);
			}
		}

		template<typename Vertex>
		void disableAttribute(Attribute attr, unsigned int binding_index = 0)
		{
			glDisableVertexArrayAttrib(m_id, Vertex::attribIndex(attr));
		}

		unsigned int id() const noexcept;
	private:
		unsigned int m_id;
	};
}