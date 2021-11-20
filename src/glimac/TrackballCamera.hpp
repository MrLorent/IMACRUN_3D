#pragma once

#include "glm.hpp"
#include <iostream>

namespace glimac
{
    class TrackballCamera
    {
    private:
        float m_fDistance;
        float m_fAngleX;
        float m_fAngleY;
    
    public:
        TrackballCamera();
        ~TrackballCamera();

        // METHODES
        void moveFront(float delta);
        void rotateSide(float degrees);
        void rotateUp(float degrees);
        glm::mat4 getViewMatrix() const;
    };
}