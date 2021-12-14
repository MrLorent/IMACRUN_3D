#include "App.hpp"
#include "Text.hpp"

// CONSTRUCTORS
/* basic constructors */

App::App(GLFWwindow* window, const unsigned int width, const unsigned int height, const std::string path)
    :_applicationPath(path)
{
    /* Initialization of the window size */
    size_callback(window, width, height);
    _width = width;
    _height = height;
    
    /* Initialization of the navigation */
    _currentScreen = PRINCIPAL_MENU;

    _text = Text(48, glimac::FilePath(_applicationPath));
    _gameRenderer = GameRenderer(glimac::FilePath(_applicationPath));
}

// METHODS

/* Graphics */
void App::render()
{
    switch (_currentScreen)
    {
    case PRINCIPAL_MENU:
        _text.draw("Tanguy gros BG", glm::vec2(50.f, 50.f), glm::vec3(182.f/255.f, 102.f/255.f, 210.f/255.f), _width, _height);
        break;
    case GAME:
        if(_game._running)
        {
            /* Running game */
            _game.runGame();
            _gameRenderer.render(_projectionMatrix, _game);
        }
        else
        {
            /* If the game just finises, we go back to menu */
            _currentScreen = PRINCIPAL_MENU;
        }
        break;
    case LOAD_MENU:
        glClearColor(1.f, 0.f, 0.f, 1.f);
        break;
    case SCORES:
        glClearColor(0.f, 1.f, 0.0f, 1.f);
        break;
    case SCORE_INPUT:
        glClearColor(0.f, 0.f, 1.f, 1.f);
        break;
    default:
        break;
    }
}

void App::key_callback(int key, int scancode, int action, int mods)
{
    switch (key)
        {
        case 49: // "1"
            _currentScreen = PRINCIPAL_MENU;
            break;
        case 50: // "2"
            _currentScreen = GAME;
            if(!_game._running)
            {
                _game.initGame();
                _gameRenderer.load3DModels();
                _game._running = true;
            }
            break;
        case 51: // "3"
            _currentScreen = LOAD_MENU;
            break;
        case 323: // "4"
            _currentScreen = SCORES;
            break;
        case 324: // "5"
            _currentScreen = SCORE_INPUT;
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