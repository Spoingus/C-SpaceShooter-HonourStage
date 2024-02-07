#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    glm::mat4 view, projection;
    glm::vec3 camera_position, camera_direction, camera_up, target_position;
    int radius;
    
    Camera();

    Camera(glm::vec3 camera_pos, glm::vec3 target_pos, float ratio, float near, float far); 

    void update_view();
};
