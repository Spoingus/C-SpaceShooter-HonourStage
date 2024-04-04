#pragma once
#include <random>
#include <glm/gtc/random.hpp>

#include "../../../Engine/Source/Objects/Actor.h"
#include "../../Engine/Source/Assets/Model.h"

class EnemyActor : public Actor
{
public:
    Model enemy_model;

    float ship_speed = 2.0f;
    float collision_radius = 20.0f;
    bool seen_player = false;
    
    EnemyActor(Model model, float random_radius)
        : Actor("Enemy", glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::quat(0, 0, 0, 1)),
    enemy_model(std::move(model))
    {
        const auto random_vec = glm::vec3(
            glm::gaussRand(0.0f, 1.0f),
            glm::gaussRand(0.0f, 1.0f),
            glm::gaussRand(0.0f, 1.0f));
        position_ = glm::normalize(random_vec) * random_radius;
    }

    void update(float delta_time);
    //bool has_hit_target() const;
    void enemy_move(Model ground, float delta_time);
    void draw_enemy(Shader shader) const;
};
