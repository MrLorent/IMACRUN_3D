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
    // CONSTANTS
    /* Navigation menu */
    static constexpr short unsigned int PRINCIPAL_MENU = 0;
    static constexpr short unsigned int GAME = 1;
    static constexpr short unsigned int LOAD_MENU = 2;
    static constexpr short unsigned int SCORES = 3;
    static constexpr short unsigned int SCORE_INPUT = 4;

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
