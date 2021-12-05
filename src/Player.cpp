#include "Player.hpp"

Player::Player(glimac::FilePath applicationPath)
{
    // CHARGEMENT DU MODEL DU JOUEUR
    ModelParams params(
        applicationPath,
        "knight/alliance.obj",
        "triangle.vs.glsl",
        "triangle.fs.glsl"
    );
    _model = Model(params);
}

void Player::draw(glm::mat4& projectionMatrix, glm::mat4& MVMatrix)
{
    _MVMatrix = MVMatrix;
    _model.draw(projectionMatrix, _MVMatrix);
}