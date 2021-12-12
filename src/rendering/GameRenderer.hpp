#pragma once
#define MAP_RENDERER_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.hpp"
#include "Game.hpp"

class GameRenderer
{
private:
    std::vector<glm::mat4> X_TRANSLATE_MATRICES;
    
    // ATTRIBUTS

    glimac::FilePath _applicationPath;
    unsigned int _renderingLength;
    float _caseSubdivisions;
    unsigned int _caseSubdivisionsIndex;
    short int _rotationDirection;

    unsigned int _rotatingIndex;

    /* 3D Models */
    Model _player;
    Model _wall;
    Model _floor;

    // PRIVATE METHODS
    void rotateMap(glm::mat4& MVMatrix, Player& player);

public:
    GameRenderer(){}
    GameRenderer(glimac::FilePath applicationPath);

    void load3DModels();
    void initMapRotation(int direction);

    void render(
        glm::mat4 projectionMatrix,
        Game& game
    );
};
