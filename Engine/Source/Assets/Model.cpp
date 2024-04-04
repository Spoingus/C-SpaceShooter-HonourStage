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
    directory = path.substr(0, path.find_last_of('/'));
    if(!resource_manager.model_loaded(directory))
        loadModel(path);
    else
    {
        std::cout << "ERROR::Existing Model At::" << path << "\n";
    }
        
}

void Model::Draw(const Shader& shader) const
{
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(shader);
}

void Model::loadModel(std::string const& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << '\n';
        return;
    }
    processNode(scene->mRootNode, scene);
}

void Model::processNode(const aiNode* node, const aiScene* scene)
{
    auto& resource_manager = ResourceManager::get();
    
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(resource_manager.processMesh(mesh, scene, directory));
    }
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
    resource_manager.model_to_map(this, directory);
}
