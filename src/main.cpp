#include <cstdlib>
#include <iostream>
#include <vector>
#include "peng/mesh.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
	Peng::Mesh mesh;

	mesh.vertices.push_back({{ 0, 1, 0 }, { 0, 0, 1 }});
	mesh.vertices.push_back({{ 1, -1, 0 }, { 0, 0, 1 }});
	mesh.vertices.push_back({{ -1, -1, 0 }, { 0, 0, 1 }});

	mesh.triangles.push_back({{ 0, 1, 2 }});

	cout << mesh;
	
	return EXIT_SUCCESS;
}
