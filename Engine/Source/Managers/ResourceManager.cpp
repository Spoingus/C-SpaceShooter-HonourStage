#include "pch.h"
#include "ResourceManager.h"
#include <fstream>
#include <sstream>
#include "..//Assets/Geometry.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void resource_manager::remove_all_assets()
{
    geometry_map.clear();
    texture_map.clear();
    shader_map.clear();
    audio_map.clear();
}

Geometry resource_manager::load_geometry(const std::string& filename)
{
    Geometry geometry;
    
    const auto in_map = geometry_map.find(filename);//Find method returns the end or location of the mesh in the map
    if(in_map == geometry_map.end())//Checks to see if the mesh is already loaded in the map using the map end
    {
        geometry.LoadMesh(filename);
        geometry_map.insert({filename,geometry});
    }
    
    return geometry;
}

unsigned int resource_manager::load_texture(const std::string& filename)
{
	// load and create a texture
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	// set the texture wrapping parameters / filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else { std::cout << "Failed to load texture:" << std::endl << "\n" << stbi_failure_reason(); }
	stbi_image_free(data);

	texture_map.insert({filename, texture});
	return texture;
    /*Texture texture;
	unsigned int textureID;
    
    const auto in_map = texture_map.find(filename);
    if(in_map == texture_map.end())
    {
	    const std::size_t position = filename.find_last_of('\\');
	    const std::string filepath = "Textures\\" + filename.substr(position + 1);
 
		int width, height, channels;
		unsigned char* image_data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
    	
		glGenTextures(1, &textureID);
 
		if (image_data)
		{
			GLenum format{};
 
			if (channels == 1)
				format = GL_RED;
			else if (channels == 3)
				format = GL_RGB;
			else if (channels == 4)
				format = GL_RGBA;
 
			glBindTexture(GL_TEXTURE_2D, textureID);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
 
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image_data);
			glGenerateMipmap(GL_TEXTURE_2D);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			std::cout << "Image loaded successfully: " << filename << "\n";
		}
		else
		{ stbi_image_free(image_data); std::cout << "Image loading failed: " << filename << "\n"; }
    }
	texture_map.insert({filename, textureID});
	return textureID;*/
}

unsigned int resource_manager::load_shader(const std::string& shader_path, GLenum shader_type)
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

void resource_manager::shader_compile_errors(unsigned shader, std::string type)
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
