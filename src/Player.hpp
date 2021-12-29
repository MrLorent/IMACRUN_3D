#pragma once
#define PLAYER_HPP

#include <iostream>
#include "glm/glm.hpp"

class Player
{
    private:
        glm::vec3 _position;
        unsigned int _score;

        unsigned int _jumpingIndex;
        unsigned int _jumpingTiming;
        unsigned int _crouchingIndex;
        unsigned int _crouchingTiming;
    public:
        // CONSTANTS
        static constexpr int LEFT = -1;
        static constexpr int MIDDLE = 0;
        static constexpr int RIGHT = 1;

        bool _isJumping;
        bool _isCrouching;

        Player(){}
        Player(short unsigned int caseSubdivision);
        // ~Player();

        // GETTER
        glm::vec3 getPosition() const;
        unsigned int getScore()const;

        // SETTER
        void setPosition(const glm::vec3 newPosition);
        void setScore(const int score);
        void goLeft();
        void goRight();

        // METHOD
        void jump();
        void crouch();
        void upScore();
};
