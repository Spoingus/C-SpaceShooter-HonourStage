#pragma once
#include <list>

#include "PlayerProjectile.h"
#include "../../../Engine/Source/Objects/Actor.h"
#include "../../Engine/Source/Assets/Shader.h"
#include "../../Engine/Source/Assets/Model.h"
#include "../../Engine/Source/Camera.h"

class PlayerActor : public Actor
{
public:
    friend class EnemyManager;
    
    int player_lives;
    float player_max_speed = 1.2f;
    float player_max_turn = 2;
    float roll_speed = 10;
    float ship_speed = 0;
    float turn_speed = 0;
    float player_radius = 10.0f;
    int weapon_delay = 120;
    bool gun_one = true;
    //Camera
    Camera player_camera;
    Model player_model;
    Model projectile_model;
    
    PlayerActor(const glm::vec3& actor_position, const glm::quat& actor_orientation)
        : Actor("Player Actor", actor_position, glm::vec3(0,0,0), actor_orientation), player_lives(3),
          player_model("Assets/Geometry/Ship/ship.obj"), projectile_model("Assets/Geometry/Projectile/Projectile.obj")
    {
    }

    void weapon_fire();
    void update_projectiles(float delta_time);
    void render_projectiles(const Shader &shader) const;

    void increment_ship_speed();
    void lower_ship_speed();

    void player_move(const Model& ground, float delta_time);
    void draw_player(Shader shader) const;
    
};
