#pragma once

class Scene;

class SceneManager
{
    SceneManager() = default;
public:
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
    SceneManager(SceneManager&&) = delete;
    SceneManager& operator=(SceneManager&&) = delete;

    static SceneManager& get(){
        static SceneManager instance;
        return instance; }
    
    void set_scene(Scene* scene) {current_scene = scene;}
    void to_previous_scene() {current_scene = previous_scene;}
    
    Scene *current_scene;
private:
    Scene *previous_scene;
    
    int width = 1920, height = 1080;
};
/*namespace  scene_manager
{
    static Scene *current_scene;
    static Scene *previous_scene;
    
    static int width = 1920, height = 1080;
    
    static void set_scene(Scene* scene) {current_scene = scene;}
    static void to_previous_scene();
}*/
