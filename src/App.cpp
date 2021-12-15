#include "App.hpp"
#include "Text.hpp"

App::App(GLFWwindow* window, int window_width, int window_height, std::string path)
    :_applicationPath(path)
{
    /* Initialization of the window size */
    size_callback(window, window_width, window_height);
    _width = window_width;
    _height = window_height;
    
    /* Initialization of the navigation */
    _currentScreen = PRINCIPAL_MENU;

    _text=Text(48, glimac::FilePath(_applicationPath), "PTMono.ttc");
    _gameRenderer = GameRenderer(glimac::FilePath(_applicationPath));
}

// GETTERS

Game& App::getGame()
{
    return _game;
}

// METHODS

/* Graphics */
void App::render()
{
    switch (_currentScreen)
    {
    case PRINCIPAL_MENU:
        //glClearColor(1.000f, 0.992f, 0.735f, 1.000f);
        _text.draw("Tanguy gros BG", glm::vec2(50.f, 50.f), glm::vec3(182.f/255.f, 102.f/255.f, 210.f/255.f), _width, _height);
        break;
    case GAME:
        if(_game._running)
        {
            _game.runGame();
            _gameRenderer.render(_projectionMatrix, _game);
        }
        else
        {
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
        case 320: // "0" NUM PAD
            _currentScreen = PRINCIPAL_MENU;
            break;
        case 71: // "1" NUM PAD
            _currentScreen = GAME;
            if(!_game._running)
            {
                _game.initGame();
                _gameRenderer.load3DModels();
                _game._running = true;
            }
            break;
        case 322: // "2" NUM PAD
            _currentScreen = LOAD_MENU;
            break;
        case 323: // "3" NUM PAD
            _currentScreen = SCORES;
            break;
        case 324: // "4" NUM PAD
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
    /* We store the size of the window just in case */
    _width = width;
    _height = height;
}