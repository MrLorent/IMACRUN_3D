#pragma once
#define MENU_HPP

#include <iostream>
#include <string>
#include <vector>

struct Button
{
    std::string label;
    unsigned short int link; 

    Button(const std::string label,const unsigned short int link)
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
    
    Menu(const std::vector<Button> &buttons);
    
    // DESTRUCTOR

    ~Menu();

    // GETTER
    inline size_t getNumberOfButtons() const { return _buttons.size(); }
    inline short unsigned int getButtonIndex() const  { return _currentButton; }
    inline short unsigned int getCurrentButtonLink() const { return _buttons[_currentButton].link; }

    Button getButtonAt(const unsigned short int index) const { return _buttons[index]; }

    // SETTER
    void setCurrentButton(const unsigned short int index);

    // METHODS
    void changeCurrentButton(const short int direction);
};
