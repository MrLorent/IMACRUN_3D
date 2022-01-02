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
    Text2D _text;


    std::deque<glm::vec3> currentLights;

    /* 3D Models */
    Model _player3DModel;
    Model _wall3DModel;
    Model _floor3DModel;
    Model _barrel3DModel;
    Model _light3DModel;
    Model _bottle3DModel;
    Model _skybox3DModel;
    Model _arch3DModel;
    Model _plank3DModel;

    // PRIVATE METHODS

    void load3DModels();

    void drawMap(Game& game, glm::mat4& VMatrix);
    void drawPlayer(Game& game,Player& player, glm::mat4& VMatrix);
    void drawSkyBox(glm::mat4& VMatrix, glm::mat4& MMatrix);
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
    // OPERATORS
    /* Move assignment operator */

    GameRenderer& operator=(GameRenderer&& rhs) noexcept;

    /* Copy assignment operator */
    GameRenderer& operator=(const GameRenderer&) = delete; // We disable copying
    
    // CONSTRUCTORS
    /* basic constructors */
    GameRenderer(){}
    GameRenderer(glimac::FilePath applicationPath);

    /* Copy constructor */

    GameRenderer(const GameRenderer&) = delete; // We disable copying

    /* move constructor */
    
    GameRenderer(GameRenderer&& rhs) noexcept;

    // DESTRUCTOR
    ~GameRenderer(){}

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