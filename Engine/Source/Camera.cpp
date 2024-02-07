#include "pch.h"
#include "Camera.h"

Camera::Camera()
{
    camera_position = glm::vec3(0.0f, 0.0f, 0.0f);
    camera_direction = glm::vec3(0.0f, 0.0f, -90.0f);
    camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
    update_view();
    projection = glm::perspective((glm::radians(120.0f)), 1.0f, 0.1f, 100.0f);
}

Camera::Camera(glm::vec3 camera_pos, glm::vec3 target_pos, float ratio, float near, float far)
{
    radius = 10;
    camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
    camera_position = camera_pos;
    camera_direction = target_pos-camera_pos;
    camera_direction = normalize(camera_direction);
    update_view();
    projection = glm::perspective((glm::radians(120.0f)), ratio, near, far);
}

void Camera::update_view()
{
    target_position = camera_position + camera_direction;
    view = lookAt(camera_position, target_position, camera_up);
}
