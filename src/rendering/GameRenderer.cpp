#include "GameRenderer.hpp"

GameRenderer::GameRenderer(glimac::FilePath applicationPath)
    :_applicationPath(applicationPath),
     _renderingLength(24), // nb ligne to draw
     _rotationDirection(0),
     _rotatingIndex(0)
{
    /* Initialization of the 3D Models */
    load3DModels();
    
    /* Initialization of the fonts */
    _text = Text2D(20, _applicationPath, "PTMono.ttc");
}

void GameRenderer::load3DModels()
{
    ModelParams params(_applicationPath);

    // LOADING OF THE PLAYER MODEL
    params.fileName = "wizard/wizard.obj";
    params.vsShader = "model.vs.glsl";
    params.fsShader = "model.fs.glsl";

    _player = Model(params);

    // LOADING OF THE TILE MODEL
    params.fileName = "Cobblestones/CobbleStones.obj";
    params.vsShader = "model.vs.glsl";
    params.fsShader = "model.fs.glsl";
 
    _floor = Model(params);

    //LOADING OF THE WALL MODEL
    params.fileName = "wall/wall.obj";
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

    //LOADING OF THE ARCH MODEL
    params.fileName = "gate_1/gate_1.obj";
    params.vsShader = "model.vs.glsl";
    params.fsShader = "model.fs.glsl"; 
 
    _arch = Model(params);   

    //LOADING OF THE PLANK MODEL
    params.fileName = "plank/plank.obj";
    params.vsShader = "model.vs.glsl";
    params.fsShader = "model.fs.glsl"; 
 
    _plank = Model(params);   
 
    //LOADING OF THE SKYBOX MODEL
    params.fileName = "skybox/skybox.obj";
    params.vsShader = "skybox.vs.glsl";
    params.fsShader = "skybox.fs.glsl";
 
    _skybox = Model(params);
}

void GameRenderer::drawMap(Game& game, glm::mat4& VMatrix)
{
    for(size_t i=0; i<game._map.firstLights.size(); ++i)
    {
        currentLights[i] = game._map.firstLights[i];
    }
    firstlightsInit = false;

    glm::mat4 MMatrix = glm::translate(
        glm::mat4(1.f),
        glm::vec3(
            -2.f, /* Place of the first left wall */
            0.f,
            0.5 - game.getPlayerIndex() - game.getCaseSubdivisionIndex() / game.getCaseSubdivision()
        ) 
    );
   // matrix matrice= matrix(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);
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
                    drawWall(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights); 
                    break;
                case Map::LIGHT_MARKER:
                    setLights(MMatrix,game._map.firstLights, currentLights, k);
                    drawWall(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);
                    break;
                case Map::LIGHT: //Mal positionnée
                    drawLantern(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);
                    break; 
                case Map::HOLE:  
                    break; 
                case Map::BAREL:
                    drawBarel(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);
                    break;
                case Map::COLLECTIBLE:
                    drawBottle(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);
                    break;
                case Map::ARCH:
                    _floor.draw(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);
                    if(k==1){
                        drawArch(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);
                    }
                    break;
                case Map::PLANK: 
                    _floor.draw(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);
                    if(k==2){
                        drawPlank(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);
                    }
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
}



void GameRenderer::drawPlayer(Game& game,Player& player, glm::mat4& VMatrix)
{
    /* turn back the model from the camera */
        glm::mat4 MMatrix = glm::rotate(
            glm::mat4(1.f),
            float(M_PI),
            glm::vec3(0.f,1.f,0.f)
        );
    /* put the player model at the right position */
        MMatrix = glm::translate(
            MMatrix,
            player.getPosition()
        );

    if(player._isCrouching){
        /* Move the player model according to the camera */
        game._camera.setPosition(glm::vec3(game._player.getPosition().x, (game._player.getPosition().y)-0.5 ,game._player.getPosition().z-0.1));
        MMatrix = glm::translate(
            MMatrix,
            glm::vec3(0.f, 0.5f, 0.f)
        );

        MMatrix=glm::scale(
            MMatrix,
            glm::vec3(0.5,0.5,0.5)
        );
    }else{
         game._camera.setPosition(game._player.getPosition()+ glm::vec3(0.,0.,-0.1));
        /* Move the player model according to the camera */
        MMatrix = glm::translate(
            MMatrix,
            glm::vec3(0., 0.8, 0)
        );
    }
    _player.draw(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);
}

void GameRenderer::drawSkyBox(glm::mat4& VMatrix)
{
    glm::mat4 id(1.f);
    _skybox.draw(
        _PROJECTION_MATRIX,
        id,
        glm::mat4(10.f),
        currentLights
    );
}

