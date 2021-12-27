#include "Game.hpp"

Game::Game()
    :_caseSubdivisions(75.f),
     _caseSubdivisionsIndex(0),
     _defaultIndex(3),
     _playerIndex(_defaultIndex),
     _running(false),
     _paused(false),
     _finished(false),
     _turn(0),
     _wallDistance(3)
{}

bool Game::isRunning()
{
    return _running && !_paused && !_finished;
}

void Game::initGame()
{
    _playerIndex = _defaultIndex;
    _turn = 0;
    _camera = Camera(_caseSubdivisions);
    _map = Map();
    _player = Player(_caseSubdivisions);
}

void Game::runGame()
{
    checkPlayerPosition();

    if(!_paused && !_finished)
    {
        _caseSubdivisionsIndex++;

        if(_caseSubdivisionsIndex == _caseSubdivisions){
            if(_playerIndex == _defaultIndex)
            {
                _map.deleteFirstLigne();
            }else if(_playerIndex < _defaultIndex){
                _playerIndex++;
            }else{
                _playerIndex--;
                _map.deleteFirstLigne();
            }
            _caseSubdivisionsIndex = 0;
            if(_map.size() < 80 && _map.size()%_map.getMapWidth() == 0) _map.reloadMap();

            if(_turn != 0) _wallDistance--;
        }
    }
}

void Game::checkPlayerPosition()
{
    const char currentCase = _map[_playerIndex * _map.getMapWidth() + _map.getMapWidth()/2 - _player.getPosition().x];
    
    switch (currentCase)
    {
    case Map::FLOOR:
        break;
    case Map::WALL:
        _finished = true;
        _paused = true;
        break;
    case Map::HOLE:
        if(_player.getPosition().y == 0)
        {
            _finished = true;
            _paused = true;
        }
        break;
    default:
        break;
    }

    if(_turn == 0 && (_map[_playerIndex * _map.getMapWidth() + _map.getMapWidth()-1] == Map::FLOOR))
    {
        _turn = Player::LEFT;
    }
    else if(_turn == 0 && (_map[_playerIndex * _map.getMapWidth()] == Map::FLOOR))
    {
        _turn = Player::RIGHT;
    }
}

void Game::passTurn()
{
    if(_turn == LEFT)
    {
        _camera._turning = RIGHT; /* Camera turns on opposite side */
        _map[(_playerIndex-(3-_wallDistance)) * _map.getMapWidth() + _map.getMapWidth() - 1] = 'p';
        _map[(_playerIndex-(2-_wallDistance)) * _map.getMapWidth() + _map.getMapWidth() - 1] = 'p';
        _map[(_playerIndex-(1-_wallDistance)) * _map.getMapWidth() + _map.getMapWidth() - 1] = 'p';
    }
    else
    {
        _camera._turning = LEFT;
        _map[(_playerIndex-(3-_wallDistance)) * _map.getMapWidth()] = 'p';
        _map[(_playerIndex-(2-_wallDistance)) * _map.getMapWidth()] = 'p';
        _map[(_playerIndex-(1-_wallDistance)) * _map.getMapWidth()] = 'p';
    }

    _map[(_playerIndex+_wallDistance) * _map.getMapWidth() + 1] = 'f';
    _map[(_playerIndex+_wallDistance) * _map.getMapWidth() + 2] = 'f';
    _map[(_playerIndex+_wallDistance) * _map.getMapWidth() + 3] = 'f';
    _map[(_playerIndex+_wallDistance-5) * _map.getMapWidth() + 1] = 'w';
    _map[(_playerIndex+_wallDistance-5) * _map.getMapWidth() + 2] = 'w';
    _map[(_playerIndex+_wallDistance-5) * _map.getMapWidth() + 3] = 'w';

    short int xPlayerPosition = _player.getPosition().x;
    switch (xPlayerPosition)
    {
    case Player::LEFT:
        if(_camera._turning == RIGHT)
        {
            if(_wallDistance == 3) _playerIndex += 2;
            else if(_wallDistance == 2 ) _playerIndex += 1;
        }
        else
        {
            if(_wallDistance == 2) _playerIndex -= 1;
            else if(_wallDistance == 1) _playerIndex -= 2;
        }
        break;
    case Player::MIDDLE:
        if(_camera._turning == RIGHT)
        {
            if(_wallDistance == 3) _playerIndex += 1;
            else if(_wallDistance == 1) _playerIndex -= 1;
        }
        else
        {
            if(_wallDistance == 3) _playerIndex += 1;
            else if(_wallDistance == 1) _playerIndex -= 1;
        }
        break;
    case Player::RIGHT:
        if(_camera._turning == RIGHT)
        {
            if(_wallDistance == 2) _playerIndex -= 1;
            else if(_wallDistance == 1) _playerIndex -= 2;
        }
        else
        {
            if(_wallDistance == 3) _playerIndex += 2;
            else if(_wallDistance == 2 ) _playerIndex += 1;
        }
        break;
    default:
        break;
    }

    _player.setPosition(glm::vec3(_turn * (-2 + _wallDistance), 0.f, 0.f));

    if(_camera._mode == Camera::TRACKBALL) _camera.rotateHorizontaly(_camera._turning * 90);
    else _camera.rotateHorizontaly(_turn * 90);

    /* The user passed the turn obstacle */
    _turn = 0;
    _wallDistance = 3;
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
                if(_turn == LEFT) passTurn();
                else _player.goLeft();
                if(_camera._mode == Camera::FREELY) _camera.setPosition(_player.getPosition());
            }
            break;
        case 68:
            if(action!=0){
                if(_turn == Player::RIGHT) passTurn();
                else _player.goRight();
                if(_camera._mode == Camera::FREELY) _camera.setPosition(_player.getPosition());
            }
            break;
        case 32: // SPACEBAR
            _player._isJumping = true;
            break;
        case 262: //Fleche droite
            if(action!=0 && _camera._mode == Camera::TRACKBALL) _camera.rotateHorizontaly(-2.*float(1));
            break;

        case 263: //Fleche gauche
            if(action!=0 && _camera._mode == Camera::TRACKBALL) _camera.rotateHorizontaly(2.*float(1));
            break;

        case 264: //Fleche bas
            if(action!=0 && _camera._mode == Camera::TRACKBALL) _camera.rotateVerticaly(-2.*float(1));
            break;
        
        case 265: //Fleche haut
            if(action!=0 && _camera._mode == Camera::TRACKBALL) _camera.rotateVerticaly(2.*float(1));
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