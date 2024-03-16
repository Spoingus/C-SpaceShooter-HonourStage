#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include "glm/gtc/quaternion.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Camera {

private:
    glm::vec3 position_ = {};
    glm::quat orientation_ = {};
    
public:
    
    Camera();

    void pitch(float pitchDegrees);

    void yaw(float yawDegrees);

    void roll(float rollDegrees);

    void rotate(float angleDegrees, const glm::vec3& axis);

    void rotate(const glm::quat& rotation);

    glm::vec3 get_position() const;

    glm::vec3 get_forward() const;

    glm::vec3 get_left() const;

    glm::vec3 get_up() const;

    void moveForward(float movement);

    void moveLeft(float movement);

    void moveUp(float movement);

    glm::mat4 get_view_matrix() const;
};
#endif // CAMERA_H
