#include "EnemyManager.h"

#include "../../../Engine/Source/Managers/CollisionManager.h"

void EnemyManager::initialise_enemies(const Model &enemy_model)
{
    for (int i = 0; i < enemy_count; ++i)
        enemy_actors.emplace_back(enemy_model, initial_dist(mersenne));
}

float EnemyManager::get_random_world_float()
{
    return dist(mersenne);
}

void EnemyManager::update_enemies(float delta_time, const glm::vec3 &player_pos)
{
    for (auto &enemy : enemy_actors)
    {
        if(!enemy.is_dead)
        {
            const auto distance = glm::distance(player_pos, enemy.get_position());
            if(distance < 1000)
                enemy.target_position = player_pos;

            for (auto &projectile : current_projectiles)
            {
                if(!projectile.has_hit &&
                    CollisionManager::check_spheres(enemy.get_position(),enemy.collision_radius,projectile.get_position(),projectile.projectile_radius))
                {
                    enemy.is_dead = true; projectile.has_hit = true;
                }
            }
            enemy.update(delta_time);
        }
    }
}

void EnemyManager::draw_enemies(Shader shader) const
{
    for (const auto& enemy : enemy_actors)
        enemy.draw_enemy(shader);
}
