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

std::istream &operator>>(std::istream &stream, Peng::Mesh &mesh) throw(Peng::InvalidMeshException, Peng::VersionMismatchException)
{
	// Ensure that this is a valid .peng file by reading and checking the magic number
	Peng::magic_number_t magic_number;
	stream.read((char *) &magic_number, sizeof(magic_number));
	if (magic_number != Peng::MAGIC_NUMBER)
		throw Peng::InvalidMeshException();

	// Ensure that the version of this .peng file matches the current version of libpeng
	Peng::version_t version;
	stream.read((char *) &version, sizeof(version));
	if (version != Peng::VERSION)
		throw Peng::VersionMismatchException();

	// Read in the number of vertices
	uint32_t num_vertices;
	stream.read((char *) &num_vertices, sizeof(num_vertices));

	// Read in the vertex array
	mesh.vertices = std::vector<Peng::Vertex>(num_vertices);
	stream.read((char *) &mesh.vertices[0], num_vertices * sizeof(Peng::Vertex));

	// Read in the number of triangles
	uint32_t num_triangles;
	stream.read((char *) &num_triangles, sizeof(num_triangles));

	// Read in the triangle array
	mesh.triangles = std::vector<Peng::Triangle>(num_triangles);
	stream.read((char *) &mesh.triangles[0], num_triangles * sizeof(Peng::Triangle));

	return stream;
}
