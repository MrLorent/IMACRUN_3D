#pragma once
#define GAME_HPP

#include <GLFW/glfw3.h>

#include "Camera.hpp"
#include "Player.hpp"
#include "Map.hpp"

class Game
{
    // friend class GameRenderer;

    private:
        // ATTRIBUTS

        short unsigned int _state;
        const short unsigned int _defaultIndex;
        short unsigned int _playerIndex;
        glm::mat4 _skyBoxMMatrix;

        void checkPlayerPosition();
        void passTurn();

    public:
        // CONSTANTS
        enum GAME_STATE{
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
        short unsigned int _wallDistance;
        
        // CONSTRUCTORS
        /* basic constructors */

        Game();

        // DESTRUCTORS
        ~Game(){};

        // GETTERS
        inline short unsigned int getState() const { return _state; }
        inline float getCaseSubdivision() const { return _caseSubdivisions; }
        inline unsigned int getCaseSubdivisionIndex() const { return _caseSubdivisionsIndex; }
        inline unsigned int getScore() const { return _player.getScore(); }
        inline unsigned int getPlayerIndex() const { return _playerIndex; }
        inline glm::mat4& getSkyBoxMMatrix() { return _skyBoxMMatrix; }

        // SETTER

        void setState(const short unsigned int newState, const short unsigned int mode);

        //  METHODS

        void initGame();
        void initGameFromSave();
        void runGame();
        void saveGame();

        void key_callback(int key, int scancode, int action, int mods);
        void mouse_button_callback(int button, int action, int mods);
        void scroll_callback(double xoffset, double yoffset);
        void cursor_position_callback(double xpos, double ypos);
};
