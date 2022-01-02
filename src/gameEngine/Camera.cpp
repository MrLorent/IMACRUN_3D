#include "Camera.hpp"

// CONSTRUCTOR
/* basic constructor */

Camera::Camera( const unsigned short int caseSubdivisions)
    :_state(LOCKED),
     _mode(TRACKBALL),
     _rotationDirection(0),
     _rotationIndex(0),
     _rotationDuration(caseSubdivisions * 2),
    // TRACKBALL
     _distance(2),
     _xAngle(M_PI / 6),    /* horizontal */
     _yAngle(M_PI),    /* vertical */
     _savedXAngle(M_PI / 6),    /* horizontal */
     _savedYAngle(M_PI),    /* vertical */
    // FREEFLY
     _position(glm::vec3(0.f, 1.f, 0.1f)),
     _phi(0),    /* horizontal */
     _theta(0.f),    /* vertical */
     _savedPhi(0),    /* horizontal */
     _savedTheta(0.f)    /* vertical */
{
    computeDirectionVectors();
}

// DESTRUCTOR

Camera::~Camera(){}

// SETTERS

void Camera::setState(const short unsigned int newState)
{
    switch (_state)
    {
    case LOCKED:
        _state = UNLOCKED;
        break;
    case UNLOCKED:
        saveSettings();
        _state = newState;
        break;
    case TURNING:
        _state = newState;
        break;
    default:
        std::cerr << "Le newState demandé n'existe pas" << std::endl;
        break;
    }
    
}

void Camera::setRotationDirection(const short int direction)
{
    _rotationDirection = direction;
}

// METHODS

void Camera::switchMode()
{
    if(_mode == TRACKBALL)
    {
        _mode = FREEFLY;
    }
    else
    {
        _mode = TRACKBALL;
    }
}

void Camera::toggleCameraLock()
{
    if(_state == Camera::UNLOCKED)
    {
        setState(Camera::LOCKED);
    }
    else if(_state == Camera::LOCKED)
    {
        setState(Camera::UNLOCKED);
    }
}

// TRACKBALL METHODS

void Camera::changeDistance(const float delta)
{
    _distance -= delta;
}

// FREEFLY METHODS

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

void Camera::takeTurn()
{
    if(_rotationIndex > _rotationDuration)
    {
        if(_mode == Camera::TRACKBALL)
        {
            _yAngle = _savedYAngle;
        }
        else
        {
            _phi = _savedPhi;
        }
        _state = LOCKED;
        _rotationIndex = 0;
    }
    else
    {
        if(_mode == TRACKBALL)
        {
            _yAngle += glm::radians(float(90.f * 1/_rotationDuration * -_rotationDirection));
        }
        else
        {
            _phi += glm::radians(float(90.f * 1/_rotationDuration * -_rotationDirection));
        }
        _rotationIndex++;
    }
}

void Camera::rotateHorizontaly(const float degrees)
{
    if(_state == UNLOCKED)
    {
        if(_mode == TRACKBALL)
        {
            _yAngle += glm::radians(degrees);
        }
        else
        {
            _phi += glm::radians(degrees);
            _phi=glm::clamp(_phi, glm::radians(-30.f), glm::radians(30.f));
            computeDirectionVectors();
        }
    }
}

void Camera::rotate90Horizontaly(const short int direction)
{
    if(_mode == TRACKBALL)
    {
        _yAngle += glm::radians(90.f * direction);
    }
    else
    {
        _phi += glm::radians(90.f * direction);
        _phi=glm::clamp(_phi, glm::radians(-30.f), glm::radians(30.f));
        computeDirectionVectors();
    }
}

void Camera::rotateVerticaly(const float degrees)
{
    if(_state == UNLOCKED)
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

void Camera::saveSettings()
{
    _savedXAngle = _xAngle;
    _savedYAngle = _yAngle;

    _savedPhi = _phi;
    _savedTheta = _theta;
}