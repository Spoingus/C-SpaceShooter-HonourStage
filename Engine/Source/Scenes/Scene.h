#pragma once

class Scene
{
protected:
    
    SceneManager scene_manager;
    
public:

    static float dt = 0;

    static Camera camera;
    
    virtual ~Scene() = default;
    Scene(SceneManager scene_manager);
    
    virtual void Render();
    virtual void Update();
    virtual void Close();
};
