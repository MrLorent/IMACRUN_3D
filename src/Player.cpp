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

// Player::~Player()
// {
// }