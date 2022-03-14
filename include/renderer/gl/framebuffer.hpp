#pragma once

#include <glad/glad.h>

#include <renderer/gl/renderbuffer.hpp>
#include <renderer/gl/texture.hpp>

namespace gfx::gl
{
	class Framebuffer
	{
	public:
		enum class Target : GLenum
		{
			eFramebuffer = GL_FRAMEBUFFER,
			eDrawFramebuffer = GL_DRAW_FRAMEBUFFER,
			eReadFramebuffer = GL_READ_FRAMEBUFFER
		};

		enum class Attachment : GLenum
		{
			eColor0 = GL_COLOR_ATTACHMENT0,
			eColor1 = GL_COLOR_ATTACHMENT1,
			eColor2 = GL_COLOR_ATTACHMENT2,
			eColor3 = GL_COLOR_ATTACHMENT3,
			eColor4 = GL_COLOR_ATTACHMENT4,
			eColor5 = GL_COLOR_ATTACHMENT5,
			eColor6 = GL_COLOR_ATTACHMENT6,
			eColor7 = GL_COLOR_ATTACHMENT7,
			eDepth = GL_DEPTH_ATTACHMENT,
			eStencil = GL_STENCIL_ATTACHMENT
		};

		enum class Status : GLenum
		{
			eUndefined = GL_FRAMEBUFFER_UNDEFINED,
			eIncompleteAttachment = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT,
			eIncompleteMissingAttachment = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
			eIncompleteDrawBuffer = GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER,
			eIncompleteReadBuffer = GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER,
			eUnsupported = GL_FRAMEBUFFER_UNSUPPORTED,
			eIncompleteMultisample = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,
			eIncompleteLayerTargets = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS,
			eComplete = GL_FRAMEBUFFER_COMPLETE
		};

		Framebuffer() noexcept;
		Framebuffer(const Framebuffer&) = delete;
		Framebuffer(Framebuffer&&) noexcept;

		Framebuffer& operator=(const Framebuffer&) = delete;
		Framebuffer& operator=(Framebuffer&&) noexcept;

		~Framebuffer() noexcept;

		// Binding
		void bind(Target target = Target::eFramebuffer) const noexcept;
		void unbind(Target target = Target::eFramebuffer) const noexcept;

		// Attachment
		void attach(const Renderbuffer& buffer, Attachment attachment) noexcept;
		void attach(const Texture& texture, Attachment attachment, int level) noexcept;

		// Getters
		Status status(Target  target = Target::eFramebuffer) const noexcept;
		unsigned int id() const noexcept;

	private:
		unsigned int m_id;
	};
} // namespace renderer::backend::gl