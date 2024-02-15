#pragma once

enum ComponentTypes
{
    geometry,
    collision,
    audio,
    behaviour
};

class Component
{
public:
    virtual ~Component() = default;
    virtual ComponentTypes get_component_type();
};
