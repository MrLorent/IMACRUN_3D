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

void MenuRenderer::render(
    std::vector<Screen> screen_list,
    short unsigned int screen_index,
    unsigned int window_width,
    unsigned int window_height
    )
{
    Screen current_screen = screen_list[screen_index];

    /* Draw the buttons */
    glm::vec3 text_color(1.f);
    float margin_bottom = 50.f;
    for(unsigned int i = current_screen.getNumberOfButtons(); i > 0; --i)
    {
        if((i-1) == current_screen.getButtonIndex()){
            text_color = glm::vec3(1.f,1.f,0.f);
        }else{
            text_color = glm::vec3(1.f);
        }

        _PTMono.draw(
            current_screen.getButtonAt(i-1).label,
            glm::vec2(50.f, margin_bottom),
            text_color,
            window_width,
            window_height
        );

        margin_bottom += 50.f;
    }
}