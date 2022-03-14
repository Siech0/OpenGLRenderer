#include <renderer/gl/texture.hpp>

#include <utility>

namespace gfx::gl
{
	Texture::Texture(Target target) noexcept
	{
		glCreateTextures((GLenum)target, 1, &m_id);
	}

	Texture::Texture(Texture&& other) noexcept
	{
		using std::swap;
		swap(m_id, other.m_id);
	}

	Texture& Texture::operator=(Texture&& other) noexcept
	{
		using std::swap;
		swap(m_id, other.m_id);

		return *this;
	}

	void Texture::bind(Target target) const noexcept
	{
		glBindTexture((GLenum) target, m_id);
	}

	void Texture::unbind(Target target) const noexcept
	{
		glBindTexture((GLenum) target, 0);
	}

	void Texture::bindUnit(int unit) const noexcept
	{
		glBindTextureUnit(unit, m_id);
	}

	void Texture::unbindUnit(int unit) const noexcept
	{
		glBindTextureUnit(unit, 0);
	}

	void Texture::parameter(Parameter pname, float param) noexcept
	{
		glTextureParameterf(m_id, (GLenum) pname, param);
	}

	void Texture::parameter(Parameter pname, int param) noexcept
	{
		glTextureParameteri(m_id, (GLenum) pname, param);
	}

	void Texture::parameter(Parameter pname, float* params) noexcept
	{
		glTextureParameterfv(m_id, (GLenum) pname, params);
	}

	void Texture::parameter(Parameter pname, int* params) noexcept
	{
		glTextureParameteriv(m_id, (GLenum) pname, params);
	}

	void Texture::buffer(DataFormat internal_format, const Buffer& buffer) noexcept
	{
		glTextureBuffer(m_id, (GLenum)internal_format, buffer.id());
	}

	void Texture::bufferRange(DataFormat internal_format, const Buffer& buffer, intptr_t offset, ssize_t size) noexcept
	{
		glTextureBufferRange(m_id, (GLenum)internal_format, buffer.id(), offset, size);
	}

	void Texture::storage1D(size_t levels, DataFormat internal_format, ssize_t width) noexcept
	{
		glTextureStorage1D(m_id, levels, (GLenum)internal_format, width);
	}

	void Texture::storage2D(size_t levels, DataFormat internal_format, ssize_t width, ssize_t height) noexcept
	{
		glTextureStorage2D(m_id, levels, (GLenum) internal_format, width, height);
	}

	void Texture::storage3D(size_t levels, DataFormat internal_format, ssize_t width, ssize_t height, ssize_t depth) noexcept
	{
		glTextureStorage3D(m_id, levels, (GLenum)internal_format, width, height, depth);
	}

	void Texture::storage2DMultisample(ssize_t samples, DataFormat internal_format, ssize_t width, ssize_t height, bool fixed_sample_locations) noexcept
	{
		glTextureStorage2DMultisample(m_id, samples, (GLenum)internal_format, width, height, fixed_sample_locations);
	}

	void Texture::storage3DMultisample(ssize_t samples, DataFormat internal_format, ssize_t width, ssize_t height, ssize_t depth, bool fixed_sample_locations) noexcept
	{
		glTextureStorage3DMultisample(m_id, samples, (GLenum)internal_format, width, height, depth, fixed_sample_locations);
	}

	void Texture::subImage1D(int level, int xoffset, ssize_t width, DataFormat format, Type type, const void *pixels) noexcept
	{
		glTextureSubImage1D(m_id, level, xoffset, width, (GLenum)format, (GLenum)type, pixels);
	}

	void Texture::subImage2D(int level, int xoffset, int yoffset, ssize_t width, ssize_t height, DataFormat format, Type type, const void* pixels) noexcept
	{
		glTextureSubImage2D(m_id, level, xoffset, yoffset, width, height, (GLenum)format, (GLenum)type, pixels);
	}

	void Texture::subImage3D(int level, int xoffset, int yoffset, int zoffset, ssize_t width, ssize_t height, ssize_t depth, DataFormat format, Type type, const void* pixels) noexcept
	{
		glTextureSubImage3D(m_id, level, xoffset, yoffset, zoffset, width, height, depth, (GLenum)format, (GLenum)type, pixels);
	}

	void Texture::compressedSubImage1D(int level, int xoffset, ssize_t width, DataFormat format, ssize_t image_size, const void* data) noexcept
	{
		glCompressedTextureSubImage1D(m_id, level, xoffset, width, (GLenum)format, image_size, data);
	}

	void Texture::compressedsubImage2D(int level, int xoffset, int yoffset, ssize_t width, ssize_t height, DataFormat format, ssize_t image_size, const void* data) noexcept
	{
		glCompressedTextureSubImage2D(m_id, level, xoffset, yoffset, width, height, (GLenum)format, image_size, data);
	}

	void Texture::compressedSubImage3D(int level, int xoffset, int yoffset, int zoffset, ssize_t width, ssize_t height, ssize_t depth, DataFormat format, ssize_t image_size, const void* data) noexcept 
	{
		glCompressedTextureSubImage3D(m_id, level, xoffset, yoffset, zoffset, width, height, depth, (GLenum)format, image_size, data);
	}

	void Texture::copySubImage1D(int level, int xoffset, int x, int y, ssize_t width) noexcept
	{
		glCopyTextureSubImage1D(m_id, level, xoffset, x, y, width);
	}

	void Texture::copySubImage2D(int level, int xoffset, int yoffset, int x, int y, ssize_t width, ssize_t height) noexcept
	{
		glCopyTextureSubImage2D(m_id, level, xoffset, yoffset, x, y, width, height);
	}

	void Texture::copySubImage3D(int level, int xoffset, int yoffset, int zoffset, int x, int y, ssize_t width, ssize_t height) noexcept
	{
		glCopyTextureSubImage3D(m_id, level, xoffset, yoffset, zoffset, x, y, width, height);
	}

	void Texture::getTextureImage(int level, DataFormat format, Type type, ssize_t buf_size, void* pixels) noexcept
	{
		glGetTextureImage(m_id, level, (GLenum)format, (GLenum)type, buf_size, pixels);
	}

	void Texture::generateMipmap() noexcept
	{
		glGenerateTextureMipmap(m_id);
	}

	unsigned int Texture::id() const noexcept
	{
		return m_id;
	}
}