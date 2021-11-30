#include <iostream>
#include "FreelyCamera.hpp"

namespace glimac
{
    FreelyCamera::FreelyCamera()
        :m_Position(glm::vec3(0.f)),
         m_fPhi(M_PI),
         m_fTheta(0.f)
    {
        computeDirectionVectors();
    }

    FreelyCamera::~FreelyCamera(){}

    void FreelyCamera::computeDirectionVectors()
    {
        m_FrontVector = glm::vec3(
            glm::cos(m_fTheta) * glm::sin(m_fPhi),
            glm::sin(m_fTheta),
            glm::cos(m_fTheta) * glm::cos(m_fPhi)
        );

        m_LeftVector = glm::vec3(
            glm::sin(m_fPhi + M_PI * 0.5),
            0,
            glm::cos(m_fPhi + M_PI * 0.5)
        );

        m_UpVector = glm::cross(
            m_FrontVector,
            m_LeftVector
        );
    }

    glm::mat4 FreelyCamera::getViewMatrix() const
    {
        return glm::lookAt(
            m_Position,
            m_Position + m_FrontVector,
            m_UpVector
        );
    }

    void FreelyCamera::moveSide(float t)
    {
        m_Position += t*m_LeftVector;
        computeDirectionVectors();
    }

    void FreelyCamera::moveFront(float t)
    {
        m_Position += t*m_FrontVector;
        computeDirectionVectors();
    }

    void FreelyCamera::rotateSide(float degrees)
    {
        m_fPhi += glm::radians(degrees);
        computeDirectionVectors();
    }

    void FreelyCamera::rotateUp(float degrees)
    {
        m_fTheta += glm::radians(degrees);
        computeDirectionVectors();
    }
}