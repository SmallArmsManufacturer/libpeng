#include <assimp.hpp>
#include <aiMesh.h>
#include <aiScene.h>
#include <aiPostProcess.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "peng/mesh.hpp"
#include "peng/version.hpp"

using namespace std;

int main(int argc, const char *argv[])
{
    if (argc != 3) {
        cout << argv[0] << " v" << Peng::VERSION << endl;
        cout << "Usage: " << argv[0] << " input-file output-file" << endl;
        return EXIT_SUCCESS;
    }
    
    const char *input = argv[1];
    const char *output = argv[2];
    
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(input, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

    if (!scene) {
        cerr << "Error: Unable to load geometry from " << input << endl;
        return EXIT_FAILURE;
    }

    Peng::Mesh mesh;

    if (scene->mNumMeshes != 1) {
        cerr << "Error: Only scenes with exactly 1 mesh are supported." << endl;
        return EXIT_FAILURE;
    }

    aiMesh *ai_mesh = scene->mMeshes[0];

    // Vertices
    mesh.vertices.resize(ai_mesh->mNumVertices);
    for (int i = 0; i < ai_mesh->mNumVertices; ++i) {
        const aiVector3D &p = ai_mesh->mVertices[i];
        const aiVector3D &n = ai_mesh->mNormals[i];
        Peng::Vertex &vertex = mesh.vertices[i];
        vertex.position[0] = p.x;
        vertex.position[1] = p.y;
        vertex.position[2] = p.z;
        vertex.normal[0] = n.x;
        vertex.normal[1] = n.y;
        vertex.normal[2] = n.z;
    }

    // Triangles
    mesh.triangles.resize(ai_mesh->mNumFaces);
    for (int i = 0; i < ai_mesh->mNumFaces; ++i) {
        const aiFace &face = ai_mesh->mFaces[i];
        Peng::Triangle &triangle = mesh.triangles[i];
        triangle.indices[0] = face.mIndices[0];
        triangle.indices[1] = face.mIndices[1];
        triangle.indices[2] = face.mIndices[2];
    }

    ofstream out(output);
    out << mesh;
    out.close();
    
    return EXIT_SUCCESS;
}
