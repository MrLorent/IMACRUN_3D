#pragma once
#define GAME_HPP

#include "Camera.hpp"
#include "Player.hpp"
#include "Map.hpp"

class Game
{
    friend class GameRenderer;

    private:
        // ATTRIBUTS

        Camera _camera;
        Map _map;
        Player _player;
        const short unsigned int _defaultIndex;
        short unsigned int _playerIndex;

        void checkPlayerPosition();
        void passTurn();

    public:
        // CONSTANTS
        static constexpr short int LEFT = -1;
        static constexpr short int NONE = 0;
        static constexpr short int RIGHT = 1;

        bool _running;
        bool _paused;
        bool _finished;

        float _caseSubdivisions;
        unsigned int _caseSubdivisionsIndex;

        short int _turn;
        short unsigned int _wallDistance;
        
        Game();

        //  METHODS
        bool isRunning();

        void initGame();
        void runGame();

        void key_callback(int key, int scancode, int action, int mods);
        void mouse_button_callback(int button, int action, int mods);
        void scroll_callback(double xoffset, double yoffset);
        void cursor_position_callback(double xpos, double ypos);
};
