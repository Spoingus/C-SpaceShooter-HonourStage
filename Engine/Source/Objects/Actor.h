#pragma once
#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

class Actor
{
public:
    Actor(const std::string& actor_name, const glm::vec3& actor_position, const glm::quat& actor_orientation)
        : actor_name_(actor_name),
          actor_position_(actor_position),
          actor_orientation_(actor_orientation)
    {
    }

    std::string get_name(){return actor_name_;}
    glm::vec3 get_position() const {return actor_position_;}

private:
    std::string actor_name_;
    glm::vec3 actor_position_;
    glm::quat actor_orientation_;
};
