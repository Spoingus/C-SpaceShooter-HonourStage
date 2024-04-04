#pragma once
#include <glm/vec3.hpp>

#include "../../../Engine/Source/Behaviours/BehaviourState.h"

class Actor;

class RandomWayPointBehaviour : BehaviourState
{
public:
    ~RandomWayPointBehaviour() override;
    void enter() override;
    void execute(Actor* actor, glm::vec3 target_pos, float delta_time) override;
    void exit() override;
};
