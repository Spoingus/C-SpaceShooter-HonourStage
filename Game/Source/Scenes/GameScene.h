#pragma once
#include "../../../Engine/Source/Scenes/Scene.h"
#include "../../Engine/Source/Assets/Shader.h"
#include "../../Engine/Source/Assets/Model.h"
#include "../ActorTypes/PlayerActor.h"
#include <list>

class GameScene : public Scene
{
public:
    Shader default_shader;
    Shader sky_shader;
    Model sky_sphere;
    Model ground;
    Model enemy_ship;
    PlayerActor player_actor;
    std::list<EnemyActor> enemy_actors;

    int enemy_count = 25;
    
    

    ~GameScene() override = default;
    GameScene(unsigned int in_width, unsigned int in_height);
    void render() override;
    void update() override;
    void close() override;
    void handle_input(GLFWwindow *window) override;
    void handle_mouse(double xposIn, double yposIn) override;
};
