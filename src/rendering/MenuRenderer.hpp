#pragma once
#define MENU_RENDERER_HPP

#include "Menu.hpp"
#include "Text2D.hpp"

struct Score
{
    short unsigned int place;
    std::string name;
    unsigned int score;

    Score(short unsigned int p, std::string n, unsigned int s)
        :place(p), name(n), score(s)
    {}
};

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
    Text2D _title;
    Text2D _text;

    void drawButtons(Menu& current);
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

    void drawMainMenu(Menu& menu);
    void drawGameOver(Menu& menu);
    void drawGamePaused(Menu& menu);
    void drawScores(Menu& menu, std::vector<Score>& scores);
};
