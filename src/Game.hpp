#pragma once
#define GAME_HPP

#include "Model.hpp"

class Game
{
private:
    glimac::FilePath _applicationPath;
    glm::mat4 _projectionMatix;
    Model _model;

    void load();

public:
    Game(){}
    Game(glimac::FilePath applicationPath, glm::mat4 projectionMatrix);

    void render(glm::mat4 MVMatrix);
};
