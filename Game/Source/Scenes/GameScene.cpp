#include "GameScene.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "../../../Engine/Source/Managers/CollisionManager.h"
#include "../../../Engine/Source/Managers/ResourceManager.h"

void GameScene::increment_ship_speed()
{
    ship_speed += 0.1f;
    turn_speed -= 0.05f;
    if(ship_speed > 8.0f)
        ship_speed = 8.0f;
    if(turn_speed < 1.0f)
        turn_speed = 1.0f;
}

void GameScene::lower_ship_speed()
{
    ship_speed -= 0.1f;
    turn_speed += 0.05f;
    if(ship_speed < 0.0f)
        ship_speed = 0.0f;
    if(turn_speed > 2.0f)
        turn_speed = 2.0f;
}

GameScene::GameScene(const unsigned int in_width, const unsigned int in_height): Scene("C++ Space Shooter - Game", in_width, in_height),
                                                                                 default_shader("Shaders/Vertex/vertex.glsl", "Shaders/Fragment/fragment.glsl"),
                                                                                 sky_shader("Shaders/Vertex/vertex.glsl", "Shaders/Fragment/sky_fragment.glsl"),
                                                                                 sky_sphere("Assets/Geometry/SkySphere/SkySphere.obj"),
                                                                                 ground("Assets/Geometry/Ground/ground.obj"),
                                                                                 ship("Assets/Geometry/Ship/ship.obj"),
                                                                                 enemy_ship("Assets/Geometry/EnemyShip/enemy_ship.obj")
{
}

void GameScene::render()
{
    auto &resource_manager = ResourceManager::get();
    // render
    // ------
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
    enemy_ship.Draw(default_shader);

    //render the ship
    glm::mat4 ship_model = glm::mat4(1);
    ship_model = glm::translate(ship_model, camera.get_position());
    ship_model *= glm::mat4_cast(glm::conjugate(camera.get_orientation()));
    default_shader.setMat4("model", ship_model);
    ship.Draw(default_shader);
}

void GameScene::update()
{
    // per-frame time logic
    const float current_frame = static_cast<float>(glfwGetTime());
    delta_time = current_frame - last_frame;
    last_frame = current_frame;
    delta_time += 1;

    if(CollisionManager::check_terrain(ship_speed, ground, camera.get_position(),10.0f))
    {
        camera.move_world_up(ship_speed * delta_time);
        camera.pitch(-150.0f * delta_time);
    }
    if(CollisionManager::check_world_sphere(camera.get_position(),10.0f,3000.0f))
    {
        ship_speed *= -1;
    }
    camera.move_forward(ship_speed * delta_time);
    
}

void GameScene::close()
{
}

void GameScene::handle_input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        increment_ship_speed();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        lower_ship_speed();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.roll(-80.0f);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.roll(80.0f);
}

void GameScene::handle_mouse(double xposIn, double yposIn)
{
    const auto& scene_manager = SceneManager::get();
    auto& cam = scene_manager.current_scene->camera;
    
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (first_mouse)
    {
        last_x = xpos;
        last_y = ypos;
        first_mouse = false;
    }

    const float x_offset = xpos - last_x;
    const float y_offset = last_y - ypos; // reversed since y-coordinates go from bottom to top

    last_x = xpos;
    last_y = ypos;

    //cam.roll(xoffset);
    cam.yaw(x_offset * turn_speed);
    cam.pitch(-y_offset * turn_speed);
}
