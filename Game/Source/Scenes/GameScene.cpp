﻿#include "GameScene.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <random>
#include "../../../Engine/Source/Managers/ResourceManager.h"
#include "../Managers/EnemyManager.h"

GameScene::GameScene(const unsigned int in_width, const unsigned int in_height): Scene("C++ Space Shooter - Game",
                                                                                       in_width, in_height),
                                                                                 default_shader("Shaders/Vertex/vertex.glsl", "Shaders/Fragment/fragment.glsl"),
                                                                                 sky_shader("Shaders/Vertex/vertex.glsl", "Shaders/Fragment/sky_fragment.glsl"),
                                                                                 sky_sphere("Assets/Geometry/SkySphere/SkySphere.obj"),
                                                                                 ground("Assets/Geometry/Ground/ground.obj"), enemy_ship("Assets/Geometry/EnemyShip/enemy_ship.obj"),
                                                                                 player_actor(glm::vec3(0, 0, 0), glm::quat(0, 0, 0, 1))
{
    EnemyManager::get().initialise_enemies(enemy_ship);
}

void GameScene::render()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // view/projection/model transformations
    const glm::mat4 projection = glm::perspective(glm::radians(90.0f), static_cast<float>(s_width) / static_cast<float>(s_height), 0.1f, 100000.0f);
    const glm::mat4 view = player_actor.player_camera.get_view_matrix();
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
    default_shader.setVec3("view_pos",player_actor.player_camera.get_position());
    ground.Draw(default_shader);
    
    EnemyManager::get().draw_enemies(default_shader);
    
    player_actor.draw_player(default_shader);
    
    player_actor.render_projectiles(default_shader);
}

void GameScene::update()
{
    // per-frame time logic
    const float current_frame = static_cast<float>(glfwGetTime());
    delta_time = current_frame - last_frame;
    last_frame = current_frame;
    delta_time += 1;

    EnemyManager::get().update_enemies(1.0f, player_actor.player_camera.get_position());
    player_actor.update_projectiles(1.0f);
}

void GameScene::close()
{
}

void GameScene::handle_input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        player_actor.weapon_fire();
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        player_actor.increment_ship_speed();
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        player_actor.lower_ship_speed();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        player_actor.player_camera.roll(-player_actor.roll_speed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        player_actor.player_camera.roll(player_actor.roll_speed);

    player_actor.player_move(ground,delta_time);
}

void GameScene::handle_mouse(double xposIn, double yposIn)
{
    const float x_pos = static_cast<float>(xposIn);
    const float y_pos = static_cast<float>(yposIn);

    if (first_mouse)
    {
        last_x = x_pos;
        last_y = y_pos;
        first_mouse = false;
    }

    const float x_offset = x_pos - last_x;
    const float y_offset = last_y - y_pos; // reversed since y-coordinates go from bottom to top

    last_x = x_pos;
    last_y = y_pos;

    //cam.roll(x_offset);
    player_actor.player_camera.yaw(x_offset * player_actor.turn_speed);
    player_actor.player_camera.pitch(-y_offset * player_actor.turn_speed);
}
