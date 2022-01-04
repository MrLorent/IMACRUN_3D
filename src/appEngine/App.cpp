#include "App.hpp"

// CONSTRUCTORS
/* basic constructors */

App::App(GLFWwindow* window, const unsigned int width, const unsigned int height, const std::string &path)
    :_applicationPath(glimac::FilePath(path)),
     _menuIndex(MAIN_MENU),
     _menuRenderer(MenuRenderer(_applicationPath)),
     _gameRenderer(GameRenderer(_applicationPath))
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

    buttons.clear();

    // GAME PAUSED
    buttons = {
        Button("Reprendre", GAME),
        Button("Recommencer", GAME),
        Button("Configurer la Camera", CAMERA_SETTINGS),
        Button("Sauvegarder et quitter", MAIN_MENU)
    };
    _menuList.push_back(Menu(buttons));

    buttons.clear();

    // CAMERA SETTINGS
    buttons = {
        Button("Enregistrer", GAME_PAUSED),
        Button("Retour", GAME_PAUSED)
    };
    _menuList.push_back(Menu(buttons));

    buttons.clear();

    // GAME OVER MENU
    buttons = {
        Button("Recommencer", GAME),
        Button("Menu Principal", MAIN_MENU)
    };
    _menuList.push_back(Menu(buttons));

    /* Initialization of the window size */
    size_callback(window, width, height);
}

// METHODS

void App::getSavedScore()
{
    std::ifstream file;
    std::string const fileName("./saves/save.txt");
    file.open(fileName, std::ios::out | std::ios::binary);

    if(file.is_open())
    {
        file >> _savedScore;

        file.close();
    }
    else
    {
        std::cerr << "ERROR FORM [APP | getSavedScore() ]: Impossible to open scores.txt." << std::endl;
    }
}

void App::getBestScores()
{
    std::ifstream file("./saves/scores.txt");
    if(file) {
        std::string pseudo;
        unsigned int score;

        for(unsigned short int i=0; i<3;++i)
        {
            file >> pseudo;
            file >> score;

            _scores.push_back(Score(i+1, pseudo, score));
        }

        file.close();
    }else
    {
        std::cerr << "ERREUR: Impossible d'ouvrir le scores.txt." << std::endl;
    }
}

void App::setBestScores()
{
    unsigned short int index = 0;
    bool registered = false;

    for(std::vector<Score>::iterator it = _scores.begin(); it != _scores.end(); ++it)
    {
        if(_game.getScore() > it->score && !registered)
        {
            _scores.insert(it, Score(index+1, _pseudoInput, _game.getScore()));
            registered = true;
        }
        index++;
    }
    _scores.pop_back();
    _pseudoInput = "";

    for(unsigned int i=0; i<_scores.size(); ++i) _scores[i].place = i+1;

    std::ofstream file;
    std::string const fileName("./saves/scores.txt");
    file.open(fileName, std::ios::out | std::ios::binary);

    if(file.is_open())
    {

        for(unsigned short int i=0; i<_scores.size();++i)
        {
            file << _scores[i].name << std::endl;
            file << _scores[i].score << std::endl;
        }

        file.close();
    }else
    {
        std::cerr << "ERREUR: Impossible d'ouvrir le scores.txt." << std::endl;
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
    case LOAD_MENU:
        _menuRenderer.drawLoadMenu(_menuList[_menuIndex], _savedScore);
        break;
    case SCORES:
        _menuRenderer.drawScores(_menuList[_menuIndex], _scores);
        break;
    case SCORE_INPUT:
        _menuRenderer.drawScoreInput(_menuList[_menuIndex], _pseudoInput);
        break;
    case GAME_PAUSED:
        _menuRenderer.drawGamePaused(_menuList[GAME_PAUSED]);
        break;
    case CAMERA_SETTINGS:
        _gameRenderer.render(_game);
        _menuRenderer.drawCameraSetting(_menuList[CAMERA_SETTINGS]);
        break;
    case GAME_OVER:
        _menuRenderer.drawGameOver(_menuList[_menuIndex]);
        break;
    case GAME:
        {
            const unsigned short int gameState = _game.getState();
            
            switch (gameState)
            {
                case Game::WAITING:
                    _game.setState(Game::RUNNING, Game::CLEAR_START);
                    break;
                
                case Game::RUNNING:
                    /* Running game */
                    _game.runGame();
                    _gameRenderer.render(_game);
                    break;
                
                case Game::PAUSED:
                    _menuIndex = GAME_PAUSED;
                    break;
                
                case Game::FINISHED:
                    if(_game.getScore() > _scores[_scores.size()-1].score)
                    {
                        _menuIndex = SCORE_INPUT;
                    }
                    else
                    {
                        _menuIndex = GAME_OVER;
                    }
                    break;
                default:
                    break;
            }
        }
        break;
    default:
        break;
    }
}

