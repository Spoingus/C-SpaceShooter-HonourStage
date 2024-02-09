#pragma once
#include <map>
#include <string>
#include <glad/glad.h>
#include "../Assets/Geometry.h"

namespace resource_manager
{
    static std::map<std::string, Geometry> geometry_map;
    static std::map<std::string, unsigned int> texture_map;
    static std::map<std::string, unsigned int> shader_map;
    static std::map<std::string, int> audio_map;

    void remove_all_assets();

    Geometry load_geometry(const std::string& filename);

    unsigned int load_texture(const std::string& filename);

    unsigned int load_shader(const std::string& shader_path, GLenum shader_type);

    unsigned int load_audio(const std::string& filename);

    void shader_compile_errors(unsigned int shader, std::string type);
}
