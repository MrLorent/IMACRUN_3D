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

        const short unsigned int _defaultIndex;
        short unsigned int _playerIndex;

        void checkPlayerPosition();
        void passTurn();

    public:
        // CONSTANTS
        static constexpr short int LEFT = -1;
        static constexpr short int NONE = 0;
        static constexpr short int RIGHT = 1;

        // ATTRIBUTS
        Camera _camera;
        Map _map;
        Player _player;

        bool _running;
        bool _paused;
        bool _finished;

        float _caseSubdivisions;
        unsigned int _caseSubdivisionsIndex;

        short int _turn;
        short unsigned int _wallDistance;
        
        Game();

        // GETTERS
        inline float getCaseSubdivision() const { return _caseSubdivisions; }
        inline unsigned int getCaseSubdivisionIndex() const { return _caseSubdivisionsIndex; }
        inline unsigned int getScore() const { return _player.getScore(); }
        inline unsigned int getPlayerIndex() const { return _playerIndex; }

        //  METHODS
        
        bool isRunning();

        void initGame();
        void initGameFromSave();
        void runGame();
        void saveGame();

        void key_callback(int key, int scancode, int action, int mods);
        void mouse_button_callback(int button, int action, int mods);
        void scroll_callback(double xoffset, double yoffset);
        void cursor_position_callback(double xpos, double ypos);
};
