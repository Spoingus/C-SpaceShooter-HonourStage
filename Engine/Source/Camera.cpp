#include "pch.h"
#include "Camera.h"

Camera::Camera()
{
    position_ = glm::vec3(0,0,0);
    orientation_ = normalize(orientation_);
}

void Camera::pitch(float pitchDegrees)
{
    rotate(glm::radians(pitchDegrees), glm::vec3(1.0f, 0.0f, 0.0f));
}

void Camera::yaw(float yawDegrees)
{
    rotate(glm::radians(yawDegrees), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::roll(float rollDegrees)
{
    rotate(glm::radians(rollDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Camera::rotate(float angleDegrees, const glm::vec3& axis)
{
    glm::quat q = glm::angleAxis(glm::radians(angleDegrees), axis);
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

void Camera::moveForward(float movement)
{
    position_ += get_forward() * movement;
}

void Camera::moveLeft(float movement)
{
    position_ += get_left() * movement;
}

void Camera::moveUp(float movement)
{
    position_ += get_up() * movement;
}

glm::mat4 Camera::get_view_matrix() const
{
    glm::mat4 viewMatrix = glm::mat4_cast(orientation_);
    viewMatrix = glm::translate(viewMatrix, -position_);
    return viewMatrix;
}
