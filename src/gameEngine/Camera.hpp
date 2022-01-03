#pragma once
#define CAMERA_HPP

#include <iostream>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

//! The Camera class contains two different modes : Trackball and Freefly.

class Camera
{
private:
    unsigned short int _state;
    unsigned short int _mode;
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

    //! Constructor
    /*!
     * Constructor by default
     */
    Camera(){};

    //! Constructor
    /*!
    *\fn Camera(const unsigned short int caseSubdivisions)
    *\param caseSubdivisions : Number of steps needed for a map element to move one meter.
    */
    Camera(const unsigned short int caseSubdivisions);

    // DESTRUCTOR

    //! Destructor
    /*!
    * Destructor by default.
    */
    ~Camera();

    // GETTERS

    //! Getter
    /*!
    *\fn inline unsigned short int getState() const
    *\return return the state of the camera (LOCKED or UNLOCKED).
    */
    inline unsigned short int getState() const { return _state; }
    
    //! Getter
    /*!
    *\fn inline unsigned short int getMode() const
    *\return return the mode of the camera (TACKBALL or FREEFLY).
    */
    inline unsigned short int getMode() const { return _mode; }
    
    //! Getter
    /*!
    *\fn inline short int getRotationDirection() const
    *\return the direction in which the camera is turning (LEFT = -1 & RIGHT = 1)
    */
    inline short int getRotationDirection() const { return _rotationDirection; }

    //! Getter
    /*!
    *\fn inline glm::vec3 getPosition()
    *\return the camera position.
    */
    inline glm::vec3 getPosition() const { return _position; };

    // SETTERS

    //! Setter
    /*!
    *\fn void setState(const unsigned short int newState)
    *\param newState : state from enum CAMERA_STATE to switch with. 
    * Setter that change the camera state (LOCKED or UNLOCKED)
    */
    void setState(const unsigned short int newState);

    //! Setter
    /*!
    *\fn void setRotationDirection(const short int direction);
    *\param direction : the direction of the rotation (LEFT = -1 & RIGHT = 1) 
    * Set the rotation direction of the camera.
    */
    void setRotationDirection(const short int direction);

    //! Setter
    /*!
    *\fn void setPosition(const glm::vec3 position);
    *\param position : position to which place the camera 
    * Set the position of the camera.
    */
    void setPosition(const glm::vec3 position);

    // METHODS

    //! Method
    /*!
    *\fn void changeDistance(const float delta)
    * Method that change the distance of the camera from the subject in Trackball mode
    */
    void changeDistance(const float delta);

    //! Method
    /*!
    *\fn void switchMode()
    * Method that switch between Trackball and Freefly mode
    */
    void switchMode();

    //! Method
    /*!
    *\fn void toggleCameraLock()
    * Method that switch between LOCK and UNLOCKED state
    */
    void toggleCameraLock();

    //! Method
    /*!
    *\fn void takeTurn()
    * Method that enable the camera to follow the player after a turn
    */
    void takeTurn();


    //! Method
    /*!
    *\fn void rotateHorizontaly(const float degrees)
    *\param degrees : degree of the rotation angle
    * Method that makes the camera rotate horizontally
    */
    void rotateHorizontaly(const float degrees);

    //! Method
    /*!
    *\fn void rotate90Horizontaly(const short int direction)
    *\param direction : ddirection of the rotation
    * Method that rotate of 90 degres in the direction given
    */
    void rotate90Horizontaly(const short int direction);
    
    //! Method
    /*!
    *\fn void rotateVerticaly(const float degrees)
    *\param degrees : degree of the rotation angle
    * Method that makes the camera rotate vertically
    */
    void rotateVerticaly(const float degrees);

    //! Method
    /*!
    *\fn glm::mat4 getViewMatrix() const
    * Method that compute the ViewMatrix of the camera
    */
    glm::mat4 getViewMatrix() const;

    //! Method
    /*!
    *\fn void saveSettings()
    * Save the parameters set by the user when the camera is unlocked
    */
    void saveSettings();
};