void GameRenderer::setLights(glm::mat4& MMatrix,std::vector<glm::vec3>& firstLights, std::deque<glm::vec3>& lights, const short unsigned int rank)
{
    MMatrix = glm::translate(
        MMatrix,
        glm::vec3(0.f, 0.f, 5.5f)
    );

    if(rank == 0)
    {
        lights[0] = glm::vec3(glm::column(MMatrix, 3));
        if(!firstlightsInit) firstLights[0] = lights[0]; 
    }
    else
    {
        lights[1] = glm::vec3(glm::column(MMatrix, 3));
        if(!firstlightsInit)
        {
            firstLights[1] = lights[1];
            firstlightsInit = true;
        }
    }

    MMatrix = glm::translate(
        MMatrix,
        glm::vec3(0.f, 0.f, -5.5f)
    );
}

void GameRenderer::drawWall(//a voir si matrice par reference
    glm::mat4 &_PROJECTION_MATRIX,
    glm::mat4 &VMatrix,
    glm::mat4 &MMatrix,
    std::deque<glm::vec3> &currentLights
    )
    {
    MMatrix = glm::translate(
        MMatrix,
        glm::vec3(0.05f,0.5f,0.f)
    );                    

    _wall.draw(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);

    MMatrix = glm::translate(
        MMatrix,
        glm::vec3(-0.05f,-0.5f,0.f) 
    );

    /*
     matrice.MMatrix = glm::translate(
        matrice.MMatrix,
        glm::vec3(0.05f,0.5f,0.f)
    );                    

    _wall.draw(matrice._PROJECTION_MATRIX, matrice.VMatrix, matrice.MMatrix, matrice.currentLights);

    matrice.MMatrix = glm::translate(
        matrice.MMatrix,
        glm::vec3(-0.05f,-0.5f,0.f) 
    );*/
}

void GameRenderer::drawBarel(
    glm::mat4 &_PROJECTION_MATRIX,
    glm::mat4 &VMatrix,
    glm::mat4 &MMatrix,
    std::deque<glm::vec3> &currentLights
    ){
        _floor.draw(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);
        MMatrix = glm::translate(
            MMatrix,
            glm::vec3(0.f,0.35f,0.f)
        );

        MMatrix=glm::scale(
            MMatrix,
            glm::vec3(0.5,0.5,0.5)
        );
        _barrel.draw(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);

        MMatrix=glm::scale(
            MMatrix,
            glm::vec3(2,2,2)
        );
        MMatrix = glm::translate(
            MMatrix,
            glm::vec3(0.f,-0.35f,0.f)
        );
    }

 void GameRenderer::drawLantern(
    glm::mat4 &_PROJECTION_MATRIX,
    glm::mat4 &VMatrix,
    glm::mat4 &MMatrix,
    std::deque<glm::vec3> &currentLights){
        drawWall(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);
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
    }

void GameRenderer::drawBottle(
    glm::mat4 &_PROJECTION_MATRIX,
    glm::mat4 &VMatrix,
    glm::mat4 &MMatrix,
    std::deque<glm::vec3> &currentLights){
         _floor.draw(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);
        MMatrix=glm::scale(
            MMatrix,
            glm::vec3(0.25,0.25,0.25)
        );
        _bottle.draw(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);
        MMatrix=glm::scale(
            MMatrix,
            glm::vec3(4,4,4)
        );
    }

void GameRenderer::drawArch(
    glm::mat4 &_PROJECTION_MATRIX,
    glm::mat4 &VMatrix,
    glm::mat4 &MMatrix,
    std::deque<glm::vec3> &currentLights){
        MMatrix = glm::translate(
            MMatrix,
            glm::vec3(1.f,0.f,0.f)
        );
        _arch.draw(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);
        MMatrix = glm::translate(
            MMatrix,
            glm::vec3(-1.f,0.f,0.f)
        );
    }

void GameRenderer::drawPlank(
    glm::mat4 &_PROJECTION_MATRIX,
    glm::mat4 &VMatrix,
    glm::mat4 &MMatrix,
    std::deque<glm::vec3> &currentLights){

        MMatrix = glm::translate(
            MMatrix,
            glm::vec3(0.f,0.9f,0.f)
        );

        _plank.draw(_PROJECTION_MATRIX, VMatrix, MMatrix, currentLights);

        MMatrix = glm::translate(
            MMatrix,
            glm::vec3(0.f,-0.9f,0.f)
        );
    }

void GameRenderer::render(
    Game& game
)
{
    //game._camera.setPosition(game._player.getPosition()+ glm::vec3(0.,0.,-0.1));
    glm::mat4 VMatrix = game._camera.getViewMatrix();
    
    // DRAW THE MAP
    drawMap(game, VMatrix);

    // DRAW THE PLAYER
    drawPlayer(game ,game._player, VMatrix);

    // DRAW THE SKYBOX
    drawSkyBox(VMatrix);

    //Draw the score
    _text.draw(
        "Score : "+std::to_string(game._player.getScore()),
        glm::vec2(50.f, 600.f ),
        glm::vec3(1.f),
        _TEXT_PROJECTION_MATRIX
    );
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