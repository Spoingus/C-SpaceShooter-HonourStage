#include "EnemyActor.h"
#include "../../../Engine/Source/Managers/CollisionManager.h"


void EnemyActor::update(float delta_time)
{
    position_ += velocity_ * ship_speed * delta_time;
}

void EnemyActor::enemy_move(Model ground, float delta_time)
{
    if(CollisionManager::check_terrain(ship_speed, ground, position_, collision_radius))
    {
    }
    if(CollisionManager::check_world_sphere(position_,collision_radius,3000.0f))
    {
    }
}

void EnemyActor::draw_enemy(Shader shader) const
{
    auto model = glm::mat4(1.0f);
    model = glm::translate(model, position_);
    model *= glm::mat4_cast(orientation_);
    shader.setMat4("model", model);
    enemy_model.Draw(shader);
}
