#define FBXSDK_NEW_API
#include <fbxsdk.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "peng/mesh.hpp"
#include "peng/version.hpp"

using namespace std;

namespace {
    vector<FbxMesh *> meshes;
    
    void ProcessNode(FbxNode *node)
    {
        if (node->GetNodeAttribute() && node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh) {
            meshes.push_back((FbxMesh *) node->GetNodeAttribute());
        }
        if (node->GetChildCount() > 0)
            for (int i = 0; i < node->GetChildCount(); i++)
                ProcessNode(node->GetChild(i));
    }
}

int main(int argc, const char *argv[])
{
    if (argc != 3) {
        cout << argv[0] << " v" << Peng::VERSION << endl;
        cout << "Usage: " << argv[0] << " input-file output-file" << endl;
        return EXIT_SUCCESS;
    }
    
    const char *input = argv[1];
    const char *output = argv[2];
    
    FbxManager *manager = FbxManager::Create();
    
    FbxIOSettings *ios = FbxIOSettings::Create(manager, IOSROOT);
    manager->SetIOSettings(ios);
    
    FbxImporter *importer = FbxImporter::Create(manager, "");
    if (!importer->Initialize(input, -1, manager->GetIOSettings())) {
        cerr << importer->GetLastErrorString() << endl;
        return EXIT_FAILURE;
    }
    
    FbxScene *scene = FbxScene::Create(manager, "scene");
    importer->Import(scene);
    importer->Destroy();
    
    ProcessNode(scene->GetRootNode());

    if (meshes.size() != 1)
    {
        cerr << "Error: This model contains " << meshes.size() << " meshes. Currently only models with exactly 1 mesh are supported." << endl;
        return EXIT_FAILURE;
    }
    
    Peng::Mesh mesh;
    FbxMesh *fbxMesh = meshes[0];

    // Triangulate the mesh if necessary
    if (!fbxMesh->IsTriangleMesh())
    {
        FbxGeometryConverter converter ( manager );
        fbxMesh = converter.TriangulateMesh ( fbxMesh );
    }

    int num_triangles = fbxMesh->GetPolygonCount();
    FbxVector4 *fbxControlPoints = fbxMesh->GetControlPoints();
    mesh.triangles.resize(num_triangles);
    mesh.vertices.resize(num_triangles * 3);

    for (int i = 0; i < num_triangles; ++i)
    {
        mesh.triangles[i].indices[0] = i * 3;
        mesh.triangles[i].indices[1] = i * 3 + 1;
        mesh.triangles[i].indices[2] = i * 3 + 2;
        for (unsigned int j = 0; j < 3; ++j)
        {
            FbxVector4 fbxVertex = fbxControlPoints[fbxMesh->GetPolygonVertex(i, j)];
            FbxVector4 fbxNormal;
            fbxMesh->GetPolygonVertexNormal(i, j, fbxNormal);
            fbxNormal.Normalize();
            mesh.vertices[i * 3 + j].position[0] = (float) fbxVertex[0];
            mesh.vertices[i * 3 + j].position[1] = (float) fbxVertex[1];
            mesh.vertices[i * 3 + j].position[2] = (float) fbxVertex[2];
            mesh.vertices[i * 3 + j].normal[0] = (float) fbxNormal[0];
            mesh.vertices[i * 3 + j].normal[1] = (float) fbxNormal[1];
            mesh.vertices[i * 3 + j].normal[2] = (float) fbxNormal[2];
        }
    }

    ofstream out(output);
    out << mesh;
    out.close();
    
    manager->Destroy();
    
    return EXIT_SUCCESS;
}
