#ifndef SHADER_H
#define SHADER_H
#pragma once
#include <string>
#include <glm/fwd.hpp>
#include "Geometry.h"

class Shader
{
public:
    virtual ~Shader() = default;
    virtual void apply_shader(glm::mat4 model, Geometry geometry) = 0;

    unsigned int shader_id;
    
    Shader(const std::string& vertex_path, const std::string& fragment_path);
};
#endif
