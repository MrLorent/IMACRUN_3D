#include "GameRenderer.hpp"

GameRenderer::GameRenderer(glimac::FilePath applicationPath)
    :_applicationPath(applicationPath),
     _renderingLength(15), // nb ligne to draw
     _rotationDirection(0),
     _rotatingIndex(0)
{}

void GameRenderer::rotateCamera(Camera& cam, unsigned int caseSubdivisions){
    if(_rotatingIndex > caseSubdivisions * 2)
    {
        if(cam._mode == Camera::TRACKBALL) cam.rotateHorizontaly(float(M_PI/2 * cam._turning));
        else cam.rotateHorizontaly(float(M_PI/2 * -cam._turning));
        cam._turning = 0;
        _rotatingIndex = 0;
    }
    else
    {
        if(cam._mode == Camera::TRACKBALL) cam.rotateHorizontaly(float(90.f * 1/(caseSubdivisions * 2) * -cam._turning));
        else cam.rotateHorizontaly(float(90.f * 1/(caseSubdivisions * 2) * cam._turning));
        _rotatingIndex++;
    }
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
    Game& game
)
{
    // DRAW THE PLAYER
    Player& player = game._player;
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
        player.getPosition()
    );

    /* Move the player model according to the camera */
    MVMatrix = game._camera.getViewMatrix() * MVMatrix;

    _player.draw(projectionMatrix, MVMatrix);

    // DRAW THE MAP
    Map& map = game._map;
    MVMatrix = glm::translate(
        glm::mat4(1.f),
        glm::vec3(
            -2.f, /* Place of the first left wall */
            0.f,
            0.5-game._playerIndex-game._caseSubdivisionsIndex/game._caseSubdivisions
        )
    );

    if(game._camera._turning != 0) rotateCamera(game._camera, game._caseSubdivisions);
    
    /* Move the scene according to the camera */
    MVMatrix = game._camera.getViewMatrix() * MVMatrix;
    
    for(unsigned int i=0; i<_renderingLength; ++i)
    {
        for(unsigned short int k=0; k<map.getMapWidth(); ++k){
            switch (map[map.getMapWidth() * i + k])
            {
                case Map::FLOOR:
                    _floor.draw(projectionMatrix, MVMatrix);
                    break;
                case Map::PASSED_TURN:
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

        /* Detecting turns */
        if(map[map.getMapWidth() * i] != Map::WALL && map[map.getMapWidth() * i] != Map::PASSED_TURN){ _rotationDirection = -1; } /* right turn */
        else if(map[map.getMapWidth() * i + map.getMapWidth()-1] != Map::WALL && map[map.getMapWidth() * i + map.getMapWidth()-1] != Map::PASSED_TURN){ _rotationDirection = 1; } /* left turn*/
        
        if(map[map.getMapWidth() * i + (map.getMapWidth()-1)/2] == Map::WALL && i > game._playerIndex){
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
}