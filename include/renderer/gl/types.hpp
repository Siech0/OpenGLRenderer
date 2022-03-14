#pragma once

#include <glad/glad.h>
#include <climits>



namespace gfx::gl
{

#if !defined(SSIZE_MIN)
	#if SIZE_MAX == UINT_MAX
		typedef int ssize_t;        /* common 32 bit case */
	#define SSIZE_MIN  INT_MIN
	#define SSIZE_MAX  INT_MAX
	#elif SIZE_MAX == ULONG_MAX
		typedef long ssize_t;       /* linux 64 bits */
	#define SSIZE_MIN  LONG_MIN
	#define SSIZE_MAX  LONG_MAX
	#elif SIZE_MAX == ULLONG_MAX
		typedef long long ssize_t;  /* windows 64 bits */
	#define SSIZE_MIN  LLONG_MIN
	#define SSIZE_MAX  LLONG_MAX
	#elif SIZE_MAX == USHRT_MAX
		typedef short ssize_t;      /* is this even possible? */
	#define SSIZE_MIN  SHRT_MIN
	#define SSIZE_MAX  SHRT_MAX
	#elif SIZE_MAX == UINTMAX_MAX
		typedef uintmax_t ssize_t;  /* last resort */
	#define SSIZE_MIN  INTMAX_MIN
	#define SSIZE_MAX  INTMAX_MAX
	#endif
#endif


	enum class Type : GLenum
	{
		eFloat = GL_FLOAT,
		eDouble = GL_DOUBLE,
		eUnsignedByte = GL_UNSIGNED_BYTE,
		eByte = GL_BYTE,
		eUnsignedShort = GL_UNSIGNED_SHORT,
		eShort = GL_SHORT,
		eUnsignedInt = GL_UNSIGNED_INT,
		eInt = GL_INT,
		eUnsignedByte332 = GL_UNSIGNED_BYTE_3_3_2,
		eUnsignedByte233Rev = GL_UNSIGNED_BYTE_2_3_3_REV,
		eUnsignedShort565 = GL_UNSIGNED_SHORT_5_6_5,
		eUnsignedShort565Rev = GL_UNSIGNED_SHORT_5_6_5_REV,
		eUnsignedShort4444 = GL_UNSIGNED_SHORT_4_4_4_4,
		eUnsignedShort4444Rev = GL_UNSIGNED_SHORT_4_4_4_4_REV,
		eUnsignedShort5551 = GL_UNSIGNED_SHORT_5_5_5_1,
		eUnsignedShort1555 = GL_UNSIGNED_SHORT_1_5_5_5_REV,
		eUnsignedInt8888 = GL_UNSIGNED_INT_8_8_8_8,
		eUnsignedInt8888Rev = GL_UNSIGNED_INT_8_8_8_8_REV,
		eUnsignedInt1010102 = GL_UNSIGNED_INT_10_10_10_2,
		eUnsignedInt210101010 = GL_UNSIGNED_INT_2_10_10_10_REV
	};

	enum class DataFormat : GLenum
	{
		// Base formats
		eR = GL_RED,
		eRG = GL_RG,
		eRGB = GL_RGB,
		eRGBA = GL_RGBA,

		// Sized formats
		eR8 = GL_R8,
		eR8SNorm = GL_R8_SNORM,
		eR16 = GL_R16,
		eR16SNorm = GL_R16_SNORM,
		eRG8 = GL_RG8,
		eRG8SNorm = GL_RG8_SNORM,
		eRG16 = GL_RG16_SNORM,
		eR3G3B2 = GL_R3_G3_B2,
		eRGB4 = GL_RGB4,
		eRGB5 = GL_RGB5,
		eRGB8 = GL_RGB8,
		eRGB8SNorm = GL_RGB8_SNORM,
		eRGB10 = GL_RGB10,
		eRGB12 = GL_RGB12,
		eRGB16Snorm = GL_RGB16_SNORM,
		eRGBA2 = GL_RGBA2,
		eRGBA4 = GL_RGBA4,
		eRGB5A1 = GL_RGB5_A1,
		eRGBA8 = GL_RGBA8,
		eRGBA8SNorm = GL_RGBA8_SNORM,
		eRGB10A2 = GL_RGB10_A2,
		eRGB10A2UI = GL_RGB10_A2UI,
		eRGBA12 = GL_RGBA12,
		eRGBA16 = GL_RGBA16,
		eSRGB8 = GL_SRGB8,
		eSRG8Alpha8 = GL_SRGB8_ALPHA8,
		eR16F = GL_R16F,
		eRG16F = GL_RG16F,
		eRGB16F = GL_RG16F,
		eRGBA16F = GL_RGBA16F,
		eR32F = GL_R32F,
		eRG32F = GL_RG32F,
		eRGB32F = GL_RGB32F,
		eRGBA32F = GL_RGBA32F,
		eR11FG11FB10F = GL_R11F_G11F_B10F,
		eRGB9E5 = GL_RGB9_E5,
		eR8I = GL_R8I,
		eR8UI = GL_R8UI,
		eR16I = GL_R16I,
		eR16UI = GL_R16UI,
		eR32I = GL_R32I,
		eR32UI = GL_R32UI,
		eRG8I = GL_RG8I,
		eRG8UI = GL_RG8UI,
		eRG16I = GL_RG16I,
		eRG16UI = GL_RG16UI,
		eRG32I = GL_RG32I,
		eRG32UI = GL_RG32UI,
		eRGB8I = GL_RGB8I,
		eRGB8UI = GL_RGB8UI,
		eRGB16I = GL_RGB16I,
		eRGB16UI =  GL_RGB16UI,
		eRGB32I = GL_RGB32I,
		eRGB32UI = GL_RGB32UI,

		// Depth formats
		eStencilIndex1 = GL_STENCIL_INDEX1,
		eStencilIndex4 = GL_STENCIL_INDEX4,
		eStencilIndex8 = GL_STENCIL_INDEX8,
		eStencilIndex16 = GL_STENCIL_INDEX16,

		// Compressed formats
		eCompressedRedRGTC1 = GL_COMPRESSED_RED_RGTC1,
		eCompressedSignedRedRGTC1 = GL_COMPRESSED_RED_RGTC1,
		eCompressedRgRGTC2 = GL_COMPRESSED_RG_RGTC2,
		eCompressedSignedRgRGTC2 = GL_COMPRESSED_RG_RGTC2,
		eCompressedRgbaBptcUnorm = GL_COMPRESSED_RGBA_BPTC_UNORM,
		eCompressedSrgbAlphaBptcUnorm = GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM,
		eCompressedRgbBptcSignedFloat = GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT,
		eCompressedRgbBptcUnsignedFloat = GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT
	};

	enum class ComparisonFunction : int
	{
		eLEqual = GL_LEQUAL,
		eGEqual = GL_GEQUAL,
		eLess = GL_LESS,
		eGreater = GL_GREATER,
		eEqual = GL_EQUAL,
		eNotEqual = GL_NOTEQUAL,
		eAlways = GL_ALWAYS,
		eNever = GL_NEVER
	};
	
	enum class TextureCompareMode : int
	{
		eCompareRefToTexture = GL_COMPARE_REF_TO_TEXTURE,
		eNone = GL_NONE
	};

	enum class MinificationFunction : int
	{
		eNearest = GL_NEAREST,
		eLinear = GL_LINEAR,
		eNearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
		eLinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
		eNearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
		eLinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR
	};

	enum class MagnificationFunction : int
	{
		eNearest = GL_NEAREST,
		eLinear = GL_LINEAR
	};
}
