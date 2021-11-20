#pragma once
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <iostream>
#include <vector>

#include <Program.hpp>
#include <FilePath.hpp>
#include <common.hpp>
#include <Image.hpp>
#include <Sphere.hpp>
#include <getTime.hpp>
#include <TrackballCamera.hpp>

struct EarthProgram
{
    glimac::Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uEarthTexture;
    GLint uCloudTexture;

    EarthProgram(){}
    EarthProgram(const glimac::FilePath& applicationPath):
        m_Program(loadProgram(
            applicationPath.dirPath() + "src/shaders/3D.vs.glsl",
            applicationPath.dirPath() + "src/shaders/multiTex3D.fs.glsl"
        ))
    {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uEarthTexture = glGetUniformLocation(m_Program.getGLId(), "uEarthTexture");
        uCloudTexture = glGetUniformLocation(m_Program.getGLId(), "uCloudTexture");
    }
};

struct MoonProgram
    {
        glimac::Program m_Program;

        GLint uMVPMatrix;
        GLint uMVMatrix;
        GLint uNormalMatrix;
        GLint uTexture;

        MoonProgram(){}
        MoonProgram(const glimac::FilePath& applicationPath):
            m_Program(loadProgram(
                applicationPath.dirPath() + "src/shaders/3D.vs.glsl",
                applicationPath.dirPath() + "src/shaders/tex3D.fs.glsl"
            ))
        {
            uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
            uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
            uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
            uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
        }
    };

class App{
public:
    App(int window_width, int window_height, std::string name);
    void render();
    void key_callback(int key, int scancode, int action, int mods);
    void mouse_button_callback(int button, int action, int mods);
    void scroll_callback(double xoffset, double yoffset);
    void cursor_position_callback(double xpos, double ypos);
    void size_callback(int width, int height);
    void destroy();

private:
    int _width{};
    int _height{};

    GLuint earthTex, cloudsTex, moonTex;
    std::unique_ptr<glimac::Image> earthPic, cloudsPic, moonPic;

    EarthProgram earthProgram;
    MoonProgram moonProgram;

    glm::mat4 projMatrix;
    glm::mat4 mvMatrix;

    GLuint vao;
    GLuint vbo;

    glimac::Sphere sphere = glimac::Sphere(1,1,1);

    std::vector<glm::vec3> randomAxis;
    std::vector<float> startPos;

    glimac::TrackballCamera trackballCamera; 
};