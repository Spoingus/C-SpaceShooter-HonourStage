#pragma once
#include "../../../Engine/Source/Objects/Actor.h"

class EnemyActor : public Actor
{
public:
    float collision_radius = 20.0f;
    
    EnemyActor(const std::string& actor_name, const glm::vec3& actor_position, const glm::quat& actor_orientation)
        : Actor(actor_name, actor_position, actor_orientation)
    {
    }
};
