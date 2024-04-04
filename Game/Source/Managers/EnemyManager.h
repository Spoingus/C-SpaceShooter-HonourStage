#pragma once
#include <list>
#include "../ActorTypes/EnemyActor.h"
#include "../../../Engine/Source/Assets/Shader.h"

class EnemyManager{
    EnemyManager() = default;
public:
    EnemyManager(const EnemyManager&) = delete;
    EnemyManager& operator=(const EnemyManager&) = delete;
    EnemyManager(EnemyManager&&) = delete;
    EnemyManager& operator=(EnemyManager&&) = delete;
    
    static std::list<EnemyActor> enemy_actors;
    static int enemy_count = 25;
    
    static void initialise_enemies(const Model &enemy_model);

    static void draw_enemies(Shader shader);

    static EnemyManager& get(){
        static EnemyManager instance;
        return instance;
    }
};
