#include <renderer/gl/buffer.hpp>

#include <utility>

namespace gfx::gl
{
	Buffer::Buffer() noexcept
	{
		glCreateBuffers(1, &m_id);
	}

	Buffer::Buffer(Buffer&& other) noexcept
	{
		std::swap(m_id, other.m_id);
	}

	Buffer& Buffer::operator=(Buffer&& other) noexcept
	{
		std::swap(m_id, other.m_id);
		return *this;
	}

	Buffer::~Buffer() noexcept
	{
		glDeleteBuffers(1, &m_id);
	}

	void Buffer::bufferData(size_t size, const void* data, Usage usage) noexcept
	{
		glNamedBufferData(m_id, size, data, (GLenum)usage);
	}

	void Buffer::bufferStorage(size_t size, const void* data, StorageFlags flags) noexcept
	{
		glNamedBufferStorage(m_id, size, data, (GLenum)flags);
	}

	void Buffer::bind(Target type) const noexcept
	{
		glBindBuffer((GLenum) type, m_id);
	}

	void Buffer::unbind(Target type) const noexcept
	{
		glBindBuffer((GLenum) type, m_id);
	}

	unsigned int Buffer::id() const noexcept
	{
		return m_id;
	}
}