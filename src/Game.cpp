#include "Game.hpp"

Game::Game(glimac::FilePath applicationPath)
    :_camera(Camera()),
     _renderer(GameRenderer(applicationPath)),
     _running(false)
{
}

void Game::initGame()
{
    _renderer.load3DModels();
    _map = Map();
    _player = Player();
}

void Game::runGame(glm::mat4& projectionMatrix)
{
    // RENDERING
    _renderer.render(
        projectionMatrix,
        _camera.getViewMatrix(),
        _player.position,
        _map
    );
}

void Game::key_callback(int key, int scancode, int action, int mods)
{
    switch (key)
        {
        case 256: //ECHAP
            _running = false;
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