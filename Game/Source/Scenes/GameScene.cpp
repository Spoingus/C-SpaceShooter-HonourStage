#include "GameScene.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

GameScene::GameScene(const unsigned int in_width, const unsigned int in_height): Scene(in_width, in_height),
                                                                                 default_shader("Shaders/Vertex/vertex.glsl", "Shaders/Fragment/fragment.glsl"),
                                                                                 guitar_backpack("Assets/Geometry/SkySphere/SkySphere.obj")
{
    //default_shader = Shader("Shaders/Vertex/vertex.glsl", "Shaders/Fragment/fragment.glsl");
    //guitar_backpack = Model("Assets/Geometry/Backpack/backpack.obj");
}

void GameScene::Render()
{
    // render
    // ------
    glClearColor(0.05f, 0.2f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    default_shader.use();

    // render the sky
    glDepthMask(GL_FALSE);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0,0,0));
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    default_shader.setMat4("model", model);
    guitar_backpack.Draw(default_shader);
    glDepthMask(GL_TRUE);

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)s_width / (float)s_height, 0.1f, 100000.0f);
    glm::mat4 view = camera.get_view_matrix();
    default_shader.setMat4("projection", projection);
    default_shader.setMat4("view", view);
}

void GameScene::Update()
{
    // per-frame time logic
    // --------------------
    const float current_frame = static_cast<float>(glfwGetTime());
    delta_time = current_frame - last_frame;
    last_frame = current_frame;
    delta_time += 1;
}

void GameScene::Close()
{
}
