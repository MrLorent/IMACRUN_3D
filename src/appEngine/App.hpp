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
    enum APP_MENUS
    {
        MAIN_MENU = 0,
        LOAD_MENU = 1,
        SCORES = 2,
        SCORE_INPUT = 3,
        GAME_PAUSED = 4,
        CAMERA_SETTINGS = 5,
        GAME_OVER = 6,
        GAME = 7
    };
    // CONSTRUCTORS
    /* Basic constructors*/

    App(GLFWwindow *window, const unsigned int width, const unsigned int height, const std::string &path);

    // DESTRUCTORS
    ~App(){};

    // GETTERS

    inline Game &getGame() { return _game; }

    // SETTERS

    // METHODS
    void getBestScores();
    void setBestScores();
    void getSavedScore();

    /* Graphics */

    void render();

    /* Control managers */

    void key_callback(const int key, const int scancode, const int action, const int mods);
    void char_callback(const unsigned int codepoint);
    void mouse_button_callback(const int button, const int action, const int mods);
    void scroll_callback(const double xoffset, const double yoffset);
    void cursor_position_callback(const double xpos, const double ypos);
    void size_callback(GLFWwindow *window, int width, int height);
};