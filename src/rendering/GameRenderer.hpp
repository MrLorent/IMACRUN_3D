#pragma once
#define MAP_RENDERER_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.hpp"
#include "Game.hpp"
#include "Text2D.hpp"

class GameRenderer
{
private:
    // ATTRIBUTS
    /* Window parameters */
    int _WINDOW_WIDTH;
    int _WINDOW_HEIGHT;
    glm::mat4 _PROJECTION_MATRIX;
    glm::mat4 _TEXT_PROJECTION_MATRIX;

    glimac::FilePath _applicationPath;
    unsigned int _renderingLength;
    short int _rotationDirection;
    unsigned int _rotatingIndex;
    Text2D _text;


    std::deque<glm::vec3> currentLights;

    /* 3D Models */
    Model _player;
    Model _wall;
    Model _floor;
    Model _barrel;
    Model _light;
    Model _bottle;
    Model _skybox;

    // PRIVATE METHODS

    void load3DModels();

    void drawMap(Game& game, glm::mat4& VMatrix);
    void drawPlayer(Player& player, glm::mat4& VMatrix);
    void drawSkyBox(glm::mat4& VMatrix);

public:
    GameRenderer(){}
    GameRenderer(glimac::FilePath applicationPath);

    // METHODS

    void render(
        Game& game
    );

    /* Window parameters */
    void setWindowParameters(
        const unsigned width,
        const unsigned height,
        glm::mat4& projection
    );

};
