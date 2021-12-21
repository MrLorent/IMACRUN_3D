#pragma once
#define SCREEN_HPP

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


class Screen
{
private:
    std::vector<Button> _buttons;
    short unsigned int _currentButton;
public:
    // OPERATORS
    const Button& operator[](const size_t& i) const;

    // CONSTRUCTORS
    /* basic constructors */
    
    Screen(std::vector<Button> buttons);
    
    // DESTRUCTOR

    ~Screen();

    // GETTER
    inline size_t getNbButtons() { return _buttons.size(); }
    inline short unsigned int getCurrentButtonIndex() { return _currentButton; }
    inline short unsigned int getCurrentButtonLink() { return _buttons[_currentButton].link; }

    // SETTER
    void setCurrentButton(const short unsigned int index);

    // METHODS
    void changeCurrentButton(short int direction);
};
