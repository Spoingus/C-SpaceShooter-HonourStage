#pragma once
#include "../../../Engine/Source/Objects/Actor.h"
#include "../../Engine/Source/Assets/Shader.h"
#include "../../Engine/Source/Assets/Model.h"
#include "../../Engine/Source/Camera.h"

class PlayerActor : Actor
{
public:
    int player_lives;
    float ship_speed = 0;
    float turn_speed = 0;
    //Camera
    Camera player_camera;
    Model player_model;
    
    PlayerActor(const std::string& actor_name, const glm::vec3& actor_position, const glm::quat& actor_orientation)
        : Actor(actor_name, actor_position, actor_orientation), player_lives(3),
          player_model("Assets/Geometry/Ship/ship.obj")
    {
    }
    void increment_ship_speed();
    void lower_ship_speed();

    void player_world_check(const Model& ground, float delta_time);
    
};
