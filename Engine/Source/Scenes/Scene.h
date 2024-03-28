#ifndef SCENE_H
#define SCENE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "..\Camera.h"
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
    Camera camera;
    unsigned int width = 1920;
    unsigned int height = 1080;

    float last_x = static_cast<float>(width) / 2.0f;
    float last_y = static_cast<float>(height) / 2.0f;
    bool first_mouse = true;
    
    virtual ~Scene() = default;
    Scene(const char* title, unsigned int in_width, unsigned int in_height);
    
    virtual void render() = 0;
    virtual void update() = 0;
    virtual void close() = 0;
    virtual void handle_input(GLFWwindow *window) = 0;
    virtual void handle_mouse(double xposIn, double yposIn) = 0;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
#endif // SCENE_H
