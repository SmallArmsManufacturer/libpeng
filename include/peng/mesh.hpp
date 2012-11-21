#pragma once

#include <iosfwd>
#include <vector>
#include "vertex.hpp"
#include "triangle.hpp"

namespace Peng
{
	struct Mesh
	{
		std::vector<Vertex> vertices;
		std::vector<Triangle> triangles;
	};
}

std::ostream &operator<<(std::ostream &stream, const Peng::Mesh &mesh);
