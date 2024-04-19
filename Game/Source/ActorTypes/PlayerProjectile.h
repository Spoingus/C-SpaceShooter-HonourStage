#pragma once
#include "EnemyActor.h"
#include "../../../Engine/Source/Objects/Actor.h"
#include "../../Engine/Source/Assets/Model.h"

class PlayerProjectile : public Actor
{
public:

    bool has_hit = false;
    float projectile_speed = 3.4f;
    float projectile_radius = 50.0f;
    glm::vec3 actor_forward;
    
    PlayerProjectile(const glm::vec3 actor_forward,const glm::vec3& actor_position, const glm::quat& actor_orientation)
        : Actor("Player Projectile", actor_position, glm::vec3(0,0,0), actor_orientation), actor_forward(actor_forward)
    {
    }

    void move_projectile(float movement);
};
