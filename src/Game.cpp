#include "Game.hpp"

Game::Game(glimac::FilePath applicationPath, glm::mat4 projectionMatrix)
    :_applicationPath(applicationPath),
     _projectionMatix(projectionMatrix),
     _MVMatrix(glm::mat4(1.)),
     _camera(glimac::TrackballCamera())
{
    /* Initialization of the MVMatrix */
    _MVMatrix = glm::translate(
        glm::mat4(1.),
        glm::vec3(0.,0.,-10.)
    );
    load();
}

void Game::load()
{
    // CHARGEMENT DU MODEL
    ModelParams params(
        _applicationPath,
        "knight/alliance.obj",
        "triangle.vs.glsl",
        "triangle.fs.glsl"
    );
    _model = Model(params);
}

void Game::render()
{
    _MVMatrix = _camera.getViewMatrix();
    _model.draw(_projectionMatix, _MVMatrix);
}