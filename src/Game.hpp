#pragma once
#define GAME_HPP

#include "Camera.hpp"
#include "Player.hpp"
#include "Map.hpp"

class Game
{
    friend class GameRenderer;

    private:
        Map _map;
        Player _player;
        short unsigned int _playerIndex;

        void checkPlayerPosition();

    public:
        bool _running;
        bool _paused;

        float _caseSubdivisions;
        unsigned int _caseSubdivisionsIndex;

        short int _turn;
        short unsigned int _distanceFromWall;
        
        Camera _camera;
        
        Game();

        //  METHODS

        void initGame();
        void runGame();

        void key_callback(int key, int scancode, int action, int mods);
        void mouse_button_callback(int button, int action, int mods);
        void scroll_callback(double xoffset, double yoffset);
        void cursor_position_callback(double xpos, double ypos);
};
