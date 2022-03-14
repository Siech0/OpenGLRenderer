#include <renderer/gl/renderbuffer.hpp>

#include <utility>

namespace gfx::gl
{
	Renderbuffer::Renderbuffer() noexcept
	{
		glCreateRenderbuffers(1, &m_id);
	}

	Renderbuffer::Renderbuffer(Renderbuffer&& other)
	{
		using std::swap;
		swap(m_id, other.m_id);
	}

	Renderbuffer& Renderbuffer::operator=(Renderbuffer&& other)
	{
		using std::swap;
		swap(m_id, other.m_id);

		return *this;
	}

	Renderbuffer::~Renderbuffer()
	{
		glDeleteRenderbuffers(1, &m_id);
	}

	void Renderbuffer::bind(Target target) const noexcept
	{
		glBindRenderbuffer((GLenum)target, m_id);
	}

	void Renderbuffer::unbind(Target target) const noexcept
	{
		glBindRenderbuffer((GLenum)target, 0);
	}
	
	void Renderbuffer::storage(DataFormat internal_format, int width, int height) noexcept
	{
		glNamedRenderbufferStorage(m_id, (GLenum)internal_format, width, height);
	}

	unsigned int Renderbuffer::id() const noexcept
	{
		return m_id;
	}
}