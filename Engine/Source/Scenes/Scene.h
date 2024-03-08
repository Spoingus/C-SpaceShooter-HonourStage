#ifndef SCENE_H
#define SCENE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../../Source/Camera.h"
#include "../Managers/SceneManager.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Scene
{
    
public:
    //Scene window
    GLFWwindow* scene_window;
    //Scene Manager
    SceneManager* scene_manager;
    //Bool to check scene loading
    bool loading_failed = false;
    //Screen width / height
    unsigned int s_width, s_height;
    //Delta time
    float delta_time = 0, last_frame = 0;
    //Camera
    static Camera camera;
    
    virtual ~Scene() = default;
    Scene(unsigned int in_width, unsigned int in_height);
    
    virtual void Render() = 0;
    virtual void Update() = 0;
    virtual void Close() = 0;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
#endif // SCENE_H
