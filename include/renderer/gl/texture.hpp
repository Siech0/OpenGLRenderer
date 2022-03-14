#pragma once

#include <glad/glad.h>

#include <renderer/gl/buffer.hpp>
#include <renderer/gl/types.hpp>

namespace gfx::gl 
{
	class Texture
	{
	public:
		enum class Target : GLenum
		{
			eTexture1D = GL_TEXTURE_1D,
			eTexture2D = GL_TEXTURE_2D,
			eTexture3D = GL_TEXTURE_3D,
			eTexture1DArray = GL_TEXTURE_1D_ARRAY,
			eTexture2DArray = GL_TEXTURE_2D_ARRAY,
			eTextureRectangle = GL_TEXTURE_RECTANGLE,
			eTextureCubeMap = GL_TEXTURE_CUBE_MAP,
			eTextureCubeMapArray = GL_TEXTURE_CUBE_MAP_ARRAY,
			eTextureBuffer = GL_TEXTURE_BUFFER,
			eTexture2DMultisample = GL_TEXTURE_2D_MULTISAMPLE,
			eTexture2DMultisampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
		};

		enum class Parameter : GLenum
		{
			eDepthStencilTextureMode = GL_DEPTH_STENCIL_TEXTURE_MODE,
			eBaseLevel = GL_TEXTURE_BASE_LEVEL,
			eBorderColor = GL_TEXTURE_BORDER_COLOR,
			eCompareFunc = GL_TEXTURE_COMPARE_FUNC,
			eCompareMode = GL_TEXTURE_COMPARE_MODE,
			eLODBias = GL_TEXTURE_LOD_BIAS,
			eMinFilter = GL_TEXTURE_MIN_FILTER,
			eMagFilter = GL_TEXTURE_MAG_FILTER,
			eMinLOD = GL_TEXTURE_MIN_LOD,
			eMaxLOD = GL_TEXTURE_MAX_LOD,
			eMaxLevel = GL_TEXTURE_MAX_LEVEL,
			eSwizzleR = GL_TEXTURE_SWIZZLE_R,
			eSwizzleG = GL_TEXTURE_SWIZZLE_G,
			eSwizzleB = GL_TEXTURE_SWIZZLE_B,
			eSwizzleA = GL_TEXTURE_SWIZZLE_A,
			eSwizzleRGBA = GL_TEXTURE_SWIZZLE_RGBA,
			eWrapS = GL_TEXTURE_WRAP_S,
			eWrapT = GL_TEXTURE_WRAP_T,
			eWrapR = GL_TEXTURE_WRAP_R
		};

		Texture(Target target) noexcept;
		Texture(const Texture& other) = delete;
		Texture(Texture&& other) noexcept;

		Texture& operator=(const Texture& other) = delete;
		Texture& operator=(Texture&& other) noexcept;

		// Bindings
		void bind(Target target) const noexcept;
		void unbind(Target target) const noexcept;
		void bindUnit(int unit) const noexcept;
		void unbindUnit(int unit) const noexcept;

		// Parameters
		void parameter(Parameter pname, float param) noexcept;
		void parameter(Parameter pname, int param) noexcept;
		void parameter(Parameter pname, float* params) noexcept;
		void parameter(Parameter pname, int* params) noexcept;

		// Storage
		void buffer(DataFormat internal_format, const Buffer& buffer) noexcept;
		void bufferRange(DataFormat internal_format, const Buffer& buffer, intptr_t offset, ssize_t size) noexcept;

		void storage1D(size_t levels, DataFormat internal_format, ssize_t width) noexcept;
		void storage2D(size_t levels, DataFormat internal_format, ssize_t width, ssize_t height) noexcept;
		void storage3D(size_t levels, DataFormat internal_format, ssize_t width, ssize_t height, ssize_t depth) noexcept;

		void storage2DMultisample(ssize_t samples, DataFormat internal_format, ssize_t width, ssize_t height, bool fixed_sample_locations) noexcept;
		void storage3DMultisample(ssize_t samples, DataFormat internal_format, ssize_t width, ssize_t height, ssize_t depth, bool fixed_sample_locations) noexcept;

		void subImage1D(int level, int xoffset, ssize_t width, DataFormat format, Type type, const void* pixels) noexcept;
		void subImage2D(int level, int xoffset, int yoffset, ssize_t width, ssize_t height, DataFormat format, Type type, const void* pixels) noexcept;
		void subImage3D(int level, int xoffset, int yoffset, int zoffset, ssize_t width, ssize_t height, ssize_t depth, DataFormat format, Type type, const void* pixels) noexcept;

		void compressedSubImage1D(int level, int xoffset, ssize_t width, DataFormat format, ssize_t image_size, const void* data) noexcept;
		void compressedsubImage2D(int level, int xoffset, int yoffset, ssize_t width, ssize_t height, DataFormat format, ssize_t image_size, const void* data) noexcept;
		void compressedSubImage3D(int level, int xoffset, int yoffset, int zoffset, ssize_t width, ssize_t height, ssize_t depth, DataFormat format, ssize_t image_size, const void* data) noexcept;
		
		// Copy
		void copySubImage1D(int level, int xoffset, int x, int y, ssize_t width) noexcept;
		void copySubImage2D(int level, int xoffset, int yoffset, int x, int y, ssize_t width, ssize_t height) noexcept;
		void copySubImage3D(int level, int xoffset, int yoffset, int zoffset, int x, int y, ssize_t width, ssize_t height) noexcept;

		// Mipmap
		void generateMipmap() noexcept;

		// Texture Image
		void getTextureImage(int level, DataFormat format, Type type, ssize_t buf_size, void* pixels) noexcept;

		// Getters
		unsigned int id() const noexcept;

	private:

		unsigned int m_id;
	};
}