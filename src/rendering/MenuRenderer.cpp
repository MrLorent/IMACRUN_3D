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
    std::vector<Menu> menu_list,
    short unsigned int menu_index,
    unsigned int window_width,
    unsigned int window_height
    )
{
    Menu current_menu = menu_list[menu_index];
    glm::mat4 projectionMatrix = glm::ortho(
        0.0f,
        static_cast<float>(window_width),
        0.0f,
        static_cast<float>(window_height)
    );

    /* Draw the buttons */
    glm::vec3 text_color(1.f);
    float margin_bottom = 50.f;
    for(unsigned int i = current_menu.getNumberOfButtons(); i > 0; --i)
    {
        if((i-1) == current_menu.getButtonIndex()){
            text_color = glm::vec3(1.f,1.f,0.f);
        }else{
            text_color = glm::vec3(1.f);
        }

        _PTMono.draw(
            current_menu.getButtonAt(i-1).label,
            glm::vec2(50.f, margin_bottom),
            text_color,
            projectionMatrix
        );

        margin_bottom += 50.f;
    }
}