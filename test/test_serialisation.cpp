#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include "peng/mesh.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
	stringstream s1, s2, s3;
	Peng::Mesh mesh, mesh2;

	mesh.vertices.push_back({{ 0, 1, 0 }, { 0, 0, 1 }});
	mesh.vertices.push_back({{ 1, -1, 0 }, { 0, 0, 1 }});
	mesh.vertices.push_back({{ -1, -1, 0 }, { 0, 0, 1 }});

	mesh.triangles.push_back({{ 0, 1, 2 }});

	s1 << mesh;
	s2 << mesh;
	s2 >> mesh2;
	s3 << mesh2;

	if (s1.str() != s3.str())
	{
		cerr << "test_serialization: Expected s1.str() to equal s3.str()." << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}