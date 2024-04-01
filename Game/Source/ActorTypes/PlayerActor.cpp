#include "PlayerActor.h"

#include "../../../Engine/Source/Camera.h"
#include "../../../Engine/Source/Managers/CollisionManager.h"

void PlayerActor::increment_ship_speed()
{
    ship_speed += 0.1f;
    turn_speed -= 0.05f;
    if(ship_speed > 8.0f)
        ship_speed = 8.0f;
    if(turn_speed < 1.0f)
        turn_speed = 1.0f;
}

void PlayerActor::lower_ship_speed()
{
    ship_speed -= 0.1f;
    turn_speed += 0.05f;
    if(ship_speed < 0.0f)
        ship_speed = 0.0f;
    if(turn_speed > 2.0f)
        turn_speed = 2.0f;
}

void PlayerActor::player_world_check(const Model& ground, float delta_time)
{
    if(CollisionManager::check_terrain(ship_speed, ground, player_camera.get_position(),10.0f))
    {
        player_camera.move_world_up(ship_speed * delta_time);
        player_camera.pitch(-150.0f * delta_time);
    }
    if(CollisionManager::check_world_sphere(player_camera.get_position(),10.0f,3000.0f))
    {
        ship_speed *= -1;
    }
    player_camera.move_forward(ship_speed * delta_time);
}
