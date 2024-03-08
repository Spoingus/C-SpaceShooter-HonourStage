#include "pch.h"
#include "Model.h"
#include <glm/glm.hpp>
#include <stb_image.h>
#include <assimp/postprocess.h>
#include <../../Engine/Source/Managers/ResourceManager.h>
#include <fstream>
#include <iostream>

Model::Model(std::string const& path, bool gamma): gamma_correction(gamma)
{
    auto& resource_manager = ResourceManager::get();
    // retrieve the directory path of the filepath
    directory = path.substr(0, path.find_last_of('/'));
    if(!resource_manager.model_loaded(directory))
        loadModel(path);
    else
        std::cout << "ERROR::Existing Model At::" << path << "\n";
}

void Model::Draw(const Shader& shader) const
{
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(shader);
}

void Model::loadModel(std::string const& path)
{
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << '\n';
        return;
    }
    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);
}

void Model::processNode(const aiNode* node, const aiScene* scene)
{
    auto& resource_manager = ResourceManager::get();
    // process each mesh located at the current node
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(resource_manager.processMesh(mesh, scene, directory));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
    //After processing each mesh and child node, we add the model to the resource_manager
    resource_manager.model_to_map(this, directory);
}
