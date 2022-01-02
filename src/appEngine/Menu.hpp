#pragma once
#define MENU_HPP

#include <iostream>
#include <string>
#include <vector>

//! The Button structure contain a label and a link to one of the menu in the application

/*!
 *  The Label attribut is a string corresponding to the text display
 *  on the screen. The link attribut is a unsigned short int corresponding
 *  to a menu define in the enum APP_MENUS, in the App class.
 */

struct Button
{
    std::string label;
    short unsigned int link;

    Button(std::string label, short unsigned int link)
        :label(label), link(link)
    {}
};

//! The Menu class contains a list of buttons, and deal with the navigation throught them

/*!
 *  The buttons of the menu are contain in the _buttons attributs,
 *  which is a std::vector. The button currently selected is given
 *  by the _currentButton attribut that correspond to the index
 *  reach in the vector of buttons.
 */

class Menu
{
private:
    std::vector<Button> _buttons;
    short unsigned int _currentButton;
public:
    // OPERATORS

    // CONSTRUCTORS
    /* basic constructors */
    
    Menu(std::vector<Button> buttons);
    
    // DESTRUCTOR

    ~Menu();

    // GETTER
    inline size_t getNumberOfButtons() { return _buttons.size(); }
    inline short unsigned int getButtonIndex() { return _currentButton; }
    inline short unsigned int getCurrentButtonLink() { return _buttons[_currentButton].link; }

    Button getButtonAt(short unsigned int index) { return _buttons[index]; }

    // SETTER
    void setCurrentButton(const short unsigned int index);

    // METHODS
    void changeCurrentButton(short int direction);
};
