#include "GameRenderer.hpp"

GameRenderer::GameRenderer(glimac::FilePath applicationPath)
    :_applicationPath(applicationPath),
     _renderingLength(15), // nb ligne to draw
     _caseSubdivisions(75.f),
     _caseSubdivisionsIndex(0),
     _rotationDirection(0)
{
    X_TRANSLATE_MATRICES = {
        glm::translate(glm::mat4(1.f),glm::vec3(-2.f,0.f,0.f)),
        glm::translate(glm::mat4(1.f),glm::vec3(-1.f,0.f,0.f)),
        glm::translate(glm::mat4(1.f),glm::vec3(0.f,0.f,0.f)),
        glm::translate(glm::mat4(1.f),glm::vec3(1.f,0.f,0.f)),
        glm::translate(glm::mat4(1.f),glm::vec3(2.f,0.f,0.f))
    };
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
    params.fileName = "Cobblestones/CobbleStones.obj";
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
    MVMatrix = X_TRANSLATE_MATRICES[0];
    /* Move the scene according to the camera */
    MVMatrix = viewMatrix * MVMatrix;
    glm::vec3 zTranslation = glm::vec3(
        0.0,
        0.0,
        -1-_caseSubdivisionsIndex/_caseSubdivisions
    );
    MVMatrix = glm::translate(
        MVMatrix,
        zTranslation
    );
    for(unsigned int i=map.getIndex(); i<map.getIndex()+_renderingLength; ++i)
    {
        for(unsigned short int k=0; k<map.getMapWidth(); ++k){
            switch (map[map.getMapWidth() * i + k])
            {
                case Map::FLOOR:
                    _floor.draw(projectionMatrix, MVMatrix);
                    break;
                case Map::WALL:
                    MVMatrix = glm::translate(
                        MVMatrix,
                        glm::vec3(0.f,1.f,0.f)
                    );
                    _floor.draw(projectionMatrix, MVMatrix);
                    MVMatrix = glm::translate(
                        MVMatrix,
                        glm::vec3(0.f,-1.f,0.f)
                    );
                    break;
                case Map::HOLE:
                    break;
                
                default:
                    break;
            }
            MVMatrix = glm::translate(MVMatrix, glm::vec3(1.f, 0.f, 0.f));
        }
        if(map[map.getMapWidth() * i] != Map::WALL){ _rotationDirection = -1; } /* right turn */
        else if(map[map.getMapWidth() * i + map.getMapWidth()-1] != Map::WALL){ _rotationDirection = 1; } /* left turn*/
        if(map[map.getMapWidth() * i + (map.getMapWidth()-1)/2] == Map::WALL){
            if(_rotationDirection == -1)
            {
                MVMatrix = glm::translate(MVMatrix, glm::vec3(-map.getMapWidth(), 0.f, -(map.getMapWidth()-1)));
            }else{
                MVMatrix = glm::translate(MVMatrix, glm::vec3(0.f, 0.f, 0.f));
            }
            MVMatrix = glm::rotate(
                MVMatrix,
                float(M_PI/2*_rotationDirection),
                glm::vec3(0.f, 1.f, 0.f)
            );
        }else{
            MVMatrix = glm::translate(MVMatrix, glm::vec3(-map.getMapWidth(), 0.f, 1.f));
        }
    }

    _caseSubdivisionsIndex++;

    if(_caseSubdivisionsIndex == _caseSubdivisions){
        map.incrementIndex();
        _caseSubdivisionsIndex = 0;
    }
    
}