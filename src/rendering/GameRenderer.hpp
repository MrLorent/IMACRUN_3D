#pragma once
#define MAP_RENDERER_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.hpp"
#include "Map.hpp"
#include "Player.hpp"

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

    /* 3D Models */
    Model _player;
    Model _wall;
    Model _floor;

    // PRIVATE METHODS

public:
    GameRenderer(){}
    GameRenderer(glimac::FilePath applicationPath);

    void load3DModels();

    void render(
        glm::mat4 projectionMatrix,
        glm::mat4 viewMatrix,
        Player& player,
        Map& map,
        bool paused
    );
};
