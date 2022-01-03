#pragma once
#define GAME_HPP

#include <GLFW/glfw3.h>

#include "Camera.hpp"
#include "Player.hpp"
#include "Map.hpp"

class Game
{
    private:
        // ATTRIBUTS

        unsigned short int _state;
        const unsigned short int _defaultIndex;
        unsigned short int _playerIndex;
        glm::mat4 _skyBoxMMatrix;

        void checkPlayerPosition();
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

        float _caseSubdivisions;
        unsigned int _caseSubdivisionsIndex;

        short int _turn;
        unsigned short int _wallDistance;
        
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

        void key_callback(int key, int scancode, int action, int mods);
        void mouse_button_callback(int button, int action, int mods);
        void scroll_callback(double xoffset, double yoffset);
        void cursor_position_callback(double xpos, double ypos);
};
