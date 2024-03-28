#include "pch.h"
#include "Camera.h"

Camera::Camera()
{
    position_ = glm::vec3(0,0,0);
    orientation_ = normalize(orientation_);
}

void Camera::pitch(float pitch_degrees)
{
    rotate(glm::radians(pitch_degrees), glm::vec3(1.0f, 0.0f, 0.0f));
}

void Camera::yaw(float yaw_degrees)
{
    rotate(glm::radians(yaw_degrees), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::roll(float roll_degrees)
{
    rotate(glm::radians(roll_degrees), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Camera::rotate(float angle_degrees, const glm::vec3& axis)
{
    glm::quat q = glm::angleAxis(glm::radians(angle_degrees), axis);
    rotate(q);
}

void Camera::rotate(const glm::quat& rotation)
{
    orientation_ = rotation * orientation_;
    normalize(orientation_);
}

glm::vec3 Camera::get_position() const
{
    return position_;
}

glm::quat Camera::get_orientation() const
{
    return orientation_;
}

glm::vec3 Camera::get_forward() const
{
    return glm::conjugate(orientation_) * glm::vec3(0.0f, 0.0f, -1.0f);
}

glm::vec3 Camera::get_left() const
{
    return glm::conjugate(orientation_) * glm::vec3(-1.0, 0.0f, 0.0f);
}

glm::vec3 Camera::get_up() const
{
    return glm::conjugate(orientation_) * glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::move_forward(float movement)
{
    position_ += get_forward() * movement;
}

void Camera::move_left(float movement)
{
    position_ += get_left() * movement;
}

void Camera::move_up(float movement)
{
    position_ += get_up() * movement;
}

void Camera::move_world_up(float movement)
{
    position_ += glm::vec3(0.0f, 1.0f, 0.0f) * movement;
}

glm::mat4 Camera::get_view_matrix() const
{
    glm::mat4 viewMatrix = glm::mat4_cast(orientation_);
    viewMatrix = glm::translate(viewMatrix, -position_);
    return viewMatrix;
}
