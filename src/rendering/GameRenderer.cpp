#include "GameRenderer.hpp"

GameRenderer::GameRenderer(glimac::FilePath applicationPath)
    :_applicationPath(applicationPath),
     _renderingLength(15), // nb ligne to draw
     _rotationDirection(0),
     _rotatingIndex(0)
{
     /* Initialisation of the fonts */
    _text = Text2D(20, _applicationPath, "PTMono.ttc");
    _textProjectionMatrix = glm::ortho(
        0.0f,
        static_cast<float>(720),
        0.0f,
        static_cast<float>(720)
    );
}

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
    params.fileName = "bottle/bottle.obj";
    params.vsShader = "model.vs.glsl";
    params.fsShader = "model.fs.glsl";

    _player = Model(params);

    // LOADING OF THE TILE MODEL
    params.fileName = "Cobblestones/CobbleStones.obj";
    params.vsShader = "model.vs.glsl";
    params.fsShader = "model.fs.glsl";
 
    _floor = Model(params);

    //LOADING OF THE FENCE MODEL
    params.fileName = "fence/fence.obj";
    params.vsShader = "model.vs.glsl";
    params.fsShader = "model.fs.glsl";
 
    _wall = Model(params);

    //LOADING OF THE BARREL MODEL
    params.fileName = "barrel/barrel.obj";
    params.vsShader = "model.vs.glsl";
    params.fsShader = "model.fs.glsl";
 
    _barrel = Model(params);

    //LOADING OF THE LIGHT MODEL
    params.fileName = "lantern/lantern.obj";
    params.vsShader = "model.vs.glsl";
    params.fsShader = "model.fs.glsl";
 
    _light = Model(params);

    //LOADING OF THE BOTTLE MODEL
    params.fileName = "bottle/bottle.obj";
    params.vsShader = "model.vs.glsl";
    params.fsShader = "model.fs.glsl";
 
    _bottle = Model(params);
}

