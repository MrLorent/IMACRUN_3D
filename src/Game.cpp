#include "Game.hpp"

Game::Game(glimac::FilePath applicationPath)
    :_applicationPath(applicationPath),
     _camera(Camera()),
     _viewMatrix(_camera.getViewMatrix()),
     _finished(false)
{
    load();
}

void Game::load()
{
    /* Initialisation of the Player and loading of the 3D model */
    _player = Player(_applicationPath);

    // A PARTIR DE LA C'EST DEGUEU
    _map = std::vector<char>(18,'f');
    ModelParams floorParams(
        _applicationPath,
        "box/box.obj",
        "triangle.vs.glsl",
        "triangle.fs.glsl"
    );
    _floor = Model(floorParams);
}

void Game::render(glm::mat4& projectionMatrix)
{
    _viewMatrix = _camera.getViewMatrix();
    _player.draw(projectionMatrix, _viewMatrix);
    for(unsigned int i=0; i<_map.size(); i++)
    {
        glm::mat4 MVMatrix = glm::mat4(1.0);

        glm::vec3 xTranslate;

        if((i+1)%3 == 1){
            xTranslate = glm::vec3(-1.0, 0.0, 0.0);
        }else if((i+1)%3 == 0){
            xTranslate = glm::vec3(1.0, 0.0, 0.0);
        }else{
            xTranslate = glm::vec3(0.0);
        }

        MVMatrix = glm::translate(
            MVMatrix,
            xTranslate
        );

        glm::vec3 zTranslate = glm::vec3(0.0,0.0,i/3);

        MVMatrix = glm::translate(
            MVMatrix,
            zTranslate
        );

        MVMatrix = _viewMatrix * MVMatrix;
        _floor.draw(projectionMatrix, MVMatrix);
    }
}

void Game::key_callback(int key, int scancode, int action, int mods)
{
    switch (key)
        {
        case 256: //ECHAP
            _finished = true;
            break;
        case 'C': case 'c':
            if(action!=0)
            {
                _camera.switchMode();
            }
        case 262: //Fleche droite
            if(action!=0){
                _camera.rotateHorizontaly(-2.*float(1));
            }
            break;

        case 263: //Fleche gauche
            if(action!=0){
                _camera.rotateHorizontaly(2.*float(1));
            }
            break;

        case 264: //Fleche bas
            if(action!=0){
                _camera.rotateVerticaly(-2.*float(1));
            }
            break;
        
        case 265: //Fleche haut
            if(action!=0){
                _camera.rotateVerticaly(2.*float(1));
            }
            break;
        default:
            std::cout << key << std::endl;
            break;
        }
}

void Game::mouse_button_callback(int button, int action, int mods)
{
}

void Game::scroll_callback(double xoffset, double yoffset)
{
    _camera.changeDistance(yoffset);
}

void Game::cursor_position_callback(double xpos, double ypos)
{
}