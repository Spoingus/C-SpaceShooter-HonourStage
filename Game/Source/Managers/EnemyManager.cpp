#include "EnemyManager.h"

void EnemyManager::initialise_enemies(const Model &enemy_model)
{
    std::mt19937 mersenne{std::random_device{}()};
    std::uniform_real_distribution<float> dist{400,2400};
    
    for (int i = 0; i < enemy_count; ++i)
    {
        float my_random_number = dist(mersenne);
        enemy_actors.emplace_back(enemy_model, my_random_number);
    }
}

void EnemyManager::draw_enemies(Shader shader)
{
    for (const auto& enemy : enemy_actors)
    {
        enemy.draw_enemy(shader);
    }
}
