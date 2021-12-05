#include "Game.hpp"

Game::Game(glimac::FilePath applicationPath, glm::mat4 projectionMatrix)
    :_applicationPath(applicationPath),
     _projectionMatix(projectionMatrix)
{
    load();
}

void Game::load()
{
    // CHARGEMENT DU MODEL
    /* WILL SOON BE IN GAME CLASS */
    ModelParams params(
        _applicationPath,
        "knight/alliance.obj",
        "triangle.vs.glsl",
        "triangle.fs.glsl"
    );
    _model = Model(params);
}

void Game::render(glm::mat4 MVMatrix)
{
    _model.draw(_projectionMatix, MVMatrix);
}