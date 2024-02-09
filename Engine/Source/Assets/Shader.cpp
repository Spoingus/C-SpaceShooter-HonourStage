#include "pch.h"
#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
/*#include <glad/glad.h>
#include "../Managers/ResourceManager.h"

Shader::Shader(const std::string& vertex_path, const std::string& fragment_path)
{
    shader_id = glad_glCreateProgram();
    glad_glAttachShader(shader_id,resource_manager::load_shader(vertex_path,GL_VERTEX_SHADER));
    glad_glAttachShader(shader_id,resource_manager::load_shader(fragment_path,GL_FRAGMENT_SHADER));
    glad_glLinkProgram(shader_id);
}*/
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    const unsigned int vertex = resource_manager::load_shader(vertexPath,GL_VERTEX_SHADER);
    const unsigned int fragment = resource_manager::load_shader(fragmentPath,GL_FRAGMENT_SHADER);
    
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    resource_manager::shader_compile_errors(ID, "PROGRAM");
    
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}


