#include "pch.h"
#include "SceneManager.h"

void scene_manager::ChangeScene(Scene* scene_type)
{
    current_scene = scene_type;
}

void scene_manager::PreviousScene()
{
    current_scene = previous_scene;
}
