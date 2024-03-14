#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Engine/Source/Assets/Shader.h"
#include "../Engine/Source/Assets/Model.h"
#include "../Engine/Source/Managers/SceneManager.h"

#include "Source/Scenes/GameScene.h"
#define _USE_MATH_DEFINES
#include <math.h>

//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    auto& scene_manager = SceneManager::get();
    //Load scene and check for GLFW / GLAD errors
    GameScene game(SCR_WIDTH, SCR_HEIGHT);
    scene_manager.set_scene(&game);

    auto& scene = scene_manager.current_scene;
    
    if (scene->loading_failed) return -1;
    glfwSetCursorPosCallback(scene_manager.current_scene->scene_window, mouse_callback);
    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(scene->scene_window))
    {
        processInput(scene->scene_window);
        
        scene->Update();
        
        scene->Render();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(scene->scene_window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    const auto& scene_manager = SceneManager::get();
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        scene_manager.current_scene->camera.moveForward(2.0f * scene_manager.current_scene->delta_time);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        scene_manager.current_scene->camera.moveForward(-2.0f * scene_manager.current_scene->delta_time);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        scene_manager.current_scene->camera.turn(0.02f);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        scene_manager.current_scene->camera.turn(-0.02f);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    const auto& scene_manager = SceneManager::get();
    
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    scene_manager.current_scene->camera.yaw(xoffset/20);
    scene_manager.current_scene->camera.pitch(-yoffset/20);
}