#pragma once
#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

class Actor
{
public:
    Actor(const std::string& name, const glm::vec3& position, const glm::vec3 velocity, const glm::quat& orientation)
        : name_(name),
    position_(position),
    velocity_(velocity),
    orientation_(orientation)
    {
    }

    std::string get_name(){return name_;}
    glm::vec3 get_position() const {return position_;}
    glm::vec3 get_velocity() const {return velocity_;}
    glm::quat get_orientation() const {return orientation_;}

protected:
    std::string name_;
    glm::vec3 position_;
    glm::vec3 velocity_;
    glm::quat orientation_;
};
