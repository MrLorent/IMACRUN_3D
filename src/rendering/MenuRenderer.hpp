#pragma once
#define MENU_RENDERER_HPP

#include "Menu.hpp"
#include "Text2D.hpp"

class MenuRenderer
{
private:
    // ATTRIBUTS
    /* Window parameters */
    int _WINDOW_WIDTH;
    int _WINDOW_HEIGHT;
    glm::mat4 _PROJECTION_MATRIX;
    glm::mat4 _TEXT_PROJECTION_MATRIX;

    glimac::FilePath _applicationPath;
    Text2D _PTMono;
public:
    // CONSTRUCTORS
    /* basic constructors */

    MenuRenderer(){}
    MenuRenderer(glimac::FilePath applicationPath);

    // DESTRUCTORS

    //~MenuRenderer();

    // METHODS
    void setWindowParameters(
        const unsigned width,
        const unsigned height,
        glm::mat4& projection
    );

    void render(
        std::vector<Menu> menu_list,
        short unsigned int menu_index
    );
};
