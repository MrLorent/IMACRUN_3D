#pragma once
#define CAMERA_HPP

#include <iostream>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
    short unsigned int _state;
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
        UNLOCKED = 1
    };
    enum CAMERA_MODE
    {
        TRACKBALL = 0,
        FREEFLY = 1
    };

    short unsigned int _mode;
    short int _turning;

    Camera(){};
    Camera(short unsigned int caseSubdivisions);
    ~Camera();

    // GETTERS

    inline short unsigned int getState() const { return _state; }

    // SETTERS

    // TRACKBALLCAMERA

    void changeDistance(float delta);

    // FREEFLY CAMERA

    void setPosition(glm::vec3 position);
        glm::vec3 getPosition(){
        return _position;
    };
    
    // COMMON METHODS
    void switchMode();
    void switchState();
    void takeTurn();
    void rotateHorizontaly(float degrees);
    void rotateVerticaly(float degrees);
    glm::mat4 getViewMatrix() const;
    void saveSettings();
};
