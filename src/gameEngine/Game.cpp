#include "Game.hpp"

Game::Game()
    :_state(WAITING),
     _caseSubdivisions(50.f),
     _caseSubdivisionsIndex(0),
     _skyBoxMMatrix(glm::mat4(1.f)),
     _defaultIndex(7),
     _playerIndex(_defaultIndex),
     _turn(0),
     _wallDistance(3)
{}

void Game::setState(const short unsigned int newState, const short unsigned int mode)
{
    switch (_state)
    {
    case WAITING:
        if(newState == RUNNING && mode == CLEAR_START)
        {
            /* Initiate game */
            initGame();
        }
        else if(newState == RUNNING && mode == FROM_SAVE)
        {
            initGameFromSave();
        }
        _state = newState;
        break;
    case RUNNING:
        if(newState == PAUSED)
        {
            _state = newState;
        }
        else if(newState == FINISHED)
        {
            _state = newState;
        }
        break;
    case PAUSED:
        if(newState == RUNNING && mode == UNPAUSE)
        {
            _state = RUNNING;
        }
        else if(newState == RUNNING && mode == CLEAR_START)
        {
            initGame();
            _state = RUNNING;
        }
        else
        {
            saveGame();
            _state = WAITING;
        }
        break;
    case FINISHED:
        if(newState == RUNNING)
        {
            initGame();
            _state = RUNNING;
        }
        else
        {
            _state = WAITING;
        }
        break;
    default:
        std::cout << "Defaut case of game.setState()" << std::endl;
        break;
    }
}

void Game::initGame()
{
    _playerIndex = _defaultIndex;
    _turn = 0;
    _camera = Camera(_caseSubdivisions);
    _map = Map();
    _map.initMap();
    _player = Player(_caseSubdivisions);
}


void Game::initGameFromSave(){
    _playerIndex = _defaultIndex;
    _turn = 0;
    _camera = Camera(_caseSubdivisions);
    _map = Map();
    _player = Player(_caseSubdivisions);
    
    /* Initialization of the game */
    std::ifstream file("./saves/save.txt");
    if(file) {
        //Charger score
        int score;
        file >> score;
        _player.setScore(score);

        //Charger position joueur
        float coord;
        glm::vec3 position;
        for (unsigned int i =0 ; i<3 ; i++){
            file >> coord;
            position[i] = coord;
        }
        _player.setPosition(position);

        //Charger Map courrante
        unsigned int mapSize;
        file >> mapSize;
        char caractere;
        for(unsigned int i=0; i < mapSize ; ++i){ 
            file >> caractere; 
            _map.add(caractere);
        }
        file.close();
    }else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
    }
}

void Game::saveGame(){
    
    std::ofstream file;
    std::string const fileName("./saves/save.txt");
    file.open(fileName, std::ios::out | std::ios::binary);

    if(file.is_open())    
    {
        file << _player.getScore() << std::endl;
        file <<  _player.getPosition().x << std::endl;
        file << _player.getPosition().y << std::endl;
        file << _player.getPosition().z << std::endl;
        file << _map.getSize();
        for(size_t i=0; i < _map.getSize(); ++i) { 
            file << _map[i]; 
            if(i%_map.getMapWidth() == _map.getMapWidth()-1) file << std::endl;
        }            
        file.close();
        std::cout << "La partie a ete sauvegardee." << std::endl;  
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }
}

void Game::runGame()
{
    checkPlayerPosition();

    if(_state == RUNNING)
    {
        if(_camera.getState() == Camera::TURNING) _camera.takeTurn();
        if(_player._isJumping) _player.jump();
        else if(_player._isCrouching) _player.crouch();
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
            if(_map.getSize() < 125 && _map.getSize()%_map.getMapWidth() == 0) _map.reloadMap();

            if(_turn != 0) _wallDistance--;
        }
    }
}

