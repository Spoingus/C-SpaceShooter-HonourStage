#pragma once

enum ComponentTypes
{
    geometry,
    collision,
    audio,
    behaviour
};

class InterfaceComponent
{
public:
    virtual ~InterfaceComponent() = default;
    virtual ComponentTypes get_component_type();
};
