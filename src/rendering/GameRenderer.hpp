#pragma once
#define MAP_RENDERER_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.hpp"

class GameRenderer
{
private:
    // ATTRIBUTS

    glimac::FilePath _applicationPath;

    Model _player;
    Model _tile;
    Model _hole;
    Model _wall;

    // PRIVATE METHODS

    void load3DModels();

public:
    GameRenderer(){}
    GameRenderer(glimac::FilePath applicationPath);

    void render(
        glm::mat4 projectionMatrix,
        glm::mat4 viewMatrix,
        glm::vec3 playerPosition,
        std::vector<char> map
    );
};
