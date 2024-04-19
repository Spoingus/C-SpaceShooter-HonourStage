#include "PlayerProjectile.h"


void PlayerProjectile::move_projectile(float movement)
{
    position_ += actor_forward * movement;
}
