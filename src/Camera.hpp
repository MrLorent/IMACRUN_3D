#pragma once
#define CAMERA_HPP

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

const short unsigned int TRACKBALL = 0;
const short unsigned int FREELY = 1;

class Camera
{
private:
    // TRACKBALL ATTRIBUTS
    float _distance;
    float _xAngle;
    float _yAngle;

    // FREELY ATTRIBUTS
    glm::vec3 _position;
    /* look direction */
    float _phi;
    float _theta;
    /* spacial direction */
    glm::vec3 _frontVector;
    glm::vec3 _leftVector;
    glm::vec3 _upVector;

    void computeDirectionVectors();

public:
    short unsigned int _mode;

    Camera();
    ~Camera();

    void switchMode();

    // TRACKBALLCAMERA

    void changeDistance(float delta);

    // FREELY CAMERA

    void moveSide(float t);
    void moveFront(float t);
    
    // COMMON METHODS

    void rotateHorizontaly(float degrees);
    void rotateVerticaly(float degrees);
    glm::mat4 getViewMatrix() const;
};
