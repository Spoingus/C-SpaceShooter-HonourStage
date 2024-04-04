#pragma once
#include "BehaviourState.h"

class BehaviourStateMachine
{
public:
    BehaviourState *current_state;
    BehaviourState *previous_state;
    
    void update(Actor *actor, const float delta_time) const {current_state->execute(actor,current_state->current_target,delta_time);}
    void change_state(BehaviourState *new_state)
    {
        previous_state = current_state;
        current_state->exit();
        current_state = new_state;
        current_state->enter();
    }
    void change_to_previous_state(){current_state = previous_state;}
    
};
