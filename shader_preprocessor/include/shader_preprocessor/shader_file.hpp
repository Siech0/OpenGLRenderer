#pragma once

#include <tsl/robin_map.h>

namespace shpp
{
	struct ShaderFile
	{
		tsl::robin_map<std::string, int> uniforms;
		tsl::robin_map<std::string, int> attributes;
	};
}