#include "PlayerActor.h"
#include "../../../Engine/Source/Managers/CollisionManager.h"
#include "../Managers/EnemyManager.h"

void PlayerActor::weapon_fire()
{
    if(weapon_delay == 120)
    {
        weapon_delay = 119;
        glm::vec3 temp_position = player_camera.get_position() - player_camera.get_up() * 1.6f;
        
        if(gun_one)
            temp_position -= player_camera.get_left();
        else
            temp_position += player_camera.get_left();
        
        temp_position += player_camera.get_forward() * 10.0f;
        
        EnemyManager::get().current_projectiles.push_back(*new PlayerProjectile(player_camera.get_forward(),
            temp_position,glm::conjugate(player_camera.get_orientation())));
    }
    gun_one = !gun_one;
}

void PlayerActor::update_projectiles(float delta_time)
{
    if(weapon_delay < 120) weapon_delay--;
    if(weapon_delay == 0) weapon_delay = 120;
    auto &projectiles = EnemyManager::get().current_projectiles;
    if(!projectiles.empty())
        for (auto& projectile : projectiles)
        {
            projectile.move_projectile(projectile.projectile_speed);// * delta_time);
            if(CollisionManager::check_world_sphere(projectile.get_position(),projectile.projectile_radius,3000))
                projectile.has_hit = true;
        }
            
}

void PlayerActor::render_projectiles(const Shader &shader) const
{
    const auto &projectiles = EnemyManager::get().current_projectiles;
    if(!projectiles.empty())
    {
        for (const auto& projectile : projectiles)
        {
            if(!projectile.has_hit)
            {
                auto model = glm::mat4(1.0f);
                            model = glm::translate(model, projectile.get_position());
                            model *= glm::mat4_cast(projectile.get_orientation());
                            shader.setMat4("model", model);
                            projectile_model.Draw(shader);
            }
        }
    }
}

void PlayerActor::increment_ship_speed()
{
    ship_speed += 0.005f;
    turn_speed -= 0.05f;
    if(ship_speed > player_max_speed)
        ship_speed = player_max_speed;
    if(turn_speed < 1.0f)
        turn_speed = 1.0f;
}

void PlayerActor::lower_ship_speed()
{
    ship_speed -= 0.005f;
    turn_speed += 0.05f;
    if(ship_speed < 0.0f)
        ship_speed = 0.0f;
    if(turn_speed > player_max_turn)
        turn_speed = player_max_turn;
}

void PlayerActor::player_move(const Model& ground, float delta_time)
{
    if(CollisionManager::check_terrain(ship_speed, ground, player_camera.get_position(),player_radius))
    {
        player_camera.move_world_up(ship_speed);// * delta_time);
        player_camera.pitch(-150.0f);// * delta_time);
    }
    if(CollisionManager::check_world_sphere(player_camera.get_position(),player_radius,3000.0f))
    {
        ship_speed *= -1;
    }
    player_camera.move_forward(ship_speed);// * delta_time);
}

void PlayerActor::draw_player(Shader shader) const
{
    //render the ship
    glm::mat4 ship_model = glm::mat4(1);
    ship_model = glm::translate(ship_model, player_camera.get_position());
    ship_model *= glm::mat4_cast(glm::conjugate(player_camera.get_orientation()));
    shader.setMat4("model", ship_model);
    player_model.Draw(shader);
}
