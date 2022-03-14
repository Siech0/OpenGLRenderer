#include <renderer/core/tex_loader.hpp>

#ifdef RENDERER_RC_ENABLED
#include <cmrc/cmrc.hpp>
CMRC_DECLARE(rc);
#endif

#include <stb_image.h>

using namespace gfx::gl;

namespace gfx::core
{
#ifdef RENDERER_RC_ENABLED
	Texture texture2DFromResource(const std::string& path)
	{
		auto rcfs = cmrc::rc::get_filesystem();
		auto file = rcfs.open(path);

		int width, height, channels;
		const unsigned char* image_rc_data = (const unsigned char*)file.cbegin();
		size_t file_size = file.size();

		unsigned char* image_data = stbi_load_from_memory(image_rc_data, file_size, &width, &height, &channels, 0);
		if (image_data == nullptr)
		{
			throw std::runtime_error(std::string("Unable to parse file texture source file resource '") + path + "': " + stbi_failure_reason());
		}

		Texture texture(Texture::Target::eTexture2D);
		DataFormat internal_format;
		if (channels == 1)
			internal_format = DataFormat::eR8;
		else if (channels == 2)
			internal_format = DataFormat::eRG8;
		else if (channels == 3)
			internal_format = DataFormat::eRGB8;
		else
			internal_format = DataFormat::eRGBA8;
		texture.storage2D(0, internal_format, width, height);

		stbi_image_free(image_data);
		return std::move(texture);
}
#endif
}