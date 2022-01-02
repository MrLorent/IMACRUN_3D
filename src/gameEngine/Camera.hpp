#pragma once
#define CAMERA_HPP

#include <iostream>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
    short unsigned int _state;
    short unsigned int _mode;
    short int _rotationDirection;
    unsigned int _rotationIndex;
    unsigned int _rotationDuration;

    // TRACKBALL ATTRIBUTS
    float _distance;
    float _xAngle;
    float _yAngle;
    float _savedXAngle;
    float _savedYAngle;

    // FREEFLY ATTRIBUTS
    glm::vec3 _position;
    /* look direction */
    float _phi;
    float _theta;
    float _savedPhi;
    float _savedTheta;
    /* spacial direction */
    glm::vec3 _frontVector;
    glm::vec3 _leftVector;
    glm::vec3 _upVector;

    void computeDirectionVectors();

public:
    // CONSTANTS
    enum CAMERA_STATE
    {
        LOCKED = 0,
        UNLOCKED = 1,
        TURNING = 2
    };
    enum CAMERA_MODE
    {
        TRACKBALL = 0,
        FREEFLY = 1
    };

    // CONSTRUCTORS
    /* basic constructors */

    Camera(){};
    Camera(const unsigned short int caseSubdivisions);

    // DESTRUCTOR

    ~Camera();

    // GETTERS

    inline short unsigned int getState() const { return _state; }
    inline short unsigned int getMode() const { return _mode; }
    inline short int getRotationDirection() const { return _rotationDirection; }

    // SETTERS

    void setState(const short unsigned int newState);
    void setRotationDirection(const short int direction);

    // METHODS

    void changeDistance(const float delta);
    void setPosition(const glm::vec3 position);
    glm::vec3 getPosition() const {
        return _position;
    };
    void switchMode();
    void toggleCameraLock();
    void takeTurn();
    void rotateHorizontaly(const float degrees);
    void rotate90Horizontaly(const short int direction);
    void rotateVerticaly(const float degrees);
    glm::mat4 getViewMatrix() const;
    void saveSettings();
};
