#pragma once
#include "../../../Engine/Source/Camera.h"
#include "../../../Engine/Source/Scenes/Scene.h"
#include "../../Engine/Source/Assets/Shader.h"
#include "../../Engine/Source/Assets/Model.h"

class MenuScene : public Scene
{
public:
    Shader default_shader;
    Shader sky_shader;
    Model sky_sphere;
    Model ground;
    Camera camera;

    MenuScene(unsigned in_width, unsigned in_height);

    void render() override;
    void update() override;
    void close() override;
    void handle_input(GLFWwindow* window) override;
    void handle_mouse(double xposIn, double yposIn) override;
    ~MenuScene() override = default;
};
