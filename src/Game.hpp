#pragma once
#define GAME_HPP

#include "Player.hpp"
#include "Camera.hpp"

class Game
{
private:
    glimac::FilePath _applicationPath;

    glm::mat4 _viewMatrix;

    Player _player;
    Model _floor;
    std::vector<char> _map;

    void load();

public:
    bool _finished;
    Camera _camera;
    
    Game(){}
    Game(glimac::FilePath applicationPath);

    void render(glm::mat4& projectionMatrix);
    void key_callback(int key, int scancode, int action, int mods);
    void mouse_button_callback(int button, int action, int mods);
    void scroll_callback(double xoffset, double yoffset);
    void cursor_position_callback(double xpos, double ypos);
};
