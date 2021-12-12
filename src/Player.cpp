#include "Player.hpp"

Player::Player()
    :_position(glm::vec3(0.f, 0.f, 0.f))
{
}

// GETTER
glm::vec3 Player::getPosition()
{
    return _position;
}

// SETTER
void Player::goLeft()
{
    if(_position.x != -1) _position.x -= 1;
}

void Player::goRight()
{
    if(_position.x != 1) _position.x += 1;
}

// Player::~Player()
// {
// }