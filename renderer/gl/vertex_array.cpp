
#include <renderer/gl/vertex_array.hpp>

#include <utility>

namespace gfx::gl
{
	VertexArray::VertexArray() noexcept
	{
		glCreateVertexArrays(1, &m_id);
	}

	VertexArray::VertexArray(VertexArray&& other) noexcept
	{
		using std::swap;
		swap(m_id, other.m_id);
	}

	VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
	{
		std::swap(m_id, other.m_id);
		return *this;
	}

	VertexArray::~VertexArray() noexcept
	{
		glDeleteVertexArrays(1, &m_id);
	}

	void VertexArray::bind() const noexcept
	{
		glBindVertexArray(m_id);
	}

	void VertexArray::unbind() const noexcept
	{
		glBindVertexArray(0);
	}

	void VertexArray::bindVertexBuffer(const Buffer& buf, ptrdiff_t offset, ssize_t stride, unsigned int binding_index) noexcept
	{
		glVertexArrayVertexBuffer(m_id, binding_index, buf.id(), offset, stride);
	}

	void VertexArray::bindElementBuffer(const Buffer& buf) noexcept
	{
		glVertexArrayElementBuffer(m_id, buf.id());
	}

	void VertexArray::enableAttribute(unsigned int attrib_index) noexcept
	{
		glEnableVertexArrayAttrib(m_id, attrib_index);
	}

	void VertexArray::disableAttribute(unsigned int attrib_index) noexcept
	{
		glDisableVertexArrayAttrib(m_id, attrib_index);
	}

	void VertexArray::formatAttribute(unsigned int attrib_index, int size, Type type, bool normalized, ssize_t relative_offset) noexcept
	{
		glVertexArrayAttribFormat(m_id, attrib_index, size, (GLenum)type, normalized, relative_offset);
	}

	void VertexArray::formatAttributeI(unsigned int attrib_index, int size, Type type, ssize_t relative_offset) noexcept
	{
		glVertexArrayAttribIFormat(m_id, attrib_index, size, (GLenum)type, relative_offset);
	}

	void VertexArray::formatAttributeL(unsigned int attrib_index, int size, Type type, ssize_t relative_offset) noexcept
	{
		glVertexArrayAttribLFormat(m_id, attrib_index, size, (GLenum)type, relative_offset);
	}

	void VertexArray::bindAttribute(unsigned int attrib_index, unsigned int binding_index) noexcept
	{
		glVertexArrayAttribBinding(m_id, attrib_index, binding_index);
	}

	unsigned int VertexArray::id() const noexcept
	{
		return m_id;
	}
}