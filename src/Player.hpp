#pragma once
#define PLAYER_HPP

#include <iostream>
#include "glm/glm.hpp"

class Player
{
    private:
        glm::vec3 _position;
        bool _isALive;
    public:
        // CONSTANTS
        static constexpr int LEFT = -1;
        static constexpr int MIDDLE = 0;
        static constexpr int RIGHT = 1;

        Player();
        // ~Player();

        // GETTER
        glm::vec3 getPosition();
        bool isALive();

        // SETTER
        void setPosition(glm::vec3 newPosition);
        void goLeft();
        void goRight();
        void die();
};
