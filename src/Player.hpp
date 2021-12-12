#pragma once
#define PLAYER_HPP

#include "glm/glm.hpp"

class Player
{
    private:
        glm::vec3 _position;
    public:
        Player();

        // GETTER
        glm::vec3 getPosition();
        // ~Player();
};
