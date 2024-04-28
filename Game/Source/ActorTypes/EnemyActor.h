#pragma once
#include <random>
#include <glm/gtc/random.hpp>
#include "../../../Engine/Source/Objects/Actor.h"
#include "../../Engine/Source/Assets/Model.h"

class EnemyActor : public Actor
{
public:
    Model enemy_model;

    float ship_speed = 0.25f;
    float collision_radius = 50.0f;
    bool is_dead = false;
    glm::vec3 target_position;
    
    EnemyActor(Model model, float random_radius)
        : Actor("Enemy", glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::quat(0, 0, 0, 1)),
          enemy_model(std::move(model)), target_position(glm::vec3(0,0,0))
    {
        const auto random_pos = glm::vec3(
            glm::gaussRand(0.0f, 1.0f),
            glm::gaussRand(0.0f, 1.0f),
            glm::gaussRand(0.0f, 1.0f));
        position_ = glm::normalize(random_pos) * random_radius;
    }

    void update(float delta_time);
    glm::vec3 steering_force() const;
    void get_new_roaming_target();
    void draw_enemy(Shader shader) const;
};
