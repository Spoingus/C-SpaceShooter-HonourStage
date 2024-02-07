#include "pch.h"
#include "DefaultShader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void DefaultShader::apply_shader(glm::mat4 model, Geometry geometry)
{
    glUseProgram(shader_id);
    
    glm::vec3 camera_position(0.0f, 0.0f, 3.0f); // -Z is into the screen.		
    glm::vec3 camera_target(0.0f, 0.0f, 0.0f);
    glm::vec3 camera_up(0.0f, 1.0f, 0.0f);
 
    glUniform3f(this->camera_position, camera_position.x, camera_position.y, camera_position.z);
 
    glm::mat4 view = glm::lookAt(camera_position, camera_target, camera_up);
    glUniformMatrix4fv(view_matrix, 1, GL_FALSE, glm::value_ptr(view)); // Uniform: Transfer view matrix to vertex shader.
 
    glm::mat4 projection = glm::perspective(glm::radians(55.0f), 1.0f, 0.1f, 100.0f);
    glUniformMatrix4fv(projection_matrix, 1, GL_FALSE, glm::value_ptr(projection));
}
