#pragma once
#define GAME_HPP

#include "Player.hpp"
#include "Camera.hpp"

class Game
{
private:
    glimac::FilePath _applicationPath;

    Player _player;

    void load();

public:
    Camera _camera;
    
    Game(){}
    Game(glimac::FilePath applicationPath);

    void render(glm::mat4& projectionMatrix);
};
