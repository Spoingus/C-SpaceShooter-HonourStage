#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "Shader.h"

class DefaultShader: Shader
{
public:
    unsigned int view_matrix;
    unsigned int projection_matrix;
    unsigned int camera_position;
    
    DefaultShader() : Shader("../Shaders/Vertex/DefaultVertex.vert", "../Shaders/Fragment/DefaultFragment.vert")
    {
        view_matrix = glad_glGetUniformLocation(shader_id, "view");
        projection_matrix = glad_glGetUniformLocation(shader_id, "projection");
        camera_position = glad_glGetUniformLocation(shader_id, "camera_position");
    }

    void apply_shader(glm::mat4 model, Geometry geometry) override;
};
