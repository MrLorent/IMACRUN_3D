#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Model.hpp"
#include "TrackballCamera.hpp"

class App
{
    private:
        int _width;
        int _height;
    public:
        // CONSTRUCTORS
        /* Basic constructor*/
        App(GLFWwindow* window, int window_width, int window_height, std::string name);
        
        void render();
        void key_callback(int key, int scancode, int action, int mods);
        void mouse_button_callback(int button, int action, int mods);
        void scroll_callback(double xoffset, double yoffset);
        void cursor_position_callback(double xpos, double ypos);
        void size_callback(GLFWwindow* window, int width, int height);
        void destroy();

        //Creation de la camera
        glimac::TrackballCamera cam = glimac::TrackballCamera();

        glm::mat4 ProjMatrix, MVMatrix;

        Model chevalier;
};