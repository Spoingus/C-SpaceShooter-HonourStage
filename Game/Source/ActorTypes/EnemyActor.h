#pragma once
#include "../../../Engine/Source/Objects/Actor.h"

class EnemyActor : public Actor
{
public:
    float collision_radius = 20.0f;
    //bool seen_player = false;
    //glm::vec3 target;
    //float target_radius;
    
    EnemyActor(const std::string& actor_name, const glm::vec3& actor_position, const glm::quat& actor_orientation)
        : Actor(actor_name, actor_position, actor_orientation)//, target(glm::vec3(0, 0, 0)), target_radius(0)
    {
    }

    //void update(glm::vec3 &player_position, float player_radius);
    //bool has_hit_target() const;
    //void draw_enemy(Shader &shader);
};
