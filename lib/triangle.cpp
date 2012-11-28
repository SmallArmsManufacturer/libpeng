#include "peng/triangle.hpp"

#include <iostream>

std::ostream &operator<<(std::ostream &stream, const Peng::Triangle &triangle)
{
	stream.write((char *) &triangle, sizeof(triangle));
	return stream;
}

std::istream &operator>>(std::istream &stream, Peng::Triangle &triangle)
{
	stream.read((char *) &triangle, sizeof(triangle));
	return stream;
}
