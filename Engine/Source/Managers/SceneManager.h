#pragma once

class Scene;

class SceneManager
{
public:
    static int width = 1920, height = 1080;

    void ChangeScene(Scene scene_type);
};
