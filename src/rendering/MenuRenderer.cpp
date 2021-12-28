#include "MenuRenderer.hpp"

// CONSTRUCTORS
/* basic constructors */

MenuRenderer::MenuRenderer(glimac::FilePath applicationPath)
    :_applicationPath(applicationPath)
{
    /* Initialisation of the fonts */
    _PTMono = Text2D(40, _applicationPath, "PTMono.ttc");
}

// DESTRUCTORS

// MenuRenderer::~MenuRenderer()
// {
// }

// METHODS

void MenuRenderer::setWindowParameters(
    const unsigned width,
    const unsigned height,
    glm::mat4& projection
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
    std::vector<Menu> menu_list,
    short unsigned int menu_index
    )
{
    Menu current_menu = menu_list[menu_index];

    drawButtons(current_menu);
}

void MenuRenderer::drawButtons(Menu& current)
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

        _PTMono.draw(
            current.getButtonAt(i-1).label,
            glm::vec2(50.f, margin_bottom),
            text_color,
            _TEXT_PROJECTION_MATRIX
        );

        margin_bottom += 50.f;
    }
}