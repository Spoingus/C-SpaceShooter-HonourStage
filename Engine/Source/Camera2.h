#ifndef CAMERA2_H
#define CAMERA2_H
#include <glm/glm.hpp>
#include "glm/gtc/quaternion.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Camera2 {

private:
    glm::vec3 mPosition = {};
    glm::quat mOrientation = {};

public:
    Camera2()
    {
        mPosition = glm::vec3(0,0,0);
        glm::quat qRoll = glm::angleAxis(glm::radians(0.0f), glm::vec3(0, 0, 1));
        glm::quat qYaw = glm::angleAxis(glm::radians(0.0f), glm::vec3(0, 1, 0));
        glm::quat qPitch = glm::angleAxis(glm::radians(0.0f), glm::vec3(1, 0, 0));
        mOrientation = qRoll * qYaw * qPitch;
        mOrientation = glm::normalize(mOrientation);
    }
    void pitch(float pitchRadians) {
        rotate(pitchRadians, glm::vec3(1.0f, 0.0f, 0.0f));
    }

    void yaw(float yawRadians) {
        rotate(yawRadians, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    void roll(float rollRadians) {
        rotate(rollRadians, glm::vec3(0.0f, 0.0f, 1.0f));
    }

    void turn(float turnRadians) {
        glm::quat q = glm::angleAxis(turnRadians, mOrientation * glm::vec3(0.0f, 1.0f, 0.0f));
        rotate(q);
    }

    void rotate(float angleRadians, const glm::vec3& axis) {
        glm::quat q = glm::angleAxis(angleRadians, axis);
        rotate(q);
    }

    void rotate(const glm::quat& rotation) {
        mOrientation = rotation * mOrientation;
    }

    glm::vec3 getForward() const {
        return glm::conjugate(mOrientation) * glm::vec3(0.0f, 0.0f, -1.0f);
    }

    glm::vec3 getLeft() const {
        return glm::conjugate(mOrientation) * glm::vec3(-1.0, 0.0f, 0.0f);
    }

    glm::vec3 getUp() const {
        return glm::conjugate(mOrientation) * glm::vec3(0.0f, 1.0f, 0.0f);
    }

    void moveForward(float movement) {
        mPosition += getForward() * movement;
    }

    void moveLeft(float movement) {
        mPosition += getLeft() * movement;
    }

    void moveUp(float movement) {
        mPosition += getUp() * movement;
    }

    glm::mat4 getViewMatrix() const {
        glm::mat4 viewMatrix = glm::mat4_cast(mOrientation);
        viewMatrix = glm::translate(viewMatrix, -mPosition);
        return viewMatrix;
    }
};
#endif // CAMERA2_H
