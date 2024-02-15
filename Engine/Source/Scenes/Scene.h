#ifndef SCENE_H
#define SCENE_H
#include "../../Source/Camera.h"

class Scene
{
    
public:

    static float delta_time;
    static Camera camera;
    
    virtual ~Scene() = default;
    
    virtual void Render(){}
    virtual void Update(){}
    virtual void Close(){}
};
#endif // SCENE_H
