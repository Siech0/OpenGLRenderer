#pragma once

#include <string>

#include <renderer/gl/texture.hpp>

namespace gfx::core
{
#ifdef RENDERER_RC_ENABLED
	gfx::gl::Texture texture2DFromResource(const std::string& path);
#endif
}