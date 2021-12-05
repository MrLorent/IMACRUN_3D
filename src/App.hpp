#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Game.hpp"

// MENU NAVIGATION
const short unsigned int PRINCIPAL_MENU = 0;
const short unsigned int GAME = 1;
const short unsigned int LOAD_MENU = 2;
const short unsigned int SCORES = 3;
const short unsigned int SCORE_INPUT = 4;

class App
{
    private:
        short unsigned int _currentScreen;

        int _windowWidth;
        int _windowHeight;
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

        glm::mat4 ProjMatrix, MVMatrix;

        Game game;
};