#include "peng/vertex.hpp"

#include <iostream>

static_assert(std::is_pod<Peng::Vertex>::value, "Peng::Vertex must be a POD type.");

std::ostream &operator<<(std::ostream &stream, const Peng::Vertex &vertex)
{
	stream.write((char *) &vertex, sizeof(vertex));
	return stream;
}

std::istream &operator>>(std::istream &stream, Peng::Vertex &vertex)
{
	stream.read((char *) &vertex, sizeof(vertex));
	return stream;
}
