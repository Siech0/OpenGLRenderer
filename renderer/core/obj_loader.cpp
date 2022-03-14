#include <renderer/core/obj_loader.hpp>

#include <stdexcept>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <fstream>
#include <iostream>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <tiny_obj_loader.h>


#ifdef RENDERER_RC_ENABLED
#include <cmrc/cmrc.hpp>
CMRC_DECLARE(rc);
#endif


namespace gfx::core
{
#ifdef RENDERER_RC_ENABLED
	void objFromResource(
		const std::string& path,
		std::vector<Vertex>& vertices,
		std::vector<unsigned int>& indices
	)
	{
		auto rcfs = cmrc::rc::get_filesystem();
		auto file = rcfs.open(path);

		objFromString(std::string(file.cbegin(), file.cend()), vertices, indices);
	}
#endif

	void objFromFile(
		const std::string& path,
		std::vector<Vertex>& vertices,
		std::vector<unsigned int>& indices
	)
	{
		std::ifstream is(path);
		objFromStream(is, vertices, indices);
	}

	void objFromStream(
		std::istream& is,
		std::vector<Vertex>& vertices,
		std::vector<unsigned int>& indices
	)
	{
		is.seekg(0, std::ios::end);
		auto len = is.tellg();
		is.seekg(0, std::ios::beg);
		
		std::string data;
		data.resize(len);
		is.read(&data[0], len);

		return objFromString(data, vertices, indices);
	}

	void objFromString(
		const std::string& data,
		std::vector<Vertex>& vertices,
		std::vector<unsigned int>& indices
	)
	{
		tinyobj::ObjReaderConfig reader_config;
		reader_config.vertex_color = false;
		reader_config.triangulation_method = "simple";
	
		tinyobj::ObjReader reader;
		if (!reader.ParseFromString(data, "", reader_config))
			throw std::runtime_error("unable to parse object file");

		auto& attrib = reader.GetAttrib();
		auto& shapes = reader.GetShapes();

		using tinyobj::index_t;
		using tinyobj::real_t;

		std::unordered_map<Vertex, unsigned int, Vertex::Hasher> vertex_index_map;
		unsigned int current_index = 0;

		// Loop over shapes
		for (size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces(polygon)
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

				Vertex vertex;

				// Loop over vertices in the face.
				for (size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
					tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
					tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];
					vertex.position = glm::vec3(vx, vy, vz);

					// Check if `normal_index` is zero or positive. negative = no normal data
					if (idx.normal_index >= 0) {
						tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
						tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
						tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
						//vertex.normal = glm::vec3(nx, ny, nz);
					}

					// Check if `texcoord_index` is zero or positive. negative = no texcoord data
					if (idx.texcoord_index >= 0) {
						tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
						tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
						//vertex.tex_coords = glm::vec2(tx, ty);
					}

					// Optional: vertex colors
					// tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
					// tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
					// tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];

					// Calculate vertex reuse
					// Already exists
					auto it = vertex_index_map.find(vertex);
					if (it != vertex_index_map.end())
					{
						indices.push_back(it->second);
					}
					// Doesn't exist
					else
					{
						vertices.push_back(vertex);
						indices.push_back(current_index);
						vertex_index_map.emplace(vertex, current_index);
						current_index += 1;
					};
				}
				index_offset += fv;
			}
		}
	}

	void objFromString(
		std::string_view& data,
		std::vector<Vertex>& vertices,
		std::vector<unsigned int>& indices
	)
	{

	}
}