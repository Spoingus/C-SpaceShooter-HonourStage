#pragma once
#include <list>
#include "../ActorTypes/EnemyActor.h"
#include "../../../Engine/Source/Assets/Shader.h"
#include "../../../Engine/Source/Assets/Model.h"
#include "../ActorTypes/PlayerActor.h"
#include "../ActorTypes/PlayerProjectile.h"

class EnemyManager{
    EnemyManager() = default;
public:
    EnemyManager(const EnemyManager&) = delete;
    EnemyManager& operator=(const EnemyManager&) = delete;
    EnemyManager(EnemyManager&&) = delete;
    EnemyManager& operator=(EnemyManager&&) = delete;

    std::mt19937 mersenne{std::random_device{}()};
    std::uniform_real_distribution<float> initial_dist{2400,2800};
    std::uniform_real_distribution<float> dist{200,2800};
    
    std::list<EnemyActor> enemy_actors;
    std::list<PlayerProjectile> current_projectiles;
    int enemy_count = 50;
    
    void initialise_enemies(const Model &enemy_model);
    float get_random_world_float();
    void update_enemies(float delta_time, const glm::vec3 &player_pos);
    void draw_enemies(Shader shader) const;

    static EnemyManager& get(){
        static EnemyManager instance;
        return instance;
    }
};
