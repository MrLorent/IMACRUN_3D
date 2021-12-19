#include "Player.hpp"

Player::Player(short unsigned int caseSubdivision)
    :_position(glm::vec3(0.f, 0.f, 0.f)),
     _isALive(true),
     _isJumping(false),
     _jumpingIndex(0),
     _jumpingTiming(caseSubdivision * 4.5)
{}

// GETTER
glm::vec3 Player::getPosition()
{
    return _position;
}

bool Player::isALive()
{
    return _isALive;
}

// SETTER
void Player::setPosition(glm::vec3 newPosition)
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

void Player::die()
{
    _isALive = false;
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

// Player::~Player()
// {
// }