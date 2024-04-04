#pragma once
#include "../../../Engine/Source/Objects/Actor.h"

class BehaviourState
{
public:
    virtual ~BehaviourState() = default;

    glm::vec3 current_target = glm::vec3(0,0,0);
    
    virtual void enter() = 0;
    virtual void execute(Actor *actor, glm::vec3 target_pos, float delta_time) = 0;
    virtual void exit() = 0;

    static glm::vec3 get_steering_force(Actor actor, glm::vec3 target_pos);
};
