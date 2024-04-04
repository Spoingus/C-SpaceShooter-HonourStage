#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Engine/Source/Managers/SceneManager.h"
#include "Source/Scenes/GameScene.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow *window);

// settings
constexpr unsigned int scr_width = 1920;
constexpr unsigned int scr_height = 1080;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    
    auto& scene_manager = SceneManager::get();
    //Load scene and check for GLFW / GLAD errors
    GameScene game(scr_width, scr_height);
    scene_manager.set_scene(&game);

    const auto& scene = scene_manager.current_scene;
    
    if (scene->loading_failed) return -1;
    glfwSetCursorPosCallback(scene_manager.current_scene->scene_window, mouse_callback);
    
    // render loop
    while (!glfwWindowShouldClose(scene->scene_window))
    {
        processInput(scene->scene_window);
        
        scene->update();
        
        scene->render();
        
        glfwSwapBuffers(scene->scene_window);
        glfwPollEvents();
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