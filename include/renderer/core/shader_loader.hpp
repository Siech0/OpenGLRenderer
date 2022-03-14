#pragma once

#include <iostream>
#include <string>

#include <renderer/gl/shader.hpp>

namespace gfx::core
{
#ifdef RENDERER_RC_ENABLED
	gfx::gl::Shader shaderFromResource(gfx::gl::Shader::Target target, const std::string& filepath);
#endif

	gfx::gl::Shader shaderFromFile(gfx::gl::Shader::Target target, const std::string& filepath);
	gfx::gl::Shader shaderFromStream(gfx::gl::Shader::Target target, std::istream& is);
}