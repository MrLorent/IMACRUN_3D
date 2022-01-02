#include "Menu.hpp"

// OPERATORS
 
// CONSTRUCTORS
/* basic constructor */

Menu::Menu(const std::vector<Button> &buttons)
    :_buttons(buttons),
     _currentButton(0)
{
}

Menu::~Menu()
{
}

// SETTER

void Menu::setCurrentButton(const short unsigned int index)
{
    _currentButton = index;
}

// METHOD

void Menu::changeCurrentButton(const short int direction)
{
    if(_currentButton == 0 && direction == -1)
    {
        _currentButton = _buttons.size()-1;
    }else{
        _currentButton = (_currentButton + direction)%_buttons.size();
    }
}