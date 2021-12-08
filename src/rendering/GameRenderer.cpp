#include "GameRenderer.hpp"

GameRenderer::GameRenderer(glimac::FilePath applicationPath)
    :_applicationPath(applicationPath),
     _renderingLength(4 * 5) // nb ligne * nb case in a line
{
    X_TRANSLATE_MATRICES = {
        glm::translate(glm::mat4(1.f),glm::vec3(-2.f,0.f,0.f)),
        glm::translate(glm::mat4(1.f),glm::vec3(-1.f,0.f,0.f)),
        glm::translate(glm::mat4(1.f),glm::vec3(0.f,0.f,0.f)),
        glm::translate(glm::mat4(1.f),glm::vec3(1.f,0.f,0.f)),
        glm::translate(glm::mat4(1.f),glm::vec3(2.f,0.f,0.f))
    };
    load3DModels();
}

void GameRenderer::load3DModels()
{
    ModelParams params(_applicationPath);

    // LOADING OF THE PLAYER MODEL
    params.fileName = "knight/alliance.obj";
    params.vsShader = "triangle.vs.glsl";
    params.fsShader = "triangle.fs.glsl";

    _player = Model(params);

    // LOADING OF THE TILE MODEL
    params.fileName = "box/box.obj";
    params.vsShader = "triangle.vs.glsl";
    params.fsShader = "triangle.fs.glsl";

    _floor = Model(params);
}

void GameRenderer::render(
    glm::mat4 projectionMatrix,
    glm::mat4 viewMatrix,
    glm::vec3 playerPosition,
    Map& map
)
{
    // DRAW THE PLAYER
    /* Place the Player Model into the scene */

    /* turn back the model from the camera */
    glm::mat4 MVMatrix = glm::rotate(
        glm::mat4(1.f),
        float(M_PI),
        glm::vec3(0.f,1.f,0.f)
    );

    /* put the player model at the right position */
    MVMatrix = glm::translate(
        MVMatrix,
        playerPosition
    );

    /* Move the player model according to the camera */
    MVMatrix = viewMatrix * MVMatrix;

    _player.draw(projectionMatrix, MVMatrix);

    // DRAW THE MAP
    for(unsigned int i=0; i<_renderingLength; i++)
    {
        MVMatrix = X_TRANSLATE_MATRICES[i%5];

        MVMatrix = glm::translate(
            MVMatrix,
            glm::vec3(0.0,0.0,i/5)
        );

        /* Move the scene according to the camera */
        MVMatrix = viewMatrix * MVMatrix;
        _floor.draw(projectionMatrix, MVMatrix);
    }
}