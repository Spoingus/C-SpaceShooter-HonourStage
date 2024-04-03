#pragma once
#include "EnemyActor.h"
#include "../../../Engine/Source/Objects/Actor.h"
#include "../../Engine/Source/Assets/Model.h"

class PlayerProjectile : public Actor
{
public:

    float projectile_speed = 20.0f;
    float projectile_radius = 5.0f;
    glm::vec3 actor_forward;
    
    PlayerProjectile(const glm::vec3 actor_forward,const glm::vec3& actor_position, const glm::quat& actor_orientation)
        : Actor("Player Projectile", actor_position, actor_orientation), actor_forward(actor_forward)
    {
    }

    void move_projectile(float movement);
    void check_hit_enemy(EnemyActor enemy);
};
