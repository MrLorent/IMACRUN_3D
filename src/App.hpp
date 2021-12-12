#pragma once
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>


#include "Game.hpp"
#include "GameRenderer.hpp"
#include "Text.hpp"

class App
{
    private:
        // CONSTANTS
        /* Navigation Menu */
        static constexpr short unsigned int PRINCIPAL_MENU = 0;
        static constexpr short unsigned int GAME = 1;
        static constexpr short unsigned int LOAD_MENU = 2;
        static constexpr short unsigned int SCORES = 3;
        static constexpr short unsigned int SCORE_INPUT = 4;
        
        int _width;
        int _height;
        std::string _name;
        Text _text;
    public:

        // PUBLIC ATTRIBUTS

        short unsigned int currentScreen;

        glm::mat4 projectionMatrix;
        Game game;


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
};