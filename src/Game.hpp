#pragma once
#define GAME_HPP

#include "Camera.hpp"
#include "GameRenderer.hpp"

struct Player
{
    glm::vec3 position;

    Player():position(glm::vec3(0.f)){}
};

class Game
{
private:
    Player _player;
    std::vector<char> _map;
    GameRenderer _renderer;

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
