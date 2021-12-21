#pragma once
#define MENU_RENDERER_HPP

#include "Menu.hpp"
#include "Text2D.hpp"

class MenuRenderer
{
private:
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
    void render(
        std::vector<Menu> menu_list,
        short unsigned int menu_index,
        unsigned int window_width,
        unsigned int window_height
    );
};
