#pragma once
#include "../../../Engine/Source/Scenes/Scene.h"
#include "../../Engine/Source/Assets/Shader.h"
#include "../../Engine/Source/Assets/Model.h"

class GameScene : public Scene
{
public:
    Shader default_shader;
    Shader sky_shader;
    Model sky_sphere;
    Model ground;
    Model ship;
    Model enemy_ship;

    float ship_speed = 0;
    float turn_speed = 0;

    void increment_ship_speed();
    void lower_ship_speed();

    ~GameScene() override = default;
    GameScene(unsigned int in_width, unsigned int in_height);
    void render() override;
    void update() override;
    void close() override;
    void handle_input(GLFWwindow *window) override;
    void handle_mouse(double xposIn, double yposIn) override;
};
