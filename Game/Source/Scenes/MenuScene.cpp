#include "MenuScene.h"

MenuScene::MenuScene(unsigned in_width, unsigned in_height): Scene("C++ Shooter Game - Main Menu", in_width, in_height),
                                                             default_shader("Shaders/Vertex/vertex.glsl", "Shaders/Fragment/fragment.glsl"),
                                                             sky_shader("Shaders/Vertex/vertex.glsl", "Shaders/Fragment/sky_fragment.glsl"),
                                                             sky_sphere("Assets/Geometry/SkySphere/SkySphere.obj"),
                                                             ground("Assets/Geometry/Ground/ground.obj")
{
    camera.rotate(140,glm::vec3(0,1,0));
    camera.move_up(-1600);
}

void MenuScene::render()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // view/projection/model transformations
    const glm::mat4 projection = glm::perspective(glm::radians(90.0f), static_cast<float>(s_width) / static_cast<float>(s_height), 0.1f, 100000.0f);
    const glm::mat4 view = camera.get_view_matrix();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0,0,0));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    
    sky_shader.use();

    // render the sky
    glDepthMask(GL_FALSE);
    sky_shader.setMat4("model", model);
    sky_shader.setMat4("projection", projection);
    sky_shader.setMat4("view", view);
    sky_sphere.Draw(sky_shader);
    glDepthMask(GL_TRUE);

    //render the ground
    default_shader.use();
    default_shader.setMat4("model", model);
    default_shader.setMat4("projection", projection);
    default_shader.setMat4("view", view);
    default_shader.setVec3("view_pos",camera.get_position());
    ground.Draw(default_shader);
}

void MenuScene::update()
{
}

void MenuScene::close()
{
}

void MenuScene::handle_input(GLFWwindow* window)
{
}

void MenuScene::handle_mouse(double xposIn, double yposIn)
{
}
