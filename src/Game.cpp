#include "Game.hpp"

Game::Game()
    :_camera(Camera()),
     _running(false),
     _paused(false),
     _isInLeftTurn(false),
     _isInRightTurn(false),
     _distanceFromWall(0)
{
}

//  GETTERS
Player& Game::getPlayer()
{
    return _player;
}

Map& Game::getMap()
{
    return _map;
}

void Game::initGame()
{
    _map = Map();
    _player = Player();
}

void Game::runGame()
{
    checkPlayerPosition();
}

void Game::checkPlayerPosition()
{
    const char currentCase = _map[_map.getIndex() * _map.getMapWidth() + _map.getMapWidth()/2 - _player.getPosition().x];
    
    switch (currentCase)
    {
    case Map::FLOOR:
        break;
    case Map::WALL:
        _player.die();
        break;
    case Map::HOLE:
        _player.die();
        break;
    default:
        break;
    }

    if(!_isInLeftTurn && (_map[_map.getIndex() * _map.getMapWidth() + _map.getMapWidth()-1] != Map::WALL))
    {
        _isInLeftTurn = true;
        _distanceFromWall = 3;
    }else if(_isInLeftTurn && (_map[_map.getIndex() * _map.getMapWidth() + _map.getMapWidth()-1] == Map::WALL))
    {
        _isInLeftTurn = false;
        _distanceFromWall = 0;
    }
    if(!_isInRightTurn && (_map[_map.getIndex() * _map.getMapWidth()] != Map::WALL))
    {
        _isInRightTurn = true;
        _distanceFromWall = 3;
    }else if(_isInRightTurn && (_map[_map.getIndex() * _map.getMapWidth()] == Map::WALL))
    {
        _isInRightTurn = false;
        _distanceFromWall = 0;
    }
}

void Game::key_callback(int key, int scancode, int action, int mods)
{
    switch (key)
        {
        case 256: //ECHAP
            _running = false;
            break;
        case 80: // 'P'
            if(action!=0)
            {
                if(_paused) _paused = false;
                else _paused = true;
            }
            break;
        case 67: // 'C'
            if(action!=0) _camera.switchMode(); 
            break;
        case 65: // 'Q'
            if(action!=0){
                if(_isInLeftTurn){
                    _player._turning = Player::LEFT;
                    _map.setIndex(_map.getIndex() + _distanceFromWall + 1);
                }
                else _player.goLeft();
            }
            break;
        case 68:
            if(action!=0){
                if(_isInRightTurn){
                    _player._turning = Player::RIGHT;
                    _map.setIndex(_map.getIndex() + _distanceFromWall + 1);
                }
                else _player.goRight();
            }
            break;
        case 262: //Fleche droite
            if(action!=0) _camera.rotateHorizontaly(-2.*float(1));
            break;

        case 263: //Fleche gauche
            if(action!=0) _camera.rotateHorizontaly(2.*float(1));
            break;

        case 264: //Fleche bas
            if(action!=0) _camera.rotateVerticaly(-2.*float(1));
            break;
        
        case 265: //Fleche haut
            if(action!=0) _camera.rotateVerticaly(2.*float(1));
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