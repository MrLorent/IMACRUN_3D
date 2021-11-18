#pragma once

#include "glm.hpp"
#include <iostream>

namespace glimac 
{
    class FreelyCamera
    {
        private:
        glm::vec3 m_Position;
        float m_fPhi;
        float m_fTheta;
        glm::vec3 m_FrontVector;
        glm::vec3 m_LeftVector;
        glm::vec3 m_UpVector;

        void computeDirectionVectors();

        public:
        FreelyCamera();
        ~FreelyCamera();

        // METHODES
        glm::mat4 getViewMatrix() const;
        void moveSide(float t);
        void moveFront(float t);
        void rotateSide(float degrees);
        void rotateUp(float degrees);
    };
}