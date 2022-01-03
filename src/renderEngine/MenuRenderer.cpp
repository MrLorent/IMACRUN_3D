#include "MenuRenderer.hpp"

// OPERATORS
/* Move assignment operator */

MenuRenderer& MenuRenderer::operator=(MenuRenderer&& rhs) noexcept
{
    if(this != &rhs)
    {
        _WINDOW_WIDTH = rhs._WINDOW_WIDTH;
        _WINDOW_HEIGHT = rhs._WINDOW_HEIGHT;
        _PROJECTION_MATRIX = rhs._PROJECTION_MATRIX;
        _TEXT_PROJECTION_MATRIX = rhs._TEXT_PROJECTION_MATRIX;

        _applicationPath = rhs._applicationPath;
        _title = std::move(rhs._title);
        _text = std::move(rhs._text);
    }

    return *this;
}

// CONSTRUCTORS
/* basic constructors */

MenuRenderer::MenuRenderer(const glimac::FilePath applicationPath)
    :_applicationPath(applicationPath),
     _title(std::move(Text2D(40, _applicationPath, "PTMono.ttc"))),
     _text(std::move(Text2D(30, _applicationPath, "PTMono.ttc"))),
     _WINDOW_WIDTH(0),
     _WINDOW_HEIGHT(0)
{
}

/* move constructor */

MenuRenderer::MenuRenderer(MenuRenderer&& rhs) noexcept
    :_WINDOW_WIDTH(rhs._WINDOW_WIDTH),
     _WINDOW_HEIGHT(rhs._WINDOW_HEIGHT),
     _PROJECTION_MATRIX(rhs._PROJECTION_MATRIX),
     _TEXT_PROJECTION_MATRIX(rhs._TEXT_PROJECTION_MATRIX),
     _applicationPath(rhs._applicationPath),
     _title(std::move(rhs._title)),
     _text(std::move(rhs._text))
{
}

// DESTRUCTORS

MenuRenderer::~MenuRenderer()
{
}

// METHODS

void MenuRenderer::setWindowParameters(
    const unsigned width,
    const unsigned height,
    const glm::mat4& projection
)
{
    _WINDOW_WIDTH = width;
    _WINDOW_HEIGHT = height;
    _PROJECTION_MATRIX = projection;
    _TEXT_PROJECTION_MATRIX = glm::ortho(
        0.0f,
        static_cast<float>(width),
        0.0f,
        static_cast<float>(height)
    );
}

void MenuRenderer::render(
    const std::vector<Menu> &menu_list,
    const short unsigned int menu_index
    )
{
    Menu current_menu = menu_list[menu_index];

    drawButtons(current_menu);
}

void MenuRenderer::drawButtons(const Menu& current)
{
    /* Draw the buttons */
    glm::vec3 text_color(1.f);
    float margin_bottom = 50.f;
    for(unsigned int i = current.getNumberOfButtons(); i > 0; --i)
    {
        if((i-1) == current.getButtonIndex()){
            text_color = glm::vec3(1.f,1.f,0.f);
        }else{
            text_color = glm::vec3(1.f); 
        }

        _title.draw(
            current.getButtonAt(i-1).label,
            glm::vec2(50.f, margin_bottom),
            text_color,
            _TEXT_PROJECTION_MATRIX
        );

        margin_bottom += 50.f;
    }
}

void MenuRenderer::drawMainMenu(const Menu& menu)
{
    _title.draw(
        "IMACRUN",
        glm::vec2(_WINDOW_WIDTH/2.f -100.f, _WINDOW_HEIGHT-100.f),
        glm::vec3(1.f,1.f,0.f),
        _TEXT_PROJECTION_MATRIX
    );

    drawButtons(menu);
}

void MenuRenderer::drawGamePaused(const Menu& menu)
{
    _title.draw(
        "GAME PAUSED",
        glm::vec2(_WINDOW_WIDTH/2.f -200.f, _WINDOW_HEIGHT-100.f),
        glm::vec3(1.f,1.f,0.f),
        _TEXT_PROJECTION_MATRIX
    );

    drawButtons(menu);
}

void MenuRenderer::drawCameraSetting(const Menu& menu)
{
    drawButtons(menu);
}

void MenuRenderer::drawGameOver(const Menu& menu)
{
    _title.draw(
        "GAME OVER",
        glm::vec2(_WINDOW_WIDTH/2.f -110.f, _WINDOW_HEIGHT-100.f),
        glm::vec3(1.f,1.f,0.f),
        _TEXT_PROJECTION_MATRIX
    );

    drawButtons(menu);
}

void MenuRenderer::drawLoadMenu(const Menu& menu, const int savedScore)
{
    _title.draw(
        "SAUVEGARDE",
        glm::vec2(_WINDOW_WIDTH/2.f - 125.f, _WINDOW_HEIGHT-100.f),
        glm::vec3(1.f,1.f,0.f),
        _TEXT_PROJECTION_MATRIX
    );

    if(savedScore == -1)
    {
        _text.draw(
            "No save found.",
            glm::vec2(_WINDOW_WIDTH/2.f - 130.f, _WINDOW_HEIGHT - 250),
            glm::vec3(1.f, 0.f, 0.f),
            _TEXT_PROJECTION_MATRIX
        );
    }
    else
    {
        _text.draw(
            "SAUVEGARDE 1  |  SCORE : " + std::to_string(savedScore),
            glm::vec2(_WINDOW_WIDTH/2.f - 235.f , _WINDOW_HEIGHT - 250),
            glm::vec3(1.f),
            _TEXT_PROJECTION_MATRIX
        );
    }
    drawButtons(menu);
}

void MenuRenderer::drawScores(const Menu& menu, const std::vector<Score>& scores)
{
    _title.draw(
        "MEILLEURS SCORES",
        glm::vec2(_WINDOW_WIDTH/2.f -200.f, _WINDOW_HEIGHT-100.f),
        glm::vec3(1.f,1.f,0.f),
        _TEXT_PROJECTION_MATRIX
    );

    float marginTop = 200.f;
    float marginLeft = 225.f;

    for(size_t i=0; i<scores.size();++i)
    {
        _text.draw(
            std::to_string(scores[i].place) + "    |    " + scores[i].name + "    |    " + std::to_string(scores[i].score),
            glm::vec2(_WINDOW_WIDTH/2.f - marginLeft, _WINDOW_HEIGHT - marginTop),
            glm::vec3(1.f),
            _TEXT_PROJECTION_MATRIX
        );

        marginTop += 75.f;
    }

    drawButtons(menu);
}

void MenuRenderer::drawScoreInput(const Menu& menu, std::string pseudo)
{
    for(size_t i=pseudo.size(); i<3; ++i) pseudo += "_";
    _title.draw(
        "NOUVEAU MEILLEUR SCORE !",
        glm::vec2(_WINDOW_WIDTH/2.f -265.f, _WINDOW_HEIGHT-100.f),
        glm::vec3(1.f,1.f,0.f),
        _TEXT_PROJECTION_MATRIX
    );

    _text.draw(
        "Veuillez entrer votre pseudo :",
        glm::vec2(_WINDOW_WIDTH/2.f -260.f, _WINDOW_HEIGHT - 250),
        glm::vec3(1.f),
        _TEXT_PROJECTION_MATRIX
    );

    _text.draw(
        "(3 lettres seulement)",
        glm::vec2(_WINDOW_WIDTH/2.f -200.f, _WINDOW_HEIGHT - 285),
        glm::vec3(1.f),
        _TEXT_PROJECTION_MATRIX
    );

    _title.draw(
        pseudo,
        glm::vec2(_WINDOW_WIDTH/2.f -50.f, _WINDOW_HEIGHT-350.f),
        glm::vec3(1.f,1.f,1.f),
        _TEXT_PROJECTION_MATRIX
    );


    drawButtons(menu);
}