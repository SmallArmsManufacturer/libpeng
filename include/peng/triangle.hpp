#pragma once

#include <cstdint>
#include <iosfwd>

namespace Peng
{
	struct Triangle
	{
		uint32_t indices[3];
	};
}

std::ostream &operator<<(std::ostream &stream, const Peng::Triangle &triangle);
std::istream &operator>>(std::istream &stream, Peng::Triangle &triangle);
