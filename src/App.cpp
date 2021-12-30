#include "App.hpp"

// CONSTRUCTORS
/* basic constructors */

App::App(GLFWwindow* window, const unsigned int width, const unsigned int height, const std::string path)
    :_applicationPath(glimac::FilePath(path))
{   
    /* Initialization of the best scores */
    getBestScores();
    getSavedScore();

    /* Initialization of the navigation */
    // MAIN MENU
    std::vector<Button> buttons = {
        Button("Nouvelle Partie", GAME),
        Button("Charger Partie", LOAD_MENU),
        Button("Scores", SCORES)
    };
    _menuList.push_back(Menu(buttons));
    
    buttons.clear();

    // GAME PAUSED MENU
    buttons = {
        Button("Reprendre", GAME),
        Button("Recommencer", GAME),
        Button("Sauvegarder et quitter", MAIN_MENU)
    };
    _menuList.push_back(Menu(buttons));

    buttons.clear();

    // GAME OVER MENU
    buttons = {
        Button("Recommencer", GAME),
        Button("Menu Principal", MAIN_MENU)
    };
    _menuList.push_back(Menu(buttons));

    buttons.clear();

    // LOAD MENU
    buttons = {
        Button("Charger", GAME),
        Button("Retour", MAIN_MENU)
    };
    _menuList.push_back(Menu(buttons));

    buttons.clear();

    // SCORES
    buttons = {
        Button("Retour", MAIN_MENU)
    };
    _menuList.push_back(Menu(buttons));

    buttons.clear();

    // SCORE INPUT
    buttons = {
        Button("Enregistrer", SCORES),
        Button("Retour", MAIN_MENU)
    };
    _menuList.push_back(Menu(buttons));

    _menuIndex = MAIN_MENU;
    _menuRenderer = MenuRenderer(_applicationPath);

    _gameRenderer = GameRenderer(_applicationPath);

    /* Initialization of the window size */
    size_callback(window, width, height);
}

// METHODS

void App::getSavedScore()
{
    std::ifstream file;
    std::string const fileName("./externals/save.txt");
    file.open(fileName, std::ios::out | std::ios::binary);

    if(file.is_open())
    {
        file >> _savedScore;

        file.close();
    }
    else
    {
        std::cout << "ERROR FORM [APP | getSavedScore() ]: Impossible to open scores.txt." << std::endl;
    }
}

void App::getBestScores()
{
    std::ifstream file("./externals/scores.txt");
    if(file) {
        std::string pseudo;
        unsigned int score;

        for(short unsigned int i=0; i<3;++i)
        {
            file >> pseudo;
            file >> score;

            _scores.push_back(Score(i+1, pseudo, score));
        }

        file.close();
    }else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le scores.txt." << std::endl;
    }
}

void App::setBestScores()
{
    short unsigned int index = 0;
    bool registered = false;

    while(!registered && index < _scores.size())
    {
        if(_game.getScore() > _scores[index].score)
        {
            _scores[index] = Score(index+1, _pseudoInput, _game.getScore());
            registered = true;
        }
        index++;
    }
    _pseudoInput = "";

    std::ofstream file;
    std::string const fileName("./externals/scores.txt");
    file.open(fileName, std::ios::out | std::ios::binary);

    if(file.is_open())
    {

        for(short unsigned int i=0; i<_scores.size();++i)
        {
            file << _scores[i].name << std::endl;
            file << _scores[i].score << std::endl;
        }

        file.close();
    }else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le scores.txt." << std::endl;
    }
}
/* Graphics */
void App::render()
{
    switch (_menuIndex)
    {
    case MAIN_MENU:
        _menuRenderer.drawMainMenu(_menuList[_menuIndex]);
        break;
    case GAME:
        if(_game._finished)
        {
            if(_game.getScore() > _scores[_scores.size()-1].score)
            {
                _menuIndex = SCORE_INPUT;
            }
            else
            {
                _menuIndex = GAME_OVER;
            }
        }
        else if(_game._paused)
        {
            _menuRenderer.drawGamePaused(_menuList[_menuIndex]);
        }
        else if(!_game._running)
        {
            /* Initiate game */
            _game.initGame();
            _game._running = true;
        }else
        {
            /* Running game */
            _game.runGame();
            _gameRenderer.render(_game);
        }
        break;
    case GAME_OVER:
        _menuRenderer.drawGameOver(_menuList[_menuIndex]);
        break;
    case LOAD_MENU:
        _menuRenderer.drawLoadMenu(_menuList[_menuIndex], _savedScore);
        break;
    case SCORES:
        _menuRenderer.drawScores(_menuList[_menuIndex], _scores);
        break;
    case SCORE_INPUT:
        _menuRenderer.drawScoreInput(_menuList[_menuIndex], _pseudoInput);
        break;
    default:
        _menuRenderer.render(_menuList, _menuIndex);
        break;
    }
}

void App::key_callback(int key, int scancode, int action, int mods)
{
    switch (key)
        {
        case GLFW_KEY_ESCAPE: //ECHAP 
            if(action !=0 && _menuIndex == GAME) _game._paused = false;
            break;
        case GLFW_KEY_DOWN: // down arrow
            if(action != 0) _menuList[_menuIndex].changeCurrentButton(1);
            break;
        case GLFW_KEY_UP: // up arrow
            if(action != 0) _menuList[_menuIndex].changeCurrentButton(-1);
            break;
        case GLFW_KEY_BACKSPACE:
            if(action !=0 && _menuIndex == SCORE_INPUT) _pseudoInput.pop_back();
            break;
        case GLFW_KEY_ENTER: // Enter
            if(action !=0)
            {
                const short unsigned int PREVIOUS_MENU = _menuIndex;
                const short unsigned int BUTTON_CLICKED = _menuList[PREVIOUS_MENU].getButtonIndex();
                _menuIndex = _menuList[_menuIndex].getCurrentButtonLink();
                _menuList[PREVIOUS_MENU].setCurrentButton(0);

                switch (PREVIOUS_MENU)
                {
                case GAME: 
                    _game._paused = false;
                    if(BUTTON_CLICKED != 0)
                    { // "RECOMMENCER" || "SAUVEGARDER" || "RETOUR AU MENU"
                       if(BUTTON_CLICKED == 2){
                            _game.saveGame();
                            _savedScore = _game.getScore();
                        }
                        _game._running = false;
                        _game._finished = false;
                    }
                    break;
                case GAME_OVER:
                    _game._paused = false;
                    _game._running = false;
                    _game._finished = false;
                    break;
                case SCORE_INPUT:
                    _game._paused = false;
                    _game._running = false;
                    _game._finished = false;
                    setBestScores();
                    break;
                case LOAD_MENU:
                    if(BUTTON_CLICKED == 0 && _savedScore != -1)
                    {
                        _game.initGameFromSave();
                        _game._running = true;
                    }
                    break;
                default:
                    break;
                }
            }
            break;
        
        default:
                std::cout << key << std::endl;
            break;
        }
}

void App::char_callback(unsigned int codepoint)
{
    if(_menuIndex == SCORE_INPUT && _pseudoInput.size() < 3) _pseudoInput.push_back(std::toupper(char(codepoint)));
    else std::cout << "code point: " << codepoint << std::endl;
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
    
    _PROJECTION_MATRIX = glm::perspectiveFov(
        glm::radians(70.0f),
        float(width),
        float(height),
        0.1f,
        100.0f
    );

    _WINDOW_WIDTH = width;
    _WINDOW_HEIGHT = height;

    _menuRenderer.setWindowParameters(width, height, _PROJECTION_MATRIX);
    _gameRenderer.setWindowParameters(width, height, _PROJECTION_MATRIX);
}