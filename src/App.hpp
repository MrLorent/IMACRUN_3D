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
        /* Navigation menu */
        static constexpr short unsigned int PRINCIPAL_MENU = 0;
        static constexpr short unsigned int GAME = 1;
        static constexpr short unsigned int LOAD_MENU = 2;
        static constexpr short unsigned int SCORES = 3;
        static constexpr short unsigned int SCORE_INPUT = 4;

        /* Window parameters */
        int _width;
        int _height;
        glm::mat4 _projectionMatrix;

        /* External parameters */
        std::string _applicationPath;

        /* Game elements */
        short unsigned int _currentScreen;
        Game _game;
        GameRenderer _gameRenderer;

        Text _text;
    public:
        // CONSTRUCTORS
        /* Basic constructor*/

        App(GLFWwindow* window, int window_width, int window_height, std::string path);
        
        // GETTERS
        Game& getGame();

        // METHODS
        /* Control managers */

        void key_callback(int key, int scancode, int action, int mods);
        void mouse_button_callback(int button, int action, int mods);
        void scroll_callback(double xoffset, double yoffset);
        void cursor_position_callback(double xpos, double ypos);
        void size_callback(GLFWwindow* window, int width, int height);
        void destroy();
        
        /* Graphics */

        void render();
};