#pragma once
#define MENU_RENDERER_HPP

#include "Menu.hpp"
#include "Text2D.hpp"

struct Score
{
    unsigned short int place;
    std::string name;
    unsigned int score;

        //! Constructor
        /*!
        *\fn Score(unsigned short int p, std::string n, unsigned int s);
        *\param p : the rank of the player 
        *\param n : the name of the player
        *\param s : the score of the player
        */ 
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

        //! Constructor
        /*!
        *\ Constructor by default
        */ 
    MenuRenderer(){}

        //! Constructor
        /*!
        *\fn MenuRenderer(glimac::FilePath applicationPath);
        *\param applicationPath : Absolute path to the application
        */ 
    MenuRenderer(const glimac::FilePath applicationPath);

    /* Copy constructor */

    MenuRenderer(const MenuRenderer&) = delete; // We disable copying

    /* move constructor */

        //! move Constructor
        /*!
        *\fn  MenuRenderer(MenuRenderer&& rhs) noexcept;
        *\ move constructor
        */   
    MenuRenderer(MenuRenderer&& rhs) noexcept;

    // DESTRUCTORS

        //! Destructor
        /*!
        *\ Destructor by default
        */ 
    ~MenuRenderer();

    // SETTER

        //! Setter
        /*!
        *\fn  setWindowParameters(const unsigned width, const unsigned height, glm::mat4& projection);
        *\param width : width of the window
        *\param height : height of the window
        \param projection : projection matrice 
        */ 
    void setWindowParameters(
        const unsigned width,
        const unsigned height,
        const glm::mat4& projection
    );


    // METHODS 

        //! method
        /*!
        *\fn render(std::vector<Menu> menu_list, unsigned short int menu_index );
        *\param menu_list : list of the menu
        *\param menu_index : index of the menu 
        */ 
    void render(
        const std::vector<Menu> &menu_list,
        const short unsigned int menu_index
    );

        //! method
        /*!
        *\fn drawMainMenu(Menu& menu);
        *\ Permit to draw the main menu
        */     

        //! method
        /*!
        *\fn drawGameOver(Menu& menu);
        *\ Permit to draw the gameover menu 
        */  

        //! method
        /*!
        *\fn drawGamePaused(Menu& menu);
        *\ Permit to draw the paused menu
        */  

        //! method
        /*!
        *\fn drawCameraSetting(Menu& menu);
        *\ Permit to draw the camera setting menu
        */  

        //! method
        /*!
        *\fn drawLoadMenu(Menu& menu, const int savedScore);
        *\ Permit to draw the load menu
        */  

        //! method
        /*!
        *\fn drawScores(Menu& menu, std::vector<Score>& scores);
        *\ Permit to draw the scores menu
        */  

        //! method
        /*!
        *\fn drawScoreInput(Menu& menu, std::string pseudo);
        *\ Permit to draw the input menu
        */
    void drawMainMenu(const Menu& menu);
    void drawGameOver(const Menu& menu);
    void drawGamePaused(const Menu& menu);
    void drawCameraSetting(const Menu& menu);
    void drawLoadMenu(const Menu& menu, const int savedScore);
    void drawScores(const Menu& menu, const std::vector<Score>& scores);
    void drawScoreInput(const Menu& menu, std::string pseudo);
};
