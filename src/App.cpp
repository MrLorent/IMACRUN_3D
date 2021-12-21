#include "App.hpp"

// CONSTRUCTORS
/* basic constructors */

App::App(GLFWwindow* window, const unsigned int width, const unsigned int height, const std::string path)
    :_applicationPath(glimac::FilePath(path))
{
    /* Initialization of the window size */
    size_callback(window, width, height);
    _width = width;
    _height = height;
    
    /* Initialization of the navigation */
    // MAIN MENU
    std::vector<Button> buttons = {
        Button("Nouvelle Partie", GAME),
        Button("Charger Partie", LOAD_MENU),
        Button("Scores", SCORES)
    };
    _menuList.push_back(Menu(buttons));
    
    buttons.empty();

    // GAME PAUSED MENU
    buttons = {
        Button("Reprendre", GAME),
        Button("Recommencer", GAME),
        Button("Menu Principal", PRINCIPAL_MENU)
    };
    _menuList.push_back(Menu(buttons));

    buttons.empty();

    // LOAD MENU
    buttons = {
        Button("Valider", GAME),
        Button("Retour", PRINCIPAL_MENU)
    };
    _menuList.push_back(Menu(buttons));

    buttons.empty();

    // SCORES
    buttons = {
        Button("Retour", PRINCIPAL_MENU)
    };
    _menuList.push_back(Menu(buttons));

    buttons.empty();

    // SCORE INPUT
    buttons = {
        Button("Valider", PRINCIPAL_MENU),
        Button("Retour", PRINCIPAL_MENU)
    };
    _menuList.push_back(Menu(buttons));

    _menuIndex = PRINCIPAL_MENU;
    _menuRenderer = MenuRenderer(_applicationPath);

    _gameRenderer = GameRenderer(_applicationPath);
}

// METHODS

/* Graphics */
void App::render()
{
    if(_menuIndex == GAME){
        if(!_game._running)
        {
            _game.initGame();
            _gameRenderer.load3DModels();
            _game._running = true;
        }else
        {
            /* Running game */
            _game.runGame();
            _gameRenderer.render(_projectionMatrix, _game);
        }
    }else{
        _menuRenderer.render(_menuList, _menuIndex, _width, _height);
    }
}

void App::key_callback(int key, int scancode, int action, int mods)
{
    switch (key)
        {
        case 264: // up arrow
            if(action != 0) _menuList[_menuIndex].changeCurrentButton(1);
            break;
        case 265: // down arrow
            if(action != 0) _menuList[_menuIndex].changeCurrentButton(-1);
            break;
        case 257: // Enter
            if(action !=0)
            {
                short unsigned int previous = _menuIndex;
                _menuIndex = _menuList[_menuIndex].getCurrentButtonLink();
                _menuList[previous].setCurrentButton(0);
            }
            break;
        case 49: // "1"
            _menuIndex = PRINCIPAL_MENU;
            break;
        case 50: // "2"
            _menuIndex = GAME;
            break;
        case 51: // "3"
            _menuIndex = LOAD_MENU;
            break;
        case 323: // "4"
            _menuIndex = SCORES;
            break;
        case 324: // "5"
            _menuIndex = SCORE_INPUT;
            break;
        default:
            std::cout << key << std::endl;
            break;
        }
}

void App::mouse_button_callback(int button, int action, int mods)
{
}

void App::scroll_callback(double xoffset, double yoffset)
{
}

void App::cursor_position_callback(double xpos, double ypos)
{
}

void App::size_callback(GLFWwindow* window, int width, int height)
{
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    _projectionMatrix = glm::perspectiveFov(
        glm::radians(70.0f),
        float(width),
        float(height),
        0.1f,
        100.0f
    );

    _width = width;
    _height = height;
}