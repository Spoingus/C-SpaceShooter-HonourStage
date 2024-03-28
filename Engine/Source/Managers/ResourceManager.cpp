#include "pch.h"
#include "ResourceManager.h"
#include <fstream>
#include <sstream>
#define STB_IMAGE_IMPLEMENTATION
#include <assimp/postprocess.h>

#include "stb_image.h"
#include "../Assets/Model.h"

/*void ResourceManager::remove_all_assets()
{
    model_map.clear();
    texture_map.clear();
    shader_map.clear();
}*/

Mesh ResourceManager::processMesh(aiMesh* mesh, const aiScene* scene, const std::string &directory)
{
	// data to fill
    std::vector<Vertex> vertices; std::vector<unsigned int> indices; std::vector<Texture> textures;

    // walk through each of the mesh's vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; //Placeholder vector
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
        // normals
        if (mesh->HasNormals()) {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;}
    	
        if(mesh->mTextureCoords[0]){
            glm::vec2 vec;
        	//Texture-Coordinates
            vec.x = mesh->mTextureCoords[0][i].x; 
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.tex_coords = vec;
            // tangent
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.tangent = vector;
            // bi_tangent
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.bi_tangent = vector;}
        else
            vertex.tex_coords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);}
	
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);        
    }
    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	
    std::vector<Texture> diffuse_maps = load_material_textures(material, aiTextureType_DIFFUSE, "texture_diffuse", directory);
    textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());
	
    std::vector<Texture> specular_maps = load_material_textures(material, aiTextureType_SPECULAR, "texture_specular", directory);
    textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());
	
    std::vector<Texture> normal_maps = load_material_textures(material, aiTextureType_NORMALS, "texture_normal", directory);
    textures.insert(textures.end(), normal_maps.begin(), normal_maps.end());
	
    std::vector<Texture> height_maps = load_material_textures(material, aiTextureType_HEIGHT, "texture_height", directory);
    textures.insert(textures.end(), height_maps.begin(), height_maps.end());
	
	aiColor3D color(0.f,0.f,0.f);
	material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
	
	auto new_mesh = Mesh(vertices, indices, textures); new_mesh.diffuse = glm::vec3(color.r,color.g,color.b);
	return new_mesh;
}

bool ResourceManager::model_loaded(const std::string& directory)
{
	const auto in_map = model_map.find(directory);
	if(in_map != model_map.end())
	{
		return true;
	}
	return false;
}

void ResourceManager::model_to_map(Model *model, const std::string& directory)
{
	model_map.insert({directory, *model});
}

std::vector<Mesh> ResourceManager::get_existing_meshes(const std::string& directory)
{
	return model_map.at(directory).meshes;
}

std::vector<Texture> ResourceManager::load_material_textures(const aiMaterial* mat, const aiTextureType type, const std::string& type_name, const std::string& directory)
{
	std::vector<Texture> textures;
	for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		
		bool skip = false;
		const auto in_map = texture_map.find(directory);
		if(in_map != texture_map.end())
		{
			skip = true;
		}
		if(!skip)
		{
			Texture texture;
			texture.id = texture_from_file(str.C_Str(), directory);
			texture.type = type_name;
			texture.path = str.C_Str();
			textures.push_back(texture);
			texture_map.insert({directory, texture});
		}
	}
	return textures;
}

unsigned int ResourceManager::texture_from_file(const char* path, const std::string& directory)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nr_components;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nr_components, 0);
	if (data)
	{
		GLenum format;
		if (nr_components == 1)
			format = GL_RED;
		else if (nr_components == 3)
			format = GL_RGB;
		else if (nr_components == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << '\n';
		stbi_image_free(data);
	}

	return textureID;
}

unsigned int ResourceManager::load_shader(const std::string& shader_path, GLenum shader_type)
{
    std::string s_shader_code;
    std::ifstream shader_file;
	
    shader_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        shader_file.open(shader_path);
        std::stringstream shader_stream;
        shader_stream << shader_file.rdbuf();
        shader_file.close();
        s_shader_code   = shader_stream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "SHADER_ERROR: FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }
    const char* c_shader_code = s_shader_code.c_str();

    const unsigned int shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &c_shader_code, nullptr);
    glCompileShader(shader);
    shader_compile_errors(shader, shader_path);

    shader_map.insert({shader_path, shader});
	return shader;
}

void ResourceManager::shader_compile_errors(unsigned shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
