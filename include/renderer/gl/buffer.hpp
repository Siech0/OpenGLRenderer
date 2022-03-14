#pragma once

#include <vector>

#include <glad/glad.h>

namespace gfx::gl
{
	class Buffer
	{
	public:
		enum class Target : GLenum
		{
			eArray = GL_ARRAY_BUFFER,
			eAtomicCounter = GL_ATOMIC_COUNTER_BUFFER,
			eCopyRead = GL_COPY_READ_BUFFER,
			eCopyWrite = GL_COPY_WRITE_BUFFER,
			eDispatchIndirect = GL_DISPATCH_INDIRECT_BUFFER,
			eDrawIndirect = GL_DRAW_INDIRECT_BUFFER,
			eElementArray = GL_ELEMENT_ARRAY_BUFFER,
			ePixelPack = GL_PIXEL_PACK_BUFFER,
			ePixelUnpack = GL_PIXEL_UNPACK_BUFFER,
			eQuery = GL_QUERY_BUFFER,
			eShaderStorage = GL_SHADER_STORAGE_BUFFER,
			eTexture = GL_TEXTURE_BUFFER,
			eTransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER,
			eUniform = GL_UNIFORM_BUFFER
		};

		enum class Usage : GLenum
		{
			eStreamDraw = GL_STREAM_DRAW,
			eStreamRead = GL_STREAM_READ,
			eStreamCopy = GL_STREAM_COPY,
			eStaticDraw = GL_STATIC_DRAW,
			eStaticRead = GL_STATIC_READ,
			eStaticCopy = GL_STATIC_COPY,
			eDynamicDraw = GL_DYNAMIC_DRAW,
			eDynamicRead = GL_DYNAMIC_READ,
			eDynamicCopy = GL_DYNAMIC_COPY
		};

		enum class StorageFlags : GLenum
		{
			eMapReadBit = GL_MAP_READ_BIT,
			eMapWriteBit = GL_MAP_WRITE_BIT,
			eDynamicStorageBit = GL_DYNAMIC_STORAGE_BIT,
			eMapPersistentBit = GL_MAP_PERSISTENT_BIT,
			eClientStorageBit = GL_CLIENT_STORAGE_BIT
		};

		Buffer() noexcept;
		Buffer(const Buffer& other) = delete;
		Buffer(Buffer&& other) noexcept;

		Buffer& operator=(const Buffer& other) = delete;
		Buffer& operator=(Buffer&& other) noexcept;

		~Buffer() noexcept;

		template<typename T>
		void bufferData(size_t count, const T* data, Usage usage) noexcept
		{
			bufferData(sizeof(T) * count, (const void *)data, usage);
		}

		template<typename T>
		void bufferData(const std::vector<T>& data, Usage usage) noexcept
		{
			bufferData(data.size(), data.data(), usage);
		}

		template<typename T, size_t N>
		void bufferData(const std::array<T, N>& data, Usage usage) noexcept
		{
			bufferData(N, data.data(), usage);
		}

		template<typename T, size_t N>
		void bufferData(const T(&data)[N], Usage usage) noexcept
		{
			bufferData(N, data.data(), usage);
		}

		void bufferData(size_t size, const void* data, Usage usage) noexcept;

		template<typename T>
		void bufferStorage(size_t count, const T* data, StorageFlags flags) noexcept
		{
			bufferStorage(sizeof(T) * count, (const void*)data, flags);
		}

		template<typename T>
		void bufferStorage(const std::vector<T>& data, StorageFlags flags) noexcept
		{
			bufferStorage(data.size(), data.data(), flags);
		}

		template<typename T, size_t N>
		void bufferStorage(const std::array<T, N>& data, StorageFlags flags) noexcept
		{
			bufferStorage(N, data.data(), flags);
		}

		template<typename T, size_t N>
		void bufferStorage(const T(&data)[N], StorageFlags flags) noexcept
		{
			bufferStorage(N, data, flags);
		}

		void bufferStorage(size_t size, const void* data, StorageFlags flags) noexcept;

		void bind(Target type) const noexcept;
		void unbind(Target type) const noexcept;

		unsigned int id() const noexcept;

	private:
		unsigned int m_id;
	};

	inline Buffer::StorageFlags operator|(Buffer::StorageFlags lhs, Buffer::StorageFlags rhs)
	{
		return (Buffer::StorageFlags)((GLenum)lhs | (GLenum)rhs);
	}


	inline Buffer::StorageFlags operator&(Buffer::StorageFlags lhs, Buffer::StorageFlags rhs)
	{
		return (Buffer::StorageFlags)((GLenum)lhs & (GLenum)rhs);
	}
}