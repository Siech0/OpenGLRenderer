
#include <renderer/gl/framebuffer.hpp>

#include <stdexcept>
#include <utility>

namespace gfx::gl
{
	Framebuffer::Framebuffer() noexcept
	{
		glCreateFramebuffers(1, &m_id);
	}

	Framebuffer::Framebuffer(Framebuffer&& other) noexcept
	{
		std::swap(m_id, other.m_id);
	}

	Framebuffer& Framebuffer::operator=(Framebuffer&& other) noexcept
	{
		std::swap(m_id, other.m_id);
		return *this;
	}

	Framebuffer::~Framebuffer() noexcept
	{
		glDeleteFramebuffers(1, &m_id);
	}

	void Framebuffer::bind(Target target) const noexcept
	{
		glBindFramebuffer((GLenum) target, m_id);
	}

	void Framebuffer::unbind(Target target) const noexcept
	{
		glBindFramebuffer((GLenum) target, 0);
	}
	
	void Framebuffer::attach(const Renderbuffer& buffer, Attachment attachment) noexcept
	{
		glNamedFramebufferRenderbuffer(m_id, (GLenum)attachment, GL_RENDERBUFFER, buffer.id());
	}

	void Framebuffer::attach(const Texture& texture, Attachment attachment, int level) noexcept
	{
		glNamedFramebufferTexture(m_id, (GLenum)attachment, texture.id(), level);
	}

	Framebuffer::Status Framebuffer::status(Target target) const noexcept
	{
		return (Framebuffer::Status)glCheckNamedFramebufferStatus(m_id, (GLenum)target);
	}

	unsigned int Framebuffer::id() const noexcept
	{
		return m_id;
	}

}