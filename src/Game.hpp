#pragma once
#define GAME_HPP

#include "Model.hpp"

class Game
{
private:
    glimac::FilePath _applicationPath;
    glm::mat4& _projectionMatix;

public:
    Game(glimac::FilePath applicationPath, glm::mat4& projectionMatrix);
};
