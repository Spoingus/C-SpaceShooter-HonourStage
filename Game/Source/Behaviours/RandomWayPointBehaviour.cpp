#include "RandomWayPointBehaviour.h"
#include <glm/gtc/random.hpp>

RandomWayPointBehaviour::~RandomWayPointBehaviour() = default;

void RandomWayPointBehaviour::enter()
{
    const glm::vec3 random_vec = glm::vec3(glm::gaussRand(0.0f, 1.0f), glm::gaussRand(0.0f, 1.0f), glm::gaussRand(0.0f, 1.0f));
    current_target = glm::normalize(random_vec) * 3000.0f;
}

void RandomWayPointBehaviour::execute(Actor* actor, glm::vec3 target_pos, float delta_time)
{
}


void RandomWayPointBehaviour::exit()
{
}
