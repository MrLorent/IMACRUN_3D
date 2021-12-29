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
        int _WINDOW_WIDTH;
        int _WINDOW_HEIGHT;
        glm::mat4 _PROJECTION_MATRIX;

        /* External parameters */
        glimac::FilePath _applicationPath;

        /* Application parameters */
        std::vector<Score> _scores;
        std::vector<Menu> _menuList;
        short unsigned int _menuIndex;
        MenuRenderer _menuRenderer;
        std::string _pseudoInput;
        int _savedScore;

        /* Game entities */
        Game _game;
        GameRenderer _gameRenderer;

    public:
        // CONSTANTS
        /* Navigation menu */
        static constexpr short unsigned int MAIN_MENU = 0;
        static constexpr short unsigned int GAME = 1;
        static constexpr short unsigned int GAME_OVER = 2;
        static constexpr short unsigned int LOAD_MENU = 3;
        static constexpr short unsigned int SCORES = 4;
        static constexpr short unsigned int SCORE_INPUT = 5;
        // CONSTRUCTORS
        /* Basic constructors*/

        App(GLFWwindow* window, const unsigned int width, const unsigned int height, const std::string path);
        
        // GETTERS

        inline Game& getGame() { return _game; }

        // SETTERS

        // METHODS
        void getBestScores();
        void setBestScores();
        void getSavedScore();

        /* Graphics */

        void render();
        
        /* Control managers */

        void key_callback(int key, int scancode, int action, int mods);
        void char_callback(unsigned int codepoint);
        void mouse_button_callback(int button, int action, int mods);
        void scroll_callback(double xoffset, double yoffset);
        void cursor_position_callback(double xpos, double ypos);
        void size_callback(GLFWwindow* window, int width, int height);
};