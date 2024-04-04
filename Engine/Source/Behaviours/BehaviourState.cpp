#include "pch.h"
#include "BehaviourState.h"

glm::vec3 BehaviourState::get_steering_force(const Actor actor, const glm::vec3 target_pos)
{
    const glm::vec3 desired_velocity = target_pos - actor.get_position();
    return desired_velocity - actor.get_velocity();
}
