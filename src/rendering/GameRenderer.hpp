#pragma once
#define MAP_RENDERER_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.hpp"
#include "Map.hpp"

class GameRenderer
{
private:
    std::vector<glm::mat4> X_TRANSLATE_MATRICES;
    
    // ATTRIBUTS

    glimac::FilePath _applicationPath;
    unsigned int _renderingLength;

    /* 3D Models */
    Model _player;
    Model _wall;
    Model _floor;

    // PRIVATE METHODS

    void load3DModels();

public:
    GameRenderer(){}
    GameRenderer(glimac::FilePath applicationPath);

    void render(
        glm::mat4 projectionMatrix,
        glm::mat4 viewMatrix,
        glm::vec3 playerPosition,
        Map& map
    );
};
