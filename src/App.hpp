#pragma once
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>


#include "Menu.hpp"
#include "MenuRenderer.hpp"
#include "Game.hpp"
#include "GameRenderer.hpp"

class App
{
    private:
        // ATTRIBUTS
        /* Window parameters */
        int _width;
        int _height;
        glm::mat4 _projectionMatrix;

        /* External parameters */
        glimac::FilePath _applicationPath;

        /* Application parameters */
        std::vector<Menu> _menuList;
        short unsigned int _menuIndex;
        MenuRenderer _menuRenderer;

        /* Game entities */
        Game _game;
        GameRenderer _gameRenderer;

    public:
        // CONSTRUCTORS
        /* Basic constructors*/

        App(GLFWwindow* window, const unsigned int width, const unsigned int height, const std::string path);
        
        // GETTERS

        inline Game& getGame() { return _game; }

        // SETTERS

        // METHODS
        /* Graphics */

        void render();
        
        /* Control managers */

        void key_callback(int key, int scancode, int action, int mods);
        void mouse_button_callback(int button, int action, int mods);
        void scroll_callback(double xoffset, double yoffset);
        void cursor_position_callback(double xpos, double ypos);
        void size_callback(GLFWwindow* window, int width, int height);
};