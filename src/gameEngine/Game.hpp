#pragma once
#define GAME_HPP

#include <GLFW/glfw3.h>

#include "Camera.hpp"
#include "Player.hpp"
#include "Map.hpp"

class Game
{
    private:
        // PRIVATE ATTRIBUTS

        unsigned short int _state;

        /* Map speed parameters */
        float _caseSubdivisions;
        unsigned int _caseSubdivisionsIndex;

        /* Player placement parameters */
        const unsigned short int _defaultIndex;
        unsigned short int _playerIndex;

        /* Turn obstacle parameters */
        short int _turn;
        unsigned short int _wallDistance;
        
        /* Skybox parameters */
        glm::mat4 _skyBoxMMatrix;

        // PRIVATE METHODS

        //! Private method
        /*!
        *\fn void checkPlayerPosition()
        * Check the case under the player position and
        * determine if the game is finished or not.
        */
        void checkPlayerPosition();

        //! Private method
        /*!
        *\fn void passTurn()
        * Fonction called when the player pass a turn obstacle
        * to modify the map in order signifie to the gameRenderer
        * that the turn has been passed. 
        */
        void passTurn();

    public:
        // CONSTANTS
        enum GAME_STATES{
            WAITING = 0,
            RUNNING = 1,
            PAUSED = 2,
            FINISHED = 3
        };

        enum START_MODE{
            CLEAR_START = 0,
            FROM_SAVE = 1,
            UNPAUSE = 2
        };

        static constexpr short int LEFT = -1;
        static constexpr short int NONE = 0;
        static constexpr short int RIGHT = 1;

        // ATTRIBUTS

        Camera _camera;
        Map _map;
        Player _player;
        
        // CONSTRUCTORS
        /* basic constructors */

        //! Constructor
        /*!
        * Constructor by default
        */
        Game();

        // DESTRUCTORS

        //! Destructor
        /*!
        * Destructor by default.
        */
        ~Game(){};

        // GETTERS

        //! Getter
        /*!
        *\fn inline unsigned short int getState() const
        *\return return the state of the Game according to those defined in the enum GAME_STATE
        */
        inline unsigned short int getState() const { return _state; }

        //! Getter
        /*!
        *\fn inline float getCaseSubdivision() const
        *\return return number of steps needed for a map element to move one meter.
        */
        inline float getCaseSubdivision() const { return _caseSubdivisions; }

        //! Getter
        /*!
        *\fn inline unsigned int getCaseSubdivisionIndex() const
        *\return return the current case subdivision index 
        */
        inline unsigned int getCaseSubdivisionIndex() const { return _caseSubdivisionsIndex; }

        //! Getter
        /*!
        *\fn inline unsigned int getScore() const
        *\return return the score of the game
        */
        inline unsigned int getScore() const { return _player.getScore(); }

        //! Getter
        /*!
        *\fn inline unsigned int getPlayerIndex() const
        *\return return the current player index in term of map line
        */
        inline unsigned int getPlayerIndex() const { return _playerIndex; }

        //! Getter
        /*!
        *\fn inline glm::mat4& getSkyBoxMMatrix()
        *\return return the skyBox MMatrix
        */
        inline glm::mat4& getSkyBoxMMatrix() { return _skyBoxMMatrix; }

        // SETTER

        //! Setter
        /*!
        *\fn void setState(const unsigned short int newState, const unsigned short int mode)
        *\param newState : state from enum GAME_STATES to switch with. 
        *\param mode : mode from enum START_MODE to specify how to start a game
        * Setter that change the game state
        */
        void setState(const unsigned short int newState, const unsigned short int mode);

        //  METHODS

        //! Method
        /*!
        *\fn void initGame()
        * Method that reinitialise the game parameters to start a new game
        */
        void initGame();

        //! Method
        /*!
        *\fn void initGameFromSave()
        * Method that reinitialise the game parameters according to an external file
        */
        void initGameFromSave();

        //! Method
        /*!
        *\fn void runGame()
        * Method that define one turn of game
        */
        void runGame();
        
        //! Method
        /*!
        *\fn void saveGame()
        * Method that register the parameters of the current game in external file save.txt
        */
        void saveGame();

        void key_callback(const int key, const int scancode, const int action, const int mods);
        void mouse_button_callback(const int button, const int action, const int mods);
        void scroll_callback(const double xoffset, const double yoffset);
        void cursor_position_callback(const double xpos, const double ypos);
};
