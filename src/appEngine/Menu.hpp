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
    unsigned short int link;
     //! Constructor
        /*!
         *\fn Button(std::string label, unsigned short int link)
         *\param label : name of the button
         *\param link : correspond to a menu define in the enum APP_MENUS in the App class
         */
    Button(const std::string label,const unsigned short int link)
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
    unsigned short int _currentButton;
public:
    // OPERATORS
    //! Constructor
    /*!
    *\fn Menu(std::vector<Button> buttons)
    *\param buttons : vector of all button
    */
    
    Menu(const std::vector<Button> &buttons);
    
    //! Destructor
        /*! Destructor
         *\destructor by default
         */
    ~Menu();

    //! Getter
    /*! Getter
    *\fn getNumberOfButtons()
    *\return the number of button
    */
    inline size_t getNumberOfButtons() const { return _buttons.size(); }
    inline short unsigned int getButtonIndex() const  { return _currentButton; }
    inline short unsigned int getCurrentButtonLink() const { return _buttons[_currentButton].link; }

        /*! Getter
        *\fn getButtonIndex()
        *\return the button's index
        */
    Button getButtonAt(const unsigned short int index) const { return _buttons[index]; }

        /*! Getter
        *\fn getButtonIndex()
        *\return the current Button's link
        */
    void setCurrentButton(const unsigned short int index);

        /*! Getter
        *\fn Button getButtonAt(unsigned short int index)
        *\param index : index to have the right button
        */


    //! Setter
        /*! Setter
        *\fn setCurrentButton(const unsigned short int index)
        *\param index : set the current button at the index
        */

    //! METHODS
        /*! Method
        *\fn changeCurrentButton(short int direction)
        *\param direction : -1 if it goes up, else it's going down
        */
    void changeCurrentButton(const short int direction);
};
