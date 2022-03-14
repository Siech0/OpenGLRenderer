#pragma once

#include <renderer/core/shader_loader.hpp>

#include <fstream>
#include <stdexcept>
#include <iterator>

#ifdef RENDERER_RC_ENABLED
#include <cmrc/cmrc.hpp>
CMRC_DECLARE(rc);
#endif

using namespace gfx::gl;

namespace gfx::core
{
#ifdef RENDERER_RC_ENABLED
	Shader shaderFromResource(Shader::Target target, const std::string& filepath) 
	{
		auto rcfs = cmrc::rc::get_filesystem();
		auto file = rcfs.open(filepath);
		return Shader(target, std::string(file.begin(), file.end()));
	}
#endif

	Shader shaderFromFile(Shader::Target target, const std::string& filepath)
	{
		std::ifstream iss(filepath);
		if (!iss)
			throw std::runtime_error(std::string("Unable to open file '") + filepath + "'");

		return shaderFromStream(target, iss);
	}

	Shader shaderFromStream(Shader::Target target, std::istream& is)
	{
		std::string data;
		std::getline(is, data, '\0');
		return Shader(target, data);
	}
}