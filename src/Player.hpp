#pragma once
#define PLAYER_HPP

#include "Model.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Player
{
private:
    glm::mat4 _MVMatrix;    /* Model View Matrix */
    Model _model;           /* 3D model of the player */
    
public:
    Player(){}
    Player(glimac::FilePath applicationPath);

    void draw(glm::mat4& projectionMatrix, glm::mat4& MVMatrix);
};
