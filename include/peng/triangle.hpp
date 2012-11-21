#pragma once

#include <iosfwd>

namespace Peng
{
	struct Triangle
	{
		int indices[3];
	};
}

std::ostream &operator<<(std::ostream &stream, const Peng::Triangle &triangle);
