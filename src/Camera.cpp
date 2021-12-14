#include "Camera.hpp"

// CONSTRUCTOR
/* basic constructor */

Camera::Camera()
    :_mode(TRACKBALL),
    // TRACKBALL
     _distance(2),
     _xAngle(M_PI / 6),    /* horizontal */
     _yAngle(M_PI),    /* vertical */
    // FREELY
     _position(glm::vec3(0.f, 1.f, 0.f)),
     _phi(0),    /* horizontal */
     _theta(0.f)    /* vertical */
{
    computeDirectionVectors();
}

// DESTRUCTOR

Camera::~Camera(){}

void Camera::switchMode()
{
    if(_mode == TRACKBALL)
    {
        _mode = FREELY;
    }
    else
    {
        _mode = TRACKBALL;
    }
}

// TRACKBALL METHODS

void Camera::changeDistance(float delta)
{
    _distance -= delta;
}

// FREELY METHODS

void Camera::computeDirectionVectors()
{
    _frontVector = glm::vec3(
        glm::cos(_theta) * glm::sin(_phi),
        glm::sin(_theta),
        glm::cos(_theta) * glm::cos(_phi)
    );

    _leftVector = glm::vec3(
        glm::sin(_phi + M_PI * 0.5),
        0,
        glm::cos(_phi + M_PI * 0.5)
    );

    _upVector = glm::cross(
        _frontVector,
        _leftVector
    );
}

void Camera::setPosition(const glm::vec3 position)
{
    _position.x = -position.x;
    _position.y = position.y +1;
    _position.z = -position.z;
}

// COMMON METHODS

void Camera::rotateHorizontaly(float degrees)
{
    if(_mode == TRACKBALL)
    {
        _yAngle += glm::radians(degrees);
    }
    else
    {
        _phi += glm::radians(degrees);
        computeDirectionVectors();
    }
}

void Camera::rotateVerticaly(float degrees)
{
    if(_mode == TRACKBALL)
    {
        _xAngle += glm::radians(degrees);
    }
    else
    {
        _theta += glm::radians(degrees);
        computeDirectionVectors();
    }
}

glm::mat4 Camera::getViewMatrix() const
{
    if(_mode == TRACKBALL)
    {
        glm::mat4 viewMatrix(1.f);

        viewMatrix = glm::translate(
        viewMatrix,
        glm::vec3(
            0.0f,
            -0.75f,
            -_distance)
        );

        viewMatrix = glm::rotate(
            viewMatrix,
            _xAngle,
            glm::vec3(1.0f,0.0f,0.0f)
        );

        viewMatrix = glm::rotate(
            viewMatrix,
            _yAngle,
            glm::vec3(0.0f,1.0f,0.0f)
        );

        return viewMatrix;

    }else{

        return glm::lookAt(
            _position,
            _position + _frontVector,
            _upVector
        );
    }
}