#include "Player.hpp"

Player::Player(short unsigned int caseSubdivision)
    :_position(glm::vec3(0.f, 0.f, 0.f)),
     _isJumping(false),
     _jumpingIndex(0),
     _jumpingTiming(caseSubdivision * 4.5),
     _score(0)
{}

// GETTER
glm::vec3 Player::getPosition() const
{
    return _position;
}

// SETTER
void Player::setPosition(const glm::vec3 newPosition)
{
    _position = newPosition;
}

void Player::goLeft()
{
    if(_position.x != -1) _position.x -= 1;
}

void Player::goRight()
{
    if(_position.x != 1) _position.x += 1;
}

// METHODS

void Player::jump()
{
    if(_jumpingIndex == _jumpingTiming)
    {
        _position.y = 0;
        _isJumping = false;
        _jumpingIndex = 0;
    }
    else
    {
        _position.y = 1-(_jumpingIndex - float(_jumpingTiming/2)) * (_jumpingIndex - float(_jumpingTiming/2))/28000.f;
        _jumpingIndex++;
    }
}

unsigned int Player::getScore()const{
    return _score;
}

void Player::upScore(){
    _score++;
}


// Player::~Player()
// {
// }