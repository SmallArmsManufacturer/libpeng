#include "peng/mesh.hpp"

#include <iostream>
#include "peng/version.hpp"

std::ostream &operator<<(std::ostream &stream, const Peng::Mesh &mesh)
{
	// Output the header
	stream.write((char *) &Peng::MAGIC_NUMBER, sizeof(Peng::MAGIC_NUMBER));
	stream.write((char *) &Peng::VERSION, sizeof(Peng::VERSION));

	// Calculate the number of faces and vertices
	uint32_t num_vertices = mesh.vertices.size(), num_triangles = mesh.triangles.size();

	// Output the vertex array
	stream.write((char *) &num_vertices, sizeof(num_vertices));
	stream.write((char *) &mesh.vertices[0], num_vertices * sizeof(Peng::Vertex));

	// Output the triangle array
	stream.write((char *) &num_triangles, sizeof(num_triangles));
	stream.write((char *) &mesh.triangles[0], num_triangles * sizeof(Peng::Triangle));
	
	return stream;
}
