#include "MapRenderer.hpp"

MapRenderer::MapRenderer(glimac::FilePath applicationPath)
    :_applicationPath(applicationPath)
{
    load3DModels();
}

void MapRenderer::load3DModels()
{
    ModelParams params(_applicationPath);

    // LOADING OF THE PLAYER MODEL
    params._fileName = "knight/alliance.obj";
    params._vsShader = "triangle.vs.glsl";
    params._fsShader = "triangle.fs.glsl";

    _player = Model(params);

    // LOADING OF THE TILE MODEL
    params._fileName = "box/box.obj";
    params._vsShader = "triangle.vs.glsl";
    params._fsShader = "triangle.fs.glsl";

    _tile = Model(params);
}

void MapRenderer::render(
    glm::mat4 projectionMatrix,
    glm::mat4 viewMatrix,
    glm::vec3 playerPosition,
    std::vector<char> map
)
{
    // DRAW THE PLAYER
    /* Place the Player Model into the scene */
    glm::mat4 MVMatrix = glm::mat4(1.f); 
    MVMatrix = glm::rotate(
        MVMatrix,
        float(M_PI),
        glm::vec3(0.f,1.f,0.f)
    );

    /* Move the scene according to the camera */
    MVMatrix = viewMatrix * MVMatrix;

    _player.draw(projectionMatrix, MVMatrix);

    // DRAW THE MAP
    for(unsigned int i=0; i<map.size(); i++)
    {
        MVMatrix = glm::mat4(1.f);

        glm::vec3 xTranslate;

        if((i+1)%3 == 1){
            xTranslate = glm::vec3(-1.0, 0.0, 0.0);
        }else if((i+1)%3 == 0){
            xTranslate = glm::vec3(1.0, 0.0, 0.0);
        }else{
            xTranslate = glm::vec3(0.0);
        }

        MVMatrix = glm::translate(
            MVMatrix,
            xTranslate
        );

        glm::vec3 zTranslate = glm::vec3(0.0,0.0,i/3);

        MVMatrix = glm::translate(
            MVMatrix,
            zTranslate
        );

        /* Move the scene according to the camera */
        MVMatrix = viewMatrix * MVMatrix;
        _tile.draw(projectionMatrix, MVMatrix);
    }
}