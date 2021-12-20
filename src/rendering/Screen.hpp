#pragma once
#define SCREEN_HPP

#include "FilePath.hpp"
#include "Mesh.hpp"
#include "Text2D.hpp"

struct ScreenParams
{
    glimac::FilePath appPath;
    std::string backgroundPath;

    ScreenParams(
        glimac::FilePath appPath,
        std::string backgroundPath
    )
     :appPath(appPath),
      backgroundPath(backgroundPath)
    {}
};

class Screen
{
private:
    glimac::Program _shaders;
    Mesh _background;
public:
    // OPERATORS
    /* Move assignement */

    Screen& operator=(Screen&& rhs) noexcept;

    // CONSTRUCTORS
    /* basic constructors */

    Screen(){}
    Screen(ScreenParams params);

    /* move constructor */
    Screen(Screen&& rhs) noexcept;
    
    // DESTRUCTOR

    ~Screen();

    // METHODS

    void draw();
};
