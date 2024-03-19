#pragma once
#include "../../../Engine/Source/Scenes/Scene.h"
#include "../../Engine/Source/Assets/Shader.h"
#include "../../Engine/Source/Assets/Model.h"

class GameScene : public Scene
{
public:
    Shader default_shader;
    Model guitar_backpack;
    Model ground;
    
    ~GameScene() override = default;
    GameScene(unsigned int in_width, unsigned int in_height);
    void Render() override;
    void Update() override;
    void Close() override;
};
