#include "PlayerActor.h"

#include "../../../Engine/Source/Camera.h"
#include "../../../Engine/Source/Managers/CollisionManager.h"

void PlayerActor::weapon_fire()
{
    
    projectiles.push_back(*new PlayerProjectile(player_camera.get_forward(), player_camera.get_position(),
                                                  glm::conjugate(player_camera.get_orientation())));
}

void PlayerActor::update_projectiles(float delta_time)
{
    if(!projectiles.empty())
    {
        for (auto& projectile : projectiles)
        {
            projectile.move_projectile(projectile.projectile_speed * delta_time);
        }
    }
}

void PlayerActor::render_projectiles(const Shader &shader) const
{
    if(!projectiles.empty())
    {
            for (auto projectile : projectiles)
            {
                auto model = glm::mat4(1.0f);
                model = glm::translate(model, projectile.get_position());
                model *= glm::mat4_cast(projectile.get_orientation());
                shader.setMat4("model", model);
                projectile_model.Draw(shader);
            }
    }
}

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

void PlayerActor::player_move(const Model& ground, float delta_time)
{
    if(CollisionManager::check_terrain(ship_speed, ground, player_camera.get_position(),player_radius))
    {
        player_camera.move_world_up(ship_speed * delta_time);
        player_camera.pitch(-150.0f * delta_time);
    }
    if(CollisionManager::check_world_sphere(player_camera.get_position(),player_radius,3000.0f))
    {
        ship_speed *= -1;
    }
    player_camera.move_forward(ship_speed * delta_time);
}
