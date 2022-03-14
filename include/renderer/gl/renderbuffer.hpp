#pragma once

#include <glad/glad.h>

#include <renderer/gl/types.hpp>

namespace gfx::gl
{
	class Renderbuffer
	{
	public:
		enum class Target : GLenum
		{
			eRenderbuffer = GL_RENDERBUFFER
		};

		Renderbuffer() noexcept;
		Renderbuffer(const Renderbuffer& other) = delete;
		Renderbuffer(Renderbuffer&& other);

		Renderbuffer& operator=(const Renderbuffer& other) = delete;
		Renderbuffer& operator=(Renderbuffer&& other);

		~Renderbuffer();
		
		// Binding
		void bind(Target target) const noexcept;
		void unbind(Target target) const noexcept;

		// Storage
		void storage(DataFormat internal_format, int width, int height) noexcept;

		// Getters
		unsigned int id() const noexcept;

	private:
		unsigned int m_id;
	};
}