void App::key_callback(const int key, const int scancode, const int action, const int mods)
{
    switch (key)
        {
        case GLFW_KEY_ESCAPE: //ECHAP 
            if(action !=0 && _menuIndex == GAME_PAUSED) _game.setState(Game::PAUSED, 0);
            break;
        case GLFW_KEY_P: // 'P'
            if(action != 0 && _menuIndex == GAME) _game.setState(Game::PAUSED, 0);
            break;
        case GLFW_KEY_C: // 'C'
            if(action!=0 && _menuIndex == CAMERA_SETTINGS) _game._camera.switchMode(); 
            break;
        case GLFW_KEY_I: // 'I'
            if(action!=0 && _menuIndex == CAMERA_SETTINGS) _game._camera.rotateVerticaly(2.*float(1));
            break;
        case GLFW_KEY_K: // 'K'
            if(action!=0 && _menuIndex == CAMERA_SETTINGS) _game._camera.rotateVerticaly(-2.*float(1));
            break;
        case GLFW_KEY_J:
            if(action!=0 && _menuIndex == CAMERA_SETTINGS) _game._camera.rotateHorizontaly(2.*float(1));
            break;
        case GLFW_KEY_L:
            if(action!=0 && _menuIndex == CAMERA_SETTINGS) _game._camera.rotateHorizontaly(-2.*float(1));
            break;
        case GLFW_KEY_DOWN: // down arrow
            if(action != 0 && !(_menuIndex == LOAD_MENU && _savedScore == -1)) _menuList[_menuIndex].changeCurrentButton(1);
            break;
        case GLFW_KEY_UP: // up arrow
            if(action != 0 && !(_menuIndex == LOAD_MENU && _savedScore == -1)) _menuList[_menuIndex].changeCurrentButton(-1);
            break;
        case GLFW_KEY_BACKSPACE:
            if(action !=0 && _menuIndex == SCORE_INPUT) _pseudoInput.pop_back();
            break;
        case GLFW_KEY_ENTER: // Enter
            if(action !=0)
            {
                const unsigned short int PREVIOUS_MENU = _menuIndex;
                const unsigned short int BUTTON_CLICKED = _menuList[PREVIOUS_MENU].getButtonIndex();
                _menuIndex = _menuList[_menuIndex].getCurrentButtonLink();
                if(_menuIndex == LOAD_MENU && _savedScore == -1)
                {
                    _menuList[LOAD_MENU].setCurrentButton(1);
                }
                _menuList[PREVIOUS_MENU].setCurrentButton(0);

                switch (PREVIOUS_MENU)
                {
                    case GAME_PAUSED:
                        {
                            switch (BUTTON_CLICKED)
                            {
                            case 0: // REPRENDRE
                                _game.setState(Game::RUNNING, Game::UNPAUSE);
                                break;
                            
                            case 1: // RECOMMENCER
                                _game.setState(Game::RUNNING, Game::CLEAR_START);
                                break;

                            case 2: // PARAMETRER LA CAMERA
                                _game._camera.setState(Camera::UNLOCKED);
                                break;
                            
                            case 3: // SAUVEGARDER ET QUITTER
                                _game.setState(Game::WAITING, 0);
                                _savedScore = _game.getScore();
                                break;

                            default:
                                break;
                            }
                        }
                        break;
                    case CAMERA_SETTINGS:
                        if(BUTTON_CLICKED == 0) _game._camera.saveSettings();
                        _game._camera.setState(Camera::LOCKED);
                        break;
                    case GAME_OVER:
                        _game.setState(Game::WAITING, 0);
                        break;
                    case SCORE_INPUT:
                        if(BUTTON_CLICKED == 0 && _pseudoInput.size() == 3)
                        {
                            setBestScores();
                            _game.setState(Game::WAITING, 0);
                        }else if(BUTTON_CLICKED == 0){
                            _menuIndex = SCORE_INPUT;
                        }else{
                            _game.setState(Game::WAITING, 0);
                        }
                        
                        break;
                    case LOAD_MENU:
                        if(BUTTON_CLICKED == 0 && _savedScore != -1)
                        {
                            _game.setState(Game::RUNNING, Game::FROM_SAVE);
                        }
                        break;
                    default:
                        break;
                }
            }
            break; 
        default:
            break;
        }
}

void App::char_callback(const unsigned int codepoint)
{
    if(_menuIndex == SCORE_INPUT && _pseudoInput.size() < 3) {
        _pseudoInput.push_back(std::toupper(char(codepoint)));
    }
}

void App::mouse_button_callback(const int button,const int action,const int mods)
{
}

void App::scroll_callback(const double xoffset,const double yoffset)
{
    if(_menuIndex == CAMERA_SETTINGS) _game._camera.changeDistance(yoffset);
}

void App::cursor_position_callback(const double xpos,const double ypos)
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
        150.0f
    );

    _WINDOW_WIDTH = width;
    _WINDOW_HEIGHT = height;

    _menuRenderer.setWindowParameters(width, height, _PROJECTION_MATRIX);
    _gameRenderer.setWindowParameters(width, height, _PROJECTION_MATRIX);
}