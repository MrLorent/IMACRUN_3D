#include "App.hpp"

App::App(GLFWwindow* window, int window_width, int window_height, std::string name)
{
    /* Initialization of the window size */
    size_callback(window, window_width, window_height);
    _windowWidth = window_width;
    _windowHeight = window_height;
    
    /* Initialization of the navigation */
    _currentScreen = PRINCIPAL_MENU;

    game = Game(glimac::FilePath(name), ProjMatrix);
}

void App::render()
{
    switch (_currentScreen)
    {
    case PRINCIPAL_MENU:
        glClearColor(1.000f, 0.992f, 0.735f, 1.000f);
        break;
    case GAME:
        glClearColor(0.f, 0.f, 0.f, 1.f);
        game.render();
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
        case 262: //Fleche droite
            if(action!=0){
                game._camera.rotateSide(-2.*float(1));
            }
            break;

        case 263: //Fleche gauche
            if(action!=0){
                game._camera.rotateSide(2.*float(1));
            }
            break;

        case 264: //Fleche bas
            if(action!=0){
                game._camera.rotateUp(-2.*float(1));
            }
            break;
        
        case 265: //Fleche haut
            if(action!=0){
                game._camera.rotateUp(2.*float(1));
            }
            break;
        case 320: // "0" NUM PAD
            _currentScreen = PRINCIPAL_MENU;
            break;
        case 321: // "1" NUM PAD
            _currentScreen = GAME;
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
    game._camera.moveFront(yoffset);
}

void App::cursor_position_callback(double xpos, double ypos)
{
}

void App::size_callback(GLFWwindow* window, int width, int height)
{
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    ProjMatrix = glm::perspectiveFov(
        glm::radians(70.0f),
        float(width),
        float(height),
        0.1f,
        100.0f
    );
    /* We store the size of the window just in case */
    _windowWidth = width;
    _windowHeight = height;
}