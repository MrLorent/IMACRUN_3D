#include "Screen.hpp"

// OPERATORS

// CONSTRUCTORS
/* basic constructor */

Screen::Screen(std::vector<Button> buttons)
    :_buttons(buttons),
     _currentButton(0)
{
}

Screen::~Screen()
{
}

// SETTER

void Screen::setCurrentButton(const short unsigned int index)
{
    _currentButton = index;
}

// METHOD

void Screen::changeCurrentButton(short int direction)
{
    if(_currentButton == 0 && direction == -1)
    {
        _currentButton = _buttons.size()-1;
    }else{
        _currentButton = (_currentButton + direction)%_buttons.size();
    }
}