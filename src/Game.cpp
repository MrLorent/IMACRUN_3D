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
}

void Game::render(glm::mat4& projectionMatrix)
{
    _viewMatrix = _camera.getViewMatrix();
    _player.draw(projectionMatrix, _viewMatrix);
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