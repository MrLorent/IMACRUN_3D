#include "Game.hpp"

Game::Game()
    :_camera(Camera()),
     _running(false),
     _paused(false),
     _caseSubdivisions(75.f),
     _caseSubdivisionsIndex(0),
     _turn(0),
     _distanceFromWall(3)
{
}

void Game::initGame()
{
    _map = Map();
    _player = Player();
}

void Game::runGame()
{
    checkPlayerPosition();

    if(!_paused && _player.isALive())
    {
        _caseSubdivisionsIndex++;

        if(_caseSubdivisionsIndex == _caseSubdivisions){
            _map.incrementIndex();
            _caseSubdivisionsIndex = 0;
            if(_turn != 0) _distanceFromWall--;
        }
    }
}

void Game::checkPlayerPosition()
{
    unsigned int playerIndex = _map.getIndex();
    const char currentCase = _map[playerIndex * _map.getMapWidth() + _map.getMapWidth()/2 - _player.getPosition().x];
    
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

    if(_turn == 0 && (_map[playerIndex * _map.getMapWidth() + _map.getMapWidth()-1] != Map::WALL))
    {
        _turn = Player::LEFT;
    }
    else if(_turn == 0 && (_map[playerIndex * _map.getMapWidth()] != Map::WALL))
    {
        _turn = Player::RIGHT;
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
                if(_turn == Player::LEFT){
                    _player._turning = Player::LEFT;
                    _map[(_map.getIndex()+(3-_distanceFromWall)) * _map.getMapWidth() + _map.getMapWidth() - 1] = 'f';
                    _map[(_map.getIndex()+(2-_distanceFromWall)) * _map.getMapWidth() + _map.getMapWidth() - 1] = 'f';
                    _map[(_map.getIndex()+(1-_distanceFromWall)) * _map.getMapWidth() + _map.getMapWidth() - 1] = 'f';
                    _map[(_map.getIndex()+_distanceFromWall-5) * _map.getMapWidth() + 1] = 'w';
                    _map[(_map.getIndex()+_distanceFromWall-5) * _map.getMapWidth() + 2] = 'w';
                    _map[(_map.getIndex()+_distanceFromWall-5) * _map.getMapWidth() + 3] = 'w';

                    _player.setPosition(glm::vec3(2 - _distanceFromWall, 0.f, 0.f));

                    _turn = 0; /* The user passed the turn obstacle */
                    _map.setIndex(_map.getIndex() + _distanceFromWall + 1);
                    _distanceFromWall = 3;
                    _camera.rotateHorizontaly(-_player._turning * 90);
                }
                else _player.goLeft();
            }
            break;
        case 68:
            if(action!=0){
                if(_turn == Player::RIGHT){
                    _player._turning = Player::RIGHT;
                    _map[(_map.getIndex()+(3-_distanceFromWall)) * _map.getMapWidth()] = 'f';
                    _map[(_map.getIndex()+(2-_distanceFromWall)) * _map.getMapWidth()] = 'f';
                    _map[(_map.getIndex()+(1-_distanceFromWall)) * _map.getMapWidth()] = 'f';
                    _map[(_map.getIndex()+_distanceFromWall-5) * _map.getMapWidth() + 1] = 'w';
                    _map[(_map.getIndex()+_distanceFromWall-5) * _map.getMapWidth() + 2] = 'w';
                    _map[(_map.getIndex()+_distanceFromWall-5) * _map.getMapWidth() + 3] = 'w';
                    
                    _player.setPosition(glm::vec3(-2 + _distanceFromWall, 0.f, 0.f));
                    
                    _turn = 0; /* The user passed the turn obstacle */
                    _map.setIndex(_map.getIndex() + _distanceFromWall + 1);
                    _distanceFromWall = 3;
                    _camera.rotateHorizontaly(-_player._turning * 90);
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