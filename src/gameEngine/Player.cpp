#include "Player.hpp"

Player::Player(const unsigned short int caseSubdivision)
    :_position(glm::vec3(0.f, 0.f, 0.f)),
     _isJumping(false),
     _isCrouching(false), 
     _crouchingIndex(0),
     _crouchingTiming(caseSubdivision * 3.5),
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

void Player::setScore(const int score)
{
    _score = score;
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
        _position.y = 1-(_jumpingIndex - float(_jumpingTiming/2)) * (_jumpingIndex - float(_jumpingTiming/2))/(float(_jumpingTiming/2) * float(_jumpingTiming/2));
        _jumpingIndex++;
    }
}

void Player::crouch()
{
    if(_crouchingIndex == _crouchingTiming){
        _isCrouching= false;
        _crouchingIndex =0;
    }
    else
    {
        _crouchingIndex++;
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