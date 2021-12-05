#include "Game.hpp"

Game::Game(glimac::FilePath applicationPath)
    :_applicationPath(applicationPath),
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

void Game::render(glm::mat4& projectionMatrix)
{
    _MVMatrix = _camera.getViewMatrix();
    _model.draw(projectionMatrix, _MVMatrix);
}