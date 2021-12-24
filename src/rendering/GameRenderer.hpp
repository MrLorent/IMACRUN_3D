#pragma once
#define MAP_RENDERER_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.hpp"
#include "Game.hpp"

class GameRenderer
{
private:
    // ATTRIBUTS

    glimac::FilePath _applicationPath;
    unsigned int _renderingLength;
    short int _rotationDirection;
    unsigned int _rotatingIndex;

    std::deque<glm::vec3> currentLights;

    /* 3D Models */
    Model _player;
    Model _wall;
    Model _floor;
    Model _barrel;
    Model _light;
    Model _bottle;

    // PRIVATE METHODS
    void rotateCamera(Camera& cam, unsigned int caseSubdivisions);

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
