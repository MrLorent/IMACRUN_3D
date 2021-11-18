#include <iostream>
#include "glimac/TrackballCamera.hpp"

namespace glimac
{
    TrackballCamera::TrackballCamera()
        :m_fDistance(5), m_fAngleX(0), m_fAngleY(0)
    {
    }
    
    TrackballCamera::~TrackballCamera(){}

    void TrackballCamera::moveFront(float delta)
    {
        m_fDistance -= delta;
    }

    void TrackballCamera::rotateSide(float degrees)
    {
        m_fAngleY += glm::radians(degrees);
    }

    void TrackballCamera::rotateUp(float degrees)
    {
        m_fAngleX += glm::radians(degrees);
    }

    glm::mat4 TrackballCamera::getViewMatrix() const
    {
        glm::mat4 viewMatrix(1.f);

        viewMatrix = glm::translate(
            viewMatrix,
            glm::vec3(
                0.0f,
                0.0f,
                -m_fDistance)
        );

        viewMatrix = glm::rotate(
            viewMatrix,
            m_fAngleX,
            glm::vec3(1.0f,0.0f,0.0f)
        );

        viewMatrix = glm::rotate(
            viewMatrix,
            m_fAngleY,
            glm::vec3(0.0f,1.0f,0.0f)
        );

        return viewMatrix;
    }
}