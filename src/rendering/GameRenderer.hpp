#pragma once
#define MAP_RENDERER_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.hpp"
#include "Game.hpp"
#include "Text2D.hpp"

struct matrix{
    glm::mat4 _PROJECTION_MATRIX;
    glm::mat4 VMatrix;
    glm::mat4 MMatrix;
    std::deque<glm::vec3> currentLights;


    matrix(glm::mat4 projMatrix,
    glm::mat4 ViewMatrix,
    glm::mat4 ModelMatrix,
    std::deque<glm::vec3> Lights):
    _PROJECTION_MATRIX(projMatrix),
    VMatrix(ViewMatrix),
    MMatrix(ModelMatrix),
    currentLights(Lights){}
};


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
    bool firstlightsInit;

    /* 3D Models */
    Model _player;
    Model _wall;
    Model _floor;
    Model _barrel;
    Model _light;
    Model _bottle;
    Model _skybox;
    Model _arch;
    Model _plank;

    // PRIVATE METHODS

    void load3DModels();

    void drawMap(Game& game, glm::mat4& VMatrix);
    void drawPlayer(Game& game,Player& player, glm::mat4& VMatrix);
    void drawSkyBox(glm::mat4& VMatrix);
    void setLights(glm::mat4& MMatrix,std::vector<glm::vec3>& firstLights, std::deque<glm::vec3>& lights, const short unsigned int rank);

    void drawWall(glm::mat4 &_PROJECTION_MATRIX,
    glm::mat4 &VMatrix,
    glm::mat4 &MMatrix,
    std::deque<glm::vec3> &currentLights);

    void drawBarel(glm::mat4 &_PROJECTION_MATRIX,
    glm::mat4 &VMatrix,
    glm::mat4 &MMatrix,
    std::deque<glm::vec3> &currentLights);

    void drawLantern(glm::mat4 &_PROJECTION_MATRIX,
    glm::mat4 &VMatrix,
    glm::mat4 &MMatrix,
    std::deque<glm::vec3> &currentLights);

    void drawBottle(glm::mat4 &_PROJECTION_MATRIX,
    glm::mat4 &VMatrix,
    glm::mat4 &MMatrix,
    std::deque<glm::vec3> &currentLights);

    void drawArch(glm::mat4 &_PROJECTION_MATRIX,
    glm::mat4 &VMatrix,
    glm::mat4 &MMatrix,
    std::deque<glm::vec3> &currentLights);

    void drawPlank(glm::mat4 &_PROJECTION_MATRIX,
    glm::mat4 &VMatrix,
    glm::mat4 &MMatrix,
    std::deque<glm::vec3> &currentLights);


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
