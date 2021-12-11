#include "GameRenderer.hpp"

GameRenderer::GameRenderer(glimac::FilePath applicationPath)
    :_applicationPath(applicationPath),
     _renderingLength(15), // nb ligne to draw
     _caseSubdivisions(75.f),
     _caseSubdivisionsIndex(0)
{
    X_TRANSLATE_MATRICES = {
        glm::translate(glm::mat4(1.f),glm::vec3(-2.f,1.f,0.f)),
        glm::translate(glm::mat4(1.f),glm::vec3(-1.f,0.f,0.f)),
        glm::translate(glm::mat4(1.f),glm::vec3(0.f,0.f,0.f)),
        glm::translate(glm::mat4(1.f),glm::vec3(1.f,0.f,0.f)),
        glm::translate(glm::mat4(1.f),glm::vec3(2.f,1.f,0.f))
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
    for(unsigned int i=map.getIndex(); i<map.getIndex()+_renderingLength; ++i)
    {
        glm::vec3 zTranslation = glm::vec3(
            0.0,
            0.0,
            (i-map.getIndex()) - _caseSubdivisionsIndex/_caseSubdivisions
        );

        for(unsigned short int k=0; k<map.getMapWidth(); ++k){
            MVMatrix = X_TRANSLATE_MATRICES[k];
            MVMatrix = glm::translate(
                MVMatrix,
                zTranslation
            );

            /* Move the scene according to the camera */
            MVMatrix = viewMatrix * MVMatrix;

            switch (map[map.getMapWidth() * i + k])
            {
                case map.FLOOR:
                    _floor.draw(projectionMatrix, MVMatrix);
                    break;
                case map.WALL:
                    _floor.draw(projectionMatrix, MVMatrix);
                    break;
                case map.HOLE:
                    break;
                
                default:
                    break;
            }
        }
    }

    _caseSubdivisionsIndex++;

    if(_caseSubdivisionsIndex == _caseSubdivisions){
        map.incrementIndex();
        _caseSubdivisionsIndex = 0;
    }
    
}