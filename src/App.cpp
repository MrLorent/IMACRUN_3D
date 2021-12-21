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
        Button("Nouvelle Partie", MenuRenderer::GAME),
        Button("Charger Partie", MenuRenderer::LOAD_MENU),
        Button("Scores", MenuRenderer::SCORES)
    };
    _screens.push_back(Screen(buttons));
    
    buttons.empty();

    // GAME PAUSED MENU
    buttons = {
        Button("Reprendre", MenuRenderer::GAME),
        Button("Recommencer", MenuRenderer::GAME),
        Button("Menu Principal", MenuRenderer::PRINCIPAL_MENU)
    };
    _screens.push_back(Screen(buttons));

    buttons.empty();

    // LOAD MENU
    buttons = {
        Button("Valider", MenuRenderer::GAME),
        Button("Retour", MenuRenderer::PRINCIPAL_MENU)
    };
    _screens.push_back(Screen(buttons));

    buttons.empty();

    // SCORES
    buttons = {
        Button("Retour", MenuRenderer::PRINCIPAL_MENU)
    };
    _screens.push_back(Screen(buttons));

    buttons.empty();

    // SCORE INPUT
    buttons = {
        Button("Valider", MenuRenderer::PRINCIPAL_MENU),
        Button("Retour", MenuRenderer::PRINCIPAL_MENU)
    };
    _screens.push_back(Screen(buttons));

    _currentScreen = MenuRenderer::PRINCIPAL_MENU;
    _menuRenderer = MenuRenderer(_applicationPath);

    _gameRenderer = GameRenderer(_applicationPath);
}

// METHODS

/* Graphics */
void App::render()
{
    if(_currentScreen == MenuRenderer::GAME){
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
        _menuRenderer.render(_screens, _currentScreen, _width, _height);
    }
}

void App::key_callback(int key, int scancode, int action, int mods)
{
    switch (key)
        {
        case 264: // up arrow
            if(action != 0) _screens[_currentScreen].changeCurrentButton(1);
            break;
        case 265: // down arrow
            if(action != 0) _screens[_currentScreen].changeCurrentButton(-1);
            break;
        case 257: // Enter
            if(action !=0)
            {
                short unsigned int previous = _currentScreen;
                _currentScreen = _screens[_currentScreen].getCurrentButtonLink();
                _screens[previous].setCurrentButton(0);
            }
            break;
        case 49: // "1"
            _currentScreen = MenuRenderer::PRINCIPAL_MENU;
            break;
        case 50: // "2"
            _currentScreen = MenuRenderer::GAME;
            break;
        case 51: // "3"
            _currentScreen = MenuRenderer::LOAD_MENU;
            break;
        case 323: // "4"
            _currentScreen = MenuRenderer::SCORES;
            break;
        case 324: // "5"
            _currentScreen = MenuRenderer::SCORE_INPUT;
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