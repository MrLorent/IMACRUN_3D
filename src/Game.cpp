#include "Game.hpp"

Game::Game(glimac::FilePath applicationPath)
    :_applicationPath(applicationPath),
     _camera(glimac::TrackballCamera())
{
    load();
}

void Game::load()
{
    _player = Player(_applicationPath);
}

void Game::render(glm::mat4& projectionMatrix)
{
    glm::mat4 MVMatrix = _camera.getViewMatrix();
    _player.draw(projectionMatrix, MVMatrix);
}