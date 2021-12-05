#pragma once
#define GAME_HPP

#include "Model.hpp"
#include "TrackballCamera.hpp"

class Game
{
private:
    glimac::FilePath _applicationPath;
    glm::mat4 _projectionMatix;
    glm::mat4 _MVMatrix;

    Model _model;

    void load();

public:
    glimac::TrackballCamera _camera;
    
    Game(){}
    Game(glimac::FilePath applicationPath);

    void render(glm::mat4& projectionMatrix);
};
