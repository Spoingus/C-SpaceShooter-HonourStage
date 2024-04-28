#include "EnemyActor.h"
#include "../../../Engine/Source/Managers/CollisionManager.h"
#include "../Managers/EnemyManager.h"


void EnemyActor::update(float delta_time)
{
    orientation_ = glm::quatLookAt(velocity_,glm::vec3(0,1,0));
    velocity_ += steering_force() * ship_speed;
    velocity_ = glm::clamp(velocity_,-ship_speed,ship_speed);
    position_ += velocity_;// * delta_time;

    if(CollisionManager::check_spheres(position_,collision_radius,target_position,0.0f))
    {
        get_new_roaming_target();
    }
}

glm::vec3 EnemyActor::steering_force() const
{
    const glm::vec3 desired_velocity = target_position - position_;
    return (desired_velocity - velocity_) / 5.0f;
}

void EnemyActor::get_new_roaming_target()
{
    const auto random_target = glm::vec3(
            glm::gaussRand(0.0f, 1.0f),
            glm::gaussRand(0.0f, 1.0f),
            glm::gaussRand(0.0f, 1.0f));
    target_position = glm::normalize(random_target) * EnemyManager::get().get_random_world_float();
}

void EnemyActor::draw_enemy(Shader shader) const
{
    if(!is_dead){
        auto model = glm::mat4(1.0f);
            model = glm::translate(model, position_);
            model *= glm::mat4_cast(orientation_);
            shader.setMat4("model", model);
            enemy_model.Draw(shader);
    }
}
