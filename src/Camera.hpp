#pragma once
#define CAMERA_HPP

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

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
    // CONSTANTS
    static constexpr short unsigned int TRACKBALL = 0;
    static constexpr short unsigned int FREELY = 1;

    short unsigned int _mode;

    Camera();
    ~Camera();

    void switchMode();

    // TRACKBALLCAMERA

    void changeDistance(float delta);

    // FREELY CAMERA

    void setPosition(glm::vec3 position);
    
    // COMMON METHODS

    void rotateHorizontaly(float degrees);
    void rotateVerticaly(float degrees);
    glm::mat4 getViewMatrix() const;
};
