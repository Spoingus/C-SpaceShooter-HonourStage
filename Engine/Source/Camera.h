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

    void pitch(float pitch_degrees);

    void yaw(float yaw_degrees);

    void roll(float roll_degrees);

    void rotate(float angle_degrees, const glm::vec3& axis);

    void rotate(const glm::quat& rotation);

    glm::vec3 get_position() const;

    glm::quat get_orientation() const;

    glm::vec3 get_forward() const;

    glm::vec3 get_left() const;

    glm::vec3 get_up() const;

    void move_forward(float movement);

    void move_left(float movement);

    void move_up(float movement);

    void move_world_up(float movement);

    glm::mat4 get_view_matrix() const;
};
#endif // CAMERA_H
