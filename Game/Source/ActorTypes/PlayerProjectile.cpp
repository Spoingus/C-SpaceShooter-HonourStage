//#include "../../../Engine/Source/Managers/CollisionManager.h"
#include "PlayerProjectile.h"
#include "EnemyActor.h"


void PlayerProjectile::move_projectile(float movement)
{
    actor_position_ += actor_forward * movement;
}

void PlayerProjectile::check_hit_enemy(EnemyActor enemy)
{
    //CollisionManager::check_spheres(actor_position_,projectile_radius,enemy.get_position(),enemy.collision_radius);
}
