#pragma once
#define PLAYER_HPP

#include <iostream>
#include "glm/glm.hpp"

class Player
{
    private:
        glm::vec3 _position;
    public:
        Player();
        // ~Player();

        // GETTER
        glm::vec3 getPosition();

        // SETTER
        void goLeft();
        void goRight();
};
