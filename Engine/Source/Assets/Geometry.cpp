#include "pch.h"
#include "Geometry.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glad/glad.h>
#include "../Managers/ResourceManager.h"


Geometry::Geometry()
= default;

std::ostream operator<<(const std::ostream& lhs, const std::invalid_argument& rhs);

void Geometry::LoadMesh(const std::string& filename)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile( filename,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_FlipUVs |
        aiProcess_GenNormals |
        aiProcess_JoinIdenticalVertices);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        throw std::invalid_argument( "Assimp scene not loaded correctly." );
    }
	
    mesh_index = scene->mNumMeshes;
    meshes.resize(mesh_index);

    const aiMesh* mesh{};

    for (unsigned int i = 0; i < mesh_index; ++i)
    {
    	// retrieve the directory path of the filepath
    	meshes[i].directory = filename.substr(0, filename.find_last_of('/'));
    	
	    mesh = scene->mMeshes[i];
	    const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        	
	    // Diffuse Texture Loop
	    for (unsigned int i_diffuse = 0; i_diffuse < material->GetTextureCount(aiTextureType_DIFFUSE); ++i_diffuse) // Only using: aiTextureType_DIFFUSE
	    {
		    aiString tex_name;
		    material->GetTexture(aiTextureType_DIFFUSE, i_diffuse, &tex_name);
		    const unsigned int diffuse_handle = resource_manager::load_texture(meshes[i].directory + "/" + tex_name.C_Str());
		    meshes[i].material.diffuse.id = diffuse_handle;
		    meshes[i].material.diffuse.image_name = tex_name.C_Str();
	    }
	    // Bump Texture Loop
	    for (unsigned int i_normal = 0; i_normal < material->GetTextureCount(aiTextureType_NORMALS); ++i_normal) // Only using: aiTextureType_NORMALS
	    {
		    aiString tex_name;
		    material->GetTexture(aiTextureType_NORMALS, i_normal, &tex_name);
		    const unsigned int normal_handle = resource_manager::load_texture(meshes[i].directory + "/" + tex_name.C_Str());
		    meshes[i].material.normal.id = normal_handle;
		    meshes[i].material.normal.image_name = tex_name.C_Str();
	    }
	    // Specular Texture Loop
	    for (unsigned int i_specular = 0; i_specular < material->GetTextureCount(aiTextureType_SPECULAR); ++i_specular) // Only using: aiTextureType_SPECULAR
	    {
		    aiString tex_name;
		    material->GetTexture(aiTextureType_SPECULAR, i_specular, &tex_name);
		    const unsigned int specular_handle = resource_manager::load_texture(meshes[i].directory + "/" + tex_name.C_Str());
		    meshes[i].material.specular.id = specular_handle;
		    meshes[i].material.specular.image_name = tex_name.C_Str();
	    }
	    //Loop through each of the vertices and add their positions / normals / texture coordinates
	    for (unsigned int i_vert = 0; i_vert < mesh->mNumVertices; ++i_vert)
	    {
		    glm::vec3 position{};
		    position.x = mesh->mVertices[i_vert].x;
		    position.y = mesh->mVertices[i_vert].y;
		    position.z = mesh->mVertices[i_vert].z;
		    meshes[i].position.push_back(position);
				
		    glm::vec3 normal{};
		    normal.x = mesh->mNormals[i_vert].x;
		    normal.y = mesh->mNormals[i_vert].y;
		    normal.z = mesh->mNormals[i_vert].z;
		    meshes[i].normal.push_back(normal);

		    if (mesh->HasTextureCoords(0))
		    {
			    glm::vec2 tex_coords{};
			    tex_coords.x = mesh->mTextureCoords[0][i_vert].x;
			    tex_coords.y = mesh->mTextureCoords[0][i_vert].y;
			    meshes[i].tex_coords.push_back(tex_coords);
		    }
		    else
			    meshes[i].tex_coords.emplace_back(0.0f, 0.0f);
	    }
	    //Loop for the indices
	    for (unsigned int i3 = 0; i3 < mesh->mNumFaces; ++i3)
		    for (unsigned int i4 = 0; i4 < mesh->mFaces[i3].mNumIndices; ++i4)										
			    meshes[i].indices.push_back(mesh->mFaces[i3].mIndices[i4]);

        	
	    // VAO,VBO and EBO setup
	    glad_glGenVertexArrays(1, &meshes[i].vao_handle);
	    glad_glGenBuffers(1, &meshes[i].vbo_vertices);
	    glad_glGenBuffers(1, &meshes[i].vbo_normals);
	    glad_glGenBuffers(1, &meshes[i].vbo_texture_coords);
	    glGenBuffers(1, &meshes[i].ebo_handle);
 
	    glBindVertexArray(meshes[i].vao_handle);	
 
	    // Vertex Positions
	    glBindBuffer(GL_ARRAY_BUFFER, meshes[i].vbo_vertices);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * meshes[i].position.size(), &meshes[i].position[0], GL_STATIC_DRAW);
	    glEnableVertexAttribArray(0);
	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
		
	    // Vertex Normals
	    glBindBuffer(GL_ARRAY_BUFFER, meshes[i].vbo_normals);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * meshes[i].normal.size(), &meshes[i].normal[0], GL_STATIC_DRAW);
	    glEnableVertexAttribArray(1);
	    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
 
	    // Texture Coordinates
	    glBindBuffer(GL_ARRAY_BUFFER, meshes[i].vbo_texture_coords);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * meshes[i].tex_coords.size(), meshes[i].tex_coords.data(), GL_STATIC_DRAW);
	    glEnableVertexAttribArray(2);
	    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), static_cast<void*>(nullptr));
		
	    // Indices
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshes[i].ebo_handle);
	    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * meshes[i].indices.size(), meshes[i].indices.data(), GL_STATIC_DRAW);
 
	    glBindVertexArray(0);
    }
}

void Geometry::Draw()
{
	for (const auto mesh : meshes)
	{
		if (mesh.material.diffuse.id > 0) {
			glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, mesh.material.diffuse.id); }
			

		if (mesh.material.normal.id > 0) {
			glActiveTexture(GL_TEXTURE1); glBindTexture(GL_TEXTURE_2D, mesh.material.normal.id); }

		if (mesh.material.specular.id > 0) {
			glActiveTexture(GL_TEXTURE2); glBindTexture(GL_TEXTURE_2D, mesh.material.specular.id); }
 
		glBindVertexArray(mesh.vao_handle);
		glDrawElements(GL_TRIANGLES, (GLsizei)mesh.indices.size(), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
	}
}
