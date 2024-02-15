#pragma once
#include "../../../Engine/Source/Scenes/Scene.h"

class GameScene : Scene
{
public:
    ~GameScene() override;
    void Render() override;
    void Update() override;
    void Close() override;
};
