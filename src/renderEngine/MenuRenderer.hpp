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
    *\fn Score(const unsigned short int p, const std::string &n,const unsigned int s);
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
        // PRIVATE ATTRIBUTS
        /* Window parameters */
        int _WINDOW_WIDTH;
        int _WINDOW_HEIGHT;
        glm::mat4 _PROJECTION_MATRIX;
        glm::mat4 _TEXT_PROJECTION_MATRIX;

        glimac::FilePath _applicationPath;
        Text2D _title;
        Text2D _text;

        //! Method
        /*!
        *\fn void drawButtons(const Menu& current)
        *\param current : menu containing the buttons to draw
        *   Method draw all the buttons of the menu passed in parameter
        */
        void drawButtons(const Menu& current);
        
    public:
        // OPERATORS
        /* Move assignment operator */

        //! Move assignment operator
        MenuRenderer& operator=(MenuRenderer&& rhs) noexcept;

        /* Copy assignment operator */

        //!Copy assignment operator
        MenuRenderer& operator=(const MenuRenderer&) = delete; // We disable copying

        // CONSTRUCTORS
        /* basic constructors */

        //! Constructor
        /*!
        *   Constructor by default
        */ 
        MenuRenderer(){}

        //! Constructor
        /*!
        *\fn MenuRenderer(const glimac::FilePath applicationPath);
        *\param applicationPath : Absolute path to the application
        */ 
        MenuRenderer(const glimac::FilePath applicationPath);

        /* Copy constructor */

        //! Constructor
        /*!
        *   Copy constructor
        */
        MenuRenderer(const MenuRenderer&) = delete; // We disable copying

        /* move constructor */

        //! Constructor
        /*!
        *\fn  MenuRenderer(MenuRenderer&& rhs) noexcept;
        *   move constructor
        */   
        MenuRenderer(MenuRenderer&& rhs) noexcept;

        // DESTRUCTORS

        //! Destructor
        /*!
        *   Destructor by default
        */ 
        ~MenuRenderer();

        // SETTER

        //! Setter
        /*!
        *\fn  setWindowParameters(const unsigned width, const unsigned height, const glm::mat4& projection);
        *\param width : width of the window
        *\param height : height of the window
        *\param projection : projection matrice 
        */ 
        void setWindowParameters(
            const unsigned width,
            const unsigned height,
            const glm::mat4& projection
        );


        // METHODS 

        //! method
        /*!
        *\fn void render(const std::vector<Menu> &menu_list, const short unsigned int menu_index)
        *\param menu_list : list of the menu
        *\param menu_index : index of the menu 
        */ 
        void render(
            const std::vector<Menu> &menu_list,
            const short unsigned int menu_index
        );

        //! method
        /*!
        *\fn drawMainMenu(const Menu& menu);
        *\ Permit to draw the main menu
        */     
        void drawMainMenu(const Menu& menu);

        //! method
        /*!
        *\fn drawGameOver(const Menu& menu);
        *\ Permit to draw the gameover menu 
        */  
        void drawGameOver(const Menu& menu);

        //! method
        /*!
        *\fn drawGamePaused(const Menu& menu);
        *\ Permit to draw the paused menu
        */  
        void drawGamePaused(const Menu& menu);

        //! method
        /*!
        *\fn drawCameraSetting(const Menu& menu);
        *\ Permit to draw the camera setting menu
        */  
        void drawCameraSetting(const Menu& menu);

        //! method
        /*!
        *\fn drawLoadMenu(const Menu& menu, const int savedScore);
        *\ Permit to draw the load menu
        */  
        void drawLoadMenu(const Menu& menu, const int savedScore);

        //! method
        /*!
        *\fn drawScores(const Menu& menu, const std::vector<Score>& scores);
        *\ Permit to draw the scores menu
        */  
        void drawScores(const Menu& menu, const std::vector<Score>& scores);

        //! method
        /*!
        *\fn drawScoreInput(Menu& menu, std::string pseudo);
        *\ Permit to draw the input menu
        */
        void drawScoreInput(const Menu& menu, std::string pseudo);
};
