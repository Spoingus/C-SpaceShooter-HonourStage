#include "GameScene.h"

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

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)s_width / (float)s_height, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    default_shader.setMat4("projection", projection);
    default_shader.setMat4("view", view);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
    default_shader.setMat4("model", model);
    guitar_backpack.Draw(default_shader);
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
