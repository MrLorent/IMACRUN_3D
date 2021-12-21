#pragma once
#define MENU_RENDERER_HPP

#include "Screen.hpp"
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
        std::vector<Screen> screen_list,
        short unsigned int screen_index,
        unsigned int window_width,
        unsigned int window_height
    );
};