void GameRenderer::render(
    glm::mat4 projectionMatrix,
    Game& game
)
{
    // DRAW THE MAP
    Map& map = game._map;
    for(size_t i=0; i<map.firstLights.size(); ++i)
    {
        currentLights.push_back(map.firstLights[i]);
    }

    glm::mat4 MMatrix = glm::translate(
        glm::mat4(1.f),
        glm::vec3(
            -2.f, /* Place of the first left wall */
            0.f,
            0.5-game._playerIndex-game._caseSubdivisionsIndex/game._caseSubdivisions
        ) 
    );

    if(game._camera._turning != 0) game._camera.takeTurn();

    auto VMatrix= game._camera.getViewMatrix();


    /* Move the scene according to the camera */
    //MVMatrix = game._camera.getViewMatrix() * MVMatrix;
    
    for(unsigned int i=0; i<_renderingLength; ++i)
    {
        for(unsigned short int k=0; k<map.getMapWidth(); ++k){
            switch (map[map.getMapWidth() * i + k])
            {
                case Map::FLOOR:
                    _floor.draw(projectionMatrix, VMatrix, MMatrix, currentLights);
                    break;
                case Map::PASSED_TURN:
                    _floor.draw(projectionMatrix, VMatrix, MMatrix, currentLights);
                    break;
                case Map::WALL:
                    if(k==0){
                        MMatrix = glm::translate(
                            MMatrix,
                            glm::vec3(0.4f,0.f,0.f)
                        );                    

                        _wall.draw(projectionMatrix, VMatrix, MMatrix, currentLights);

                        MMatrix = glm::translate(
                            MMatrix,
                            glm::vec3(-0.4f,0.f,0.f)
                        );
                    }else if(k%4==0){
                        
                        MMatrix = glm::translate(
                            MMatrix,
                            glm::vec3(-0.4f,0.1f,0.f)
                        );
                      
                          MMatrix = glm::rotate(
                            MMatrix,
                            glm::pi<float>(),
                            glm::vec3(0.f, 1.f, 0.f)
                        );

                        _wall.draw(projectionMatrix, VMatrix, MMatrix, currentLights);

                        MMatrix = glm::rotate(
                            MMatrix,
                            glm::pi<float>(),
                            glm::vec3(0.f, 1.f, 0.f)
                        );

                        MMatrix = glm::translate(
                            MMatrix,
                            glm::vec3(0.4f,-0.1f,0.f)
                        );
                    }
                        
                    break; 
                case Map::LIGHT: //Mal positionnée
                    MMatrix = glm::translate(
                        MMatrix,
                        glm::vec3(0.f,1.f,0.f)
                    );
                    _light.MMatrixLight = MMatrix;
                    _light.draw(projectionMatrix, VMatrix, MMatrix, currentLights);
                    MMatrix = glm::translate(
                        MMatrix,
                        glm::vec3(0.f,-1.f,0.f)
                    );
                    break;
                case Map::HOLE:
                    break;
                case Map::BAREL:
                    _floor.draw(projectionMatrix, VMatrix, MMatrix, currentLights);
                    MMatrix = glm::translate(
                        MMatrix,
                        glm::vec3(0.f,0.5f,0.f)
                    );
                    _barrel.draw(projectionMatrix, VMatrix, MMatrix, currentLights);
                    MMatrix = glm::translate(
                        MMatrix,
                        glm::vec3(0.f,-0.5f,0.f)
                    );
                    break;
                case Map::COLLECTIBLE:

                    _floor.draw(projectionMatrix, VMatrix, MMatrix, currentLights);
                    MMatrix = glm::translate(
                        MMatrix,
                        glm::vec3(0.f,0.5f,0.f)
                    );
                    MMatrix=glm::scale(
                        MMatrix,
                        glm::vec3(0.25,0.25,0.25)
                    );
                    _bottle.draw(projectionMatrix, VMatrix, MMatrix, currentLights);
                    MMatrix=glm::scale(
                        MMatrix,
                        glm::vec3(4,4,4)
                    );
                    MMatrix = glm::translate(
                        MMatrix,
                        glm::vec3(0.f,-0.5f,0.f)
                    );
                default:
                    break;
            }
           
            MMatrix = glm::translate(MMatrix, glm::vec3(1.f, 0.f, 0.f));
        }

        /* Detecting turns */
        if(map[map.getMapWidth() * i] == Map::FLOOR){ _rotationDirection = -1; } /* right turn */
        else if(map[map.getMapWidth() * i + map.getMapWidth()-1] == Map::FLOOR){ _rotationDirection = 1; } /* left turn*/
        
        if(map[map.getMapWidth() * i + (map.getMapWidth()-1)/2] == Map::WALL && i >= game._playerIndex){
            if(_rotationDirection == -1)
            {
                MMatrix = glm::translate(MMatrix, glm::vec3(-map.getMapWidth(), 0.f, -(map.getMapWidth()-1)));
            }else{
                MMatrix = glm::translate(MMatrix, glm::vec3(0.f, 0.f, 0.f));
            }
            MMatrix = glm::rotate(
                MMatrix,
                glm::pi<float>()/2*_rotationDirection,
                glm::vec3(0.f, 1.f, 0.f)
            );
        }else{
            MMatrix = glm::translate(MMatrix, glm::vec3(-map.getMapWidth(), 0.f, 1.f));
        }

    }

    // DRAW THE PLAYER
    Player& player = game._player;

    if(player._isJumping) player.jump();
    /* Place the Player Model into the scene */

    /* turn back the model from the camera */
    MMatrix = glm::rotate(
        glm::mat4(1.f),
        float(M_PI),
        glm::vec3(0.f,1.f,0.f)
    );

    /* put the player model at the right position */
    MMatrix = glm::translate(
        MMatrix,
        player.getPosition()
    );

    VMatrix = game._camera.getViewMatrix();

    /* Move the player model according to the camera */
    MMatrix=glm::scale(
                        MMatrix,
                        glm::vec3(0.5,0.5,0.5)
                    );
    _player.draw(projectionMatrix, VMatrix, MMatrix, currentLights);
    MMatrix=glm::scale(
                        MMatrix,
                        glm::vec3(2,2,2)
                    );

    _text.draw(
            "Score : "+std::to_string(game._player.getScore()),
            glm::vec2(50.f, 600.f ),
            glm::vec3(1.f),
            _textProjectionMatrix
        );
}