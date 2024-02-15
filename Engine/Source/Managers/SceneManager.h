#pragma once
#include "../Scenes/Scene.h"

namespace  scene_manager
{
    static Scene current_scene;
    static Scene previous_scene;
    
    static int width = 1920, height = 1080;

    static void ChangeScene(Scene scene_type);
    static void PreviousScene();
}
