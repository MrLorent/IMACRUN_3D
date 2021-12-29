#include "GameRenderer.hpp"

GameRenderer::GameRenderer(glimac::FilePath applicationPath)
    :_applicationPath(applicationPath),
     _renderingLength(15), // nb ligne to draw
     _rotationDirection(0),
     _rotatingIndex(0)
{
    load3DModels();
    
     /* Initialisation of the fonts */
    _text = Text2D(20, _applicationPath, "PTMono.ttc");
}

void GameRenderer::setWindowParameters(
    const unsigned width,
    const unsigned height,
    glm::mat4& projection
)
{
    _WINDOW_WIDTH = width;
    _WINDOW_HEIGHT = height;
    _PROJECTION_MATRIX = projection;
    _TEXT_PROJECTION_MATRIX = glm::ortho(
        0.0f,
        static_cast<float>(width),
        0.0f,
        static_cast<float>(height)
    );
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
 
    //LOADING OF THE SKYBOX MODEL
    params.fileName = "skybox/skybox.obj";
    params.vsShader = "skybox.vs.glsl";
    params.fsShader = "skybox.fs.glsl";
 
    _skybox = Model(params);
}

void GameRenderer::render(
    Game& game
)
{   
    // DRAW THE MAP
    for(size_t i=0; i<game._map.firstLights.size(); ++i)
    {
        currentLights.push_back(game._map.firstLights[i]);
    }

    glm::mat4 MMatrix = glm::translate(
        glm::mat4(1.f),
        glm::vec3(
            -2.f, /* Place of the first left wall */
            0.f,
            0.5 - game.getPlayerIndex() - game.getCaseSubdivisionIndex() / game.getCaseSubdivision()
        ) 
    );

    if(game._camera._turning != 0) game._camera.takeTurn();

    auto VMatrix = game._camera.getViewMatrix();
    
    for(unsigned int i=0; i<_renderingLength; ++i)
    {
        for(unsigned short int k=0; k < game._map.getMapWidth(); ++k){
            switch (game._map[game._map.getMapWidth() * i + k])
            {
                case Map::FLOOR:
                    _floor.draw(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);
                    break; 
                case Map::PASSED_TURN:
                    _floor.draw(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);
                    break;
                case Map::WALL:
                    if(k==0){
                        MMatrix = glm::translate(
                            MMatrix,
                            glm::vec3(0.4f,0.f,0.f)
                        );                    

                        _wall.draw(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);

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

                        _wall.draw(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);

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
                    _light.draw(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);
                    MMatrix = glm::translate(
                        MMatrix,
                        glm::vec3(0.f,-1.f,0.f)
                    );
                    break;
                case Map::HOLE:
                    break;
                case Map::BAREL:
                    _floor.draw(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);
                    MMatrix = glm::translate(
                        MMatrix,
                        glm::vec3(0.f,0.5f,0.f)
                    );
                    _barrel.draw(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);
                    MMatrix = glm::translate(
                        MMatrix,
                        glm::vec3(0.f,-0.5f,0.f)
                    );
                    break;
                case Map::COLLECTIBLE:

                    _floor.draw(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);
                    MMatrix = glm::translate(
                        MMatrix,
                        glm::vec3(0.f,0.5f,0.f)
                    );
                    MMatrix=glm::scale(
                        MMatrix,
                        glm::vec3(0.25,0.25,0.25)
                    );
                    _bottle.draw(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);
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
        if(game._map[game._map.getMapWidth() * i] == Map::FLOOR){ _rotationDirection = -1; } /* right turn */
        else if(game._map[game._map.getMapWidth() * i + game._map.getMapWidth()-1] == Map::FLOOR){ _rotationDirection = 1; } /* left turn*/
        
        if(game._map[game._map.getMapWidth() * i + (game._map.getMapWidth()-1)/2] == Map::WALL && i >= game.getPlayerIndex()){
            if(_rotationDirection == -1)
            {
                MMatrix = glm::translate(MMatrix, glm::vec3(-game._map.getMapWidth(), 0.f, -(game._map.getMapWidth()-1)));
            }else{
                MMatrix = glm::translate(MMatrix, glm::vec3(0.f, 0.f, 0.f));
            }
            MMatrix = glm::rotate(
                MMatrix,
                glm::pi<float>()/2*_rotationDirection,
                glm::vec3(0.f, 1.f, 0.f)
            );
        }else{
            MMatrix = glm::translate(MMatrix, glm::vec3(-game._map.getMapWidth(), 0.f, 1.f));
        }

    }

    // DRAW THE PLAYER
    if(game._player._isJumping) game._player.jump();
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
        game._player.getPosition()
    );

    /* Move the player model according to the camera */
    MMatrix=glm::scale(
                        MMatrix,
                        glm::vec3(0.5,0.5,0.5)
                    );
    _player.draw(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);
    MMatrix=glm::scale(
        MMatrix,
        glm::vec3(2,2,2) 
    );


    //Draw the skybox
    glm::mat4 skyboxMMatrix = glm::mat4(10.f);

    _skybox.draw(_PROJECTION_MATRIX, VMatrix, skyboxMMatrix, currentLights);

    //Draw the score
    _text.draw(
        "Score : "+std::to_string(game._player.getScore()),
        glm::vec2(50.f, 600.f ),
        glm::vec3(1.f),
        _TEXT_PROJECTION_MATRIX
    );
}