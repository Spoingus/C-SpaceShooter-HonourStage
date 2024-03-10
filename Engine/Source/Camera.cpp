#include "pch.h"
#include "Camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float roll):
    Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(speed), MouseSensitivity(sensitivity), Zoom(zoom)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    Roll = roll;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch, float roll):
    Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(speed), MouseSensitivity(sensitivity), Zoom(zoom)
{
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    Roll = roll;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    const float velocity = MovementSpeed * deltaTime;
    if (direction == forward)
        Position += Front * velocity;
    if (direction == backward)
        Position -= Front * velocity;
    if (direction == left)
        Roll -= 1.0f * deltaTime;
    if (direction == right)
        Roll += 1.0f * deltaTime;
    const auto roll_mat = glm::rotate(glm::mat4(1.0f), glm::radians(Roll), Front);
    Up = glm::mat3(roll_mat) * Up;

    updateCameraVectors();
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    //Get Roll Matrix
    const auto roll_mat = glm::rotate(glm::mat4(1.0f), glm::radians(Roll), Front);
    Up = glm::mat3(roll_mat) * Up;

    Right = glm::mat3(roll_mat) * normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
    Up = glm::mat3(roll_mat) * normalize(cross(Right, Front));
}
