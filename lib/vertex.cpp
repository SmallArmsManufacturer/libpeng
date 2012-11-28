#include "peng/vertex.hpp"

#include <iostream>

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
