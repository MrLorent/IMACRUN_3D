#pragma once
#define MENU_RENDERER_HPP

#include "Menu.hpp"
#include "Text2D.hpp"

struct Score
{
    short unsigned int place;
    std::string name;
    unsigned int score;

    Score(const unsigned short int p, const std::string &n,const unsigned int s)
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

    void drawButtons(const Menu& current);
public:
    // OPERATORS
    /* Move assignment operator */

    MenuRenderer& operator=(MenuRenderer&& rhs) noexcept;

    /* Copy assignment operator */
    MenuRenderer& operator=(const MenuRenderer&) = delete; // We disable copying

    // CONSTRUCTORS
    /* basic constructors */

    MenuRenderer(){}
    MenuRenderer(const glimac::FilePath applicationPath);

    /* Copy constructor */

    MenuRenderer(const MenuRenderer&) = delete; // We disable copying

    /* move constructor */
    
    MenuRenderer(MenuRenderer&& rhs) noexcept;

    // DESTRUCTORS

    ~MenuRenderer();

    // METHODS
    void setWindowParameters(
        const unsigned width,
        const unsigned height,
        const glm::mat4& projection
    );

    void render(
        const std::vector<Menu> &menu_list,
        const short unsigned int menu_index
    );

    void drawMainMenu(const Menu& menu);
    void drawGameOver(const Menu& menu);
    void drawGamePaused(const Menu& menu);
    void drawCameraSetting(const Menu& menu);
    void drawLoadMenu(const Menu& menu, const int savedScore);
    void drawScores(const Menu& menu, const std::vector<Score>& scores);
    void drawScoreInput(const Menu& menu, std::string &pseudo);
};
