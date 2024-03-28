#include "pch.h"
#include "Scene.h"

#include <stb_image.h>

//Camera Scene::camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));

Scene::Scene(const char* title,unsigned in_width, unsigned in_height): s_width(in_width), s_height(in_height)
{
    auto titles = "Failed to create GLFW window";
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    scene_window = glfwCreateWindow(static_cast<int>(s_width), static_cast<int>(s_height), title, nullptr,nullptr);
    if (scene_window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << '\n';
        glfwTerminate();
        loading_failed = true;
    }
    glfwMakeContextCurrent(scene_window);
    glfwSetFramebufferSizeCallback(scene_window, framebuffer_size_callback);
    
    glfwSetInputMode(scene_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << '\n';
        loading_failed = true;
    }
    
    stbi_set_flip_vertically_on_load(true);
    
    glEnable(GL_DEPTH_TEST);
}

void Scene::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{ glViewport(0, 0, width, height); }