void Game::checkPlayerPosition()
{
    char currentCase = _map[_playerIndex * _map.getMapWidth() + _map.getMapWidth()/2 - _player.getPosition().x];
    
    switch (currentCase)
    {
    case Map::FLOOR:
        break;
    case Map::WALL:
        setState(FINISHED, 0);
        break;
    case Map::HOLE:
        if(_player.getPosition().y == 0) setState(FINISHED, 0);
        break;
    case Map::BAREL:
        if(_player.getPosition().y == 0) setState(FINISHED, 0);
        break;
    case Map::COLLECTIBLE:
        if(_player.getPosition().y == 0)
            {
                _player.upScore();
                _map[_playerIndex * _map.getMapWidth() + _map.getMapWidth()/2 - _player.getPosition().x]=Map::FLOOR;
            }
        break;
    case Map::ARCH:
        if(_player.getPosition().x != 0) setState(FINISHED, 0);
        break;
    case Map::PLANK:
        if(!_player._isCrouching || _player._isJumping) setState(FINISHED, 0);
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
        _camera.setRotationDirection(RIGHT); /* Camera turns on opposite side */
        _camera.setState(Camera::TURNING);
        _map[(_playerIndex-(3-_wallDistance)) * _map.getMapWidth() + _map.getMapWidth() - 1] = 'p';
        _map[(_playerIndex-(2-_wallDistance)) * _map.getMapWidth() + _map.getMapWidth() - 1] = 'p';
        _map[(_playerIndex-(1-_wallDistance)) * _map.getMapWidth() + _map.getMapWidth() - 1] = 'p';
    }
    else
    {
        _camera.setRotationDirection(LEFT);
        _camera.setState(Camera::TURNING);
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
        if(_turn == LEFT)
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
        if(_turn == LEFT)
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
        if(_turn == LEFT)
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

    short int cameraTurn;
    if(_camera.getMode() == Camera::TRACKBALL)
    {
        _camera.rotate90Horizontaly(-_turn);
        cameraTurn = -_turn;
    }
    else
    {
        _camera.rotate90Horizontaly(_turn);
        cameraTurn = _turn;
    }

    _skyBoxMMatrix = glm::rotate(
        _skyBoxMMatrix,
        float(cameraTurn * 90),
        glm::vec3(0.f,1.f,0.f)
    );

    /* The user passed the turn obstacle */
    _turn = 0;
    _wallDistance = 3;
}

void Game::key_callback(int key, int scancode, int action, int mods)
{
    switch (key)
        {
        case GLFW_KEY_ESCAPE: //ECHAP 
            if(action != 0) setState(PAUSED, 0);
            break;
        case GLFW_KEY_P: // 'P'
            if(action != 0) setState(PAUSED, 0);
            break;
        case GLFW_KEY_L: // 'L'
            if(action != 0) _camera.toggleCameraLock();
            break;
        case GLFW_KEY_C: // 'C'
            if(action!=0) _camera.switchMode(); 
            break;
        case GLFW_KEY_A: // 'Q'
            if(action!=0){
                if(_turn == LEFT) passTurn();
                else _player.goLeft();
                _camera.setPosition(_player.getPosition());
            }
            break;
        case GLFW_KEY_D:
            if(action!=0){
                if(_turn == Player::RIGHT) passTurn();
                else _player.goRight();
                _camera.setPosition(_player.getPosition());
            }
            break;
        case GLFW_KEY_S: // S
            _player._isCrouching= true;
            break;
        case GLFW_KEY_SPACE: // SPACEBAR
            _player._isJumping = true;
            break;
        case GLFW_KEY_RIGHT: //Fleche droite
            if(action != 0) _camera.rotateHorizontaly(-2.*float(1));
            
            break;

        case GLFW_KEY_LEFT: //Fleche gauche
            if(action != 0) _camera.rotateHorizontaly(2.*float(1));
            break;

        case GLFW_KEY_DOWN: //Fleche bas
            if(action != 0) _camera.rotateVerticaly(-2.*float(1));
            break;
        
        case GLFW_KEY_UP: //Fleche haut
            if(action != 0) _camera.rotateVerticaly(2.*float(1));
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