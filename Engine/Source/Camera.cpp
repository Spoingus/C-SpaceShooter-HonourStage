#include "pch.h"
#include "Camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>


Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float roll):
    Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(speed), MouseSensitivity(sensitivity)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    Roll = roll;
    
    updateView();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch, float roll):
    Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(speed), MouseSensitivity(sensitivity)
{
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    Roll = roll;
    updateView();
}

glm::mat4 Camera::GetViewMatrix()
{
    //return glm::lookAt(Position, Position + WorldFront, Up);
    // You should know the camera move reversely relative to the user input.
    // That's the point of Graphics Camera

    glm::quat reverseOrient = glm::conjugate(Orientation);
    glm::mat4 rot = glm::mat4_cast(reverseOrient);
    glm::mat4 translation = glm::translate(glm::mat4(1.0), -Position);

    return (rot * translation);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    const float velocity = MovementSpeed * deltaTime;
    if (direction == forward)
        Position += Front * velocity;
    if (direction == backward)
        Position -= Front * velocity;
    if (direction == left)
        Yaw -= 2.2f * velocity;
    if (direction == right)
        Yaw += 2.2f * velocity;

    updateView();
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Roll += xoffset;
    Pitch += yoffset;
    /*float f = Roll;
    if(Roll < 0)
        f = Roll * -1;
    f /= 180;
    if(Roll > 0){
        Yaw += yoffset * (1.0 - f) + xoffset * f;
        Pitch += xoffset * (1.0 - f) + yoffset * f;}
    else{
        Yaw += xoffset * (1.0 - f) + yoffset * f;
        Pitch += yoffset * (1.0 - f) + xoffset * f;}*/

    /*/ make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }*/

    // update Front, Right and Up Vectors using the updated Euler angles
    updateView();
}

void Camera::updateView()
{
    /*/Get Roll Matrix
    const auto roll_mat = glm::rotate(glm::mat4(1.0f), glm::radians(Roll), Front);
    // Roll
    glm::quat roll_quat = glm::angleAxis(glm::radians(Roll), glm::vec3(0, 0, 1));
    // Yaw
    glm::quat yaw_quat = glm::angleAxis(glm::radians(-Yaw), glm::vec3(0, 1, 0));
    // Pitch
    glm::quat pitch_quat = glm::angleAxis(glm::radians(Pitch), glm::vec3(1, 0, 0));

    Orientation = roll_quat * yaw_quat * pitch_quat;

    glm::quat qF = Orientation * glm::quat(0, 0, 0, -1) * glm::conjugate(Orientation);
    Front = { qF.x, qF.y, qF.z };
    //Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::cross(Front, Up);*/
    //FPS camera:  RotationX(pitch) * RotationY(yaw)
    //Get Roll Matrix
    //glm::quat roll_mat = glm::rotate(glm::mat4(1.0f), glm::radians(Roll), Front);
    // Roll
    glm::quat qRoll = glm::angleAxis(glm::radians(Roll), normalize(Front));//glm::vec3(0, 0, 1));
    // Yaw
    glm::quat qYaw = glm::angleAxis(glm::radians(-Yaw), glm::vec3(0, 1, 0));
    // Pitch
    glm::quat qPitch = glm::angleAxis(glm::radians(Pitch), glm::vec3(1, 0, 0));
    
    Orientation = qRoll * qYaw * qPitch;
    Orientation = glm::normalize(Orientation);

    glm::quat qF = Orientation * glm::quat(0, 0, 0, -1) * glm::conjugate(Orientation);
    Front = { qF.x, qF.y, qF.z };
    Right = qRoll * glm::normalize(glm::cross(Front, Up));
    Up = qRoll * glm::normalize(glm::cross(Right, Front));

    glm::mat4 rotate = glm::mat4_cast(Orientation);

    glm::mat4 translate = glm::mat4(1.0f);
    translate = glm::translate(translate, -Front);
    
    WorldFront = glm::mat3(glm::inverse(rotate * translate)) * Front;
    //viewMatrix = rotate * translate;
    
}
