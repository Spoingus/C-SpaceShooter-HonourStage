#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Engine/Source/Managers/SceneManager.h"
#include "Source/Scenes/GameScene.h"
#include "Source/Scenes/MenuScene.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow *window);

// settings
constexpr unsigned int scr_width = 1920;
constexpr unsigned int scr_height = 1080;

int main()
{
    constexpr double fps_limit = 1.0 / 165.0; //Framerate base on monitor refresh rate
    double last_frame_time = 0;
    
    auto& scene_manager = SceneManager::get();
    //Load scene and check for GLFW / GLAD errors
    //MenuScene menu(scr_width, scr_height);
    GameScene game(scr_width, scr_height);
    scene_manager.set_scene(&game);

    const auto& scene = scene_manager.current_scene;
    
    if (scene->loading_failed) return -1;
    glfwSetCursorPosCallback(scene_manager.current_scene->scene_window, mouse_callback);
    
    //Update Loop
    while (!glfwWindowShouldClose(scene->scene_window))
    {
        const double now = glfwGetTime();
        
        glfwPollEvents();
        processInput(scene->scene_window);
        
        scene->update();
        
        if (now - last_frame_time >= fps_limit)
        {
            scene->render();
            glfwSwapBuffers(scene->scene_window);
            last_frame_time = now;
        }
    }
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    const auto& scene_manager = SceneManager::get();
    scene_manager.current_scene->handle_input(window);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    const auto& scene_manager = SceneManager::get();
    scene_manager.current_scene->handle_mouse(xposIn,yposIn);
}