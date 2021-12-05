#include "Player.hpp"

Player::Player(glimac::FilePath applicationPath)
{
    /* Initialization of the MVMatrix */
    _MVMatrix = glm::translate(
        glm::mat4(1.),
        glm::vec3(0.,0.,-10.)
    );
    
    // CHARGEMENT DU MODEL
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