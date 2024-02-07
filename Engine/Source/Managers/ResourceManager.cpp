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
    Texture texture;
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
	return textureID;
}

unsigned int resource_manager::load_shader(const std::string& shader_name, GLenum shader_type)
{
    unsigned int shader;//Creates the shader to check for

    const auto in_map = shader_map.find(shader_name);//Find method returns the end or location of the shader in the map
    if(in_map == shader_map.end())//Checks to see if the shader is already loaded in the map using the map end
    {
        shader = glad_glCreateShader(shader_type);
        
        const std::ifstream shader_file (shader_name);
        const char* shader_source;
        if ( shader_file.is_open() )//While open the file will read everything to the shader source
        {
            std::stringstream b;
            b << shader_file.rdbuf();
            shader_source = b.str().c_str();//Converts it to a const char to be used in the glShaderSource
        }
        glad_glShaderSource(shader,1, &shader_source,nullptr);//Loads the shader source

        glad_glCompileShader(shader);//Compiles the shader
        shader_map.insert({shader_name,shader});//Adds the shader to the map
    }
    else
        shader = in_map->second;//If the shader is in the map the value is set to that to be returned
    
    return shader; // Returns the newly created shader or the existing shader
}
