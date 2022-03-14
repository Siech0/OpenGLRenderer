#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <istream>

#include <renderer/core/vertex.hpp>

namespace gfx::core
{

#ifdef RENDERER_RC_ENABLED
	void objFromResource(
		const std::string& path,
		std::vector<Vertex>& vertices,
		std::vector<unsigned int>& indices
	);
#endif

	void objFromFile(
		const std::string& path,
		std::vector<Vertex>& vertices,
		std::vector<unsigned int>& indices
	);

	void objFromStream(
		std::istream& is,
		std::vector<Vertex>& vertices,
		std::vector<unsigned int>& indices
	);

	void objFromString(
		const std::string& data,
		std::vector<Vertex>& vertices,
		std::vector<unsigned int>& indices
	);

}