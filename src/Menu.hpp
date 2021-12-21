#pragma once
#define MENU_HPP

#include <iostream>
#include <string>
#include <vector>

struct Button
{
    std::string label;
    short unsigned int link;

    Button(std::string label, short unsigned int link)
        :label(label), link(link)
    {}
};


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
