#pragma once

#include <iosfwd>
#include <stdexcept>
#include <vector>
#include "vertex.hpp"
#include "triangle.hpp"

namespace Peng
{
	class InvalidMeshException : public std::exception {};
	class VersionMismatchException : public std::exception {};

	struct Mesh
	{
		std::vector<Vertex> vertices;
		std::vector<Triangle> triangles;
	};
}

std::ostream &operator<<(std::ostream &stream, const Peng::Mesh &mesh);
std::istream &operator>>(std::istream &stream, Peng::Mesh &mesh) throw(Peng::InvalidMeshException, Peng::VersionMismatchException);
