#pragma once
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

#include "Menu.hpp"
#include "MenuRenderer.hpp"
#include "Game.hpp"
#include "GameRenderer.hpp"

//! The App class deals with the navigation throught the different menus, and the game.

/*!
 *  The App class contains a MenuRenderer object and
 *  deals with the navigation throught the different
 *  according to the Strategy design pattern. It also
 *  contains a Game object and a GameRenderer object
 *  to launch the game.
 */

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

    //! Constructor
    /*!
    *\fn App(GLFWwindow* window, const unsigned int width, const unsigned int height, const std::string path)
    *\param window : pointer to a GLFWwindow
    *\param width : width of the GLFWwindow
    *\param height : height of the GLFWwindow
    *\param path : local path to the application root directory
    */
    App(GLFWwindow *window, const unsigned int width, const unsigned int height, const std::string &path);

    // DESTRUCTORS
    ~App(){};

    //! Getter
    /*!
    *\fn inline Game& getGame()
    *\return a reference on the game.
    */      
    inline Game &getGame() { return _game; }

    // METHODS

    //! Method
    /*!
    *\fn void getBestScores()
    * Method that get the registered scores in a output file.
    */
    void getBestScores();

    //! Method
    /*!
    *\fn void SetBestScores()
    * Method that Set the registered scores in a output file.
    */
    void setBestScores();
    
    //! Method
    /*!
    *\fn void getSavedScore()
    * Method that read the score of the last game saved in a output file.
    */
    void getSavedScore();

    //! Method
    /*!
    *\fn void render()
    * Main method that display the application.
    */
    void render();

    /* Control managers */

    void key_callback(const int key, const int scancode, const int action, const int mods);
    void char_callback(const unsigned int codepoint);
    void mouse_button_callback(const int button, const int action, const int mods);
    void scroll_callback(const double xoffset, const double yoffset);
    void cursor_position_callback(const double xpos, const double ypos);
    void size_callback(GLFWwindow *window, int width, int height);
};