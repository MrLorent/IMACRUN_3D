#include "App.hpp"
#include "Text.hpp"

App::App(GLFWwindow* window, int window_width, int window_height, std::string name):_name(name)
{
    /* Initialization of the window size */
    size_callback(window, window_width, window_height);
    _width = window_width;
    _height = window_height;
    
    /* Initialization of the navigation */
    currentScreen = PRINCIPAL_MENU;
    game = Game(glimac::FilePath(_name));
    _text=Text("Arial.ttf", 48, glimac::FilePath(_name));
}

void App::render()
{
    switch (currentScreen)
    {
    case PRINCIPAL_MENU:
        //glClearColor(1.000f, 0.992f, 0.735f, 1.000f);
        _text.draw(_text.shader, "abcdefghijkl", float(_width/2.), float(_height/2.), 1.0f, glm::vec3(1.000f, 1.f, 1.f), _width, _height);
        break;
    case GAME:
        if(game._running)
        {
            glClearColor(0.f, 0.f, 0.f, 1.f);
            game.runGame(projectionMatrix);
        }
        else
        {
            currentScreen = PRINCIPAL_MENU;
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
            currentScreen = PRINCIPAL_MENU;
            break;
        case 71: // "1" NUM PAD
            currentScreen = GAME;
            if(!game._running)
            {
                game.initGame();
                game._running = true;
            }
            break;
        case 322: // "2" NUM PAD
            currentScreen = LOAD_MENU;
            break;
        case 323: // "3" NUM PAD
            currentScreen = SCORES;
            break;
        case 324: // "4" NUM PAD
            currentScreen = SCORE_INPUT;
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
    projectionMatrix = glm::perspectiveFov(
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