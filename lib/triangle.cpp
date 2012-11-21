#include "peng/triangle.hpp"

#include <iostream>

static_assert(std::is_pod<Peng::Triangle>::value, "Peng::Triangle must be a POD type.");

std::ostream &operator<<(std::ostream &stream, const Peng::Triangle &triangle)
{
	stream.write((char *) &triangle, sizeof(triangle));
	return stream;
}
