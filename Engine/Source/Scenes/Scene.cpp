#include "pch.h"
#include "Scene.h"

#include <stb_image.h>

//Camera Scene::camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));

Scene::Scene(unsigned in_width, unsigned in_height): s_width(in_width), s_height(in_height)
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    scene_window = glfwCreateWindow(static_cast<int>(s_width), static_cast<int>(s_height), "C++ Space Shooter", nullptr,nullptr);
    if (scene_window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << '\n';
        glfwTerminate();
        loading_failed = true;
    }
    glfwMakeContextCurrent(scene_window);
    glfwSetFramebufferSizeCallback(scene_window, framebuffer_size_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(scene_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << '\n';
        loading_failed = true;
    }

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
}

void Scene::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{ glViewport(0, 0, width, height); }
