#pragma once

#include <iosfwd>

namespace Peng
{
	struct Vertex
	{
		float position[3];
		float normal[3];
	};
}

std::ostream &operator<<(std::ostream &stream, const Peng::Vertex &vertex);
std::istream &operator>>(std::istream &stream, Peng::Vertex &vertex);
