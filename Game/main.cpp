#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Engine/Source/Assets/Shader.h"
#include "../Engine/Source/Assets/Model.h"
#include "../Engine/Source/Managers/SceneManager.h"

#include "Source/Scenes/GameScene.h"

//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
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
    
    if (scene_manager.current_scene->loading_failed) return -1;
    glfwSetCursorPosCallback(scene_manager.current_scene->scene_window, mouse_callback);
    glfwSetScrollCallback(scene_manager.current_scene->scene_window, scroll_callback);
    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(scene_manager.current_scene->scene_window))
    {
        scene_manager.current_scene->Update();
        
        scene_manager.current_scene->Render();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(scene_manager.current_scene->scene_window);
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
}

/*/ glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}*/

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
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

    GameScene::camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    GameScene::camera.ProcessMouseScroll(static_cast<float>(yoffset));
}