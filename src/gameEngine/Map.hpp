#pragma once
#define MAP_HPP

#include <vector>
#include <deque>
#include <random>
#include <iostream>
#include <fstream>
#include <time.h>
#include "glm/glm.hpp"

class Map
{
private:
    // PRIVATE ATTRIBUTS

    unsigned short int _mapWidth;
    std::deque<char> _map;
    std::vector<std::vector<char>> _mapElements;
    
    /* Mersenne twister random parameters */
    unsigned _seed;
    std::mt19937_64 _random;
    std::uniform_int_distribution<int> _distribution;

    // PRIVATE METHODS

    //! Private method
    /*!
    *\fn void loadMapElements()
    * Method that read all the map elements in external file ./assets/map/map.txt
    * and register then in the _mapElement attribut
    */
    void loadMapElements();

public:
    // CONSTANTS
    static constexpr char WALL = 'w';
    static constexpr char LIGHT_MARKER = 'x';
    static constexpr char LIGHT = 'l';
    static constexpr char FLOOR = 'f';
    static constexpr char BAREL = 'b';
    static constexpr char PASSED_TURN = 'p';
    static constexpr char COLLECTIBLE = 'c';
    static constexpr char ARCH = 'a';
    static constexpr char PLANK = 'o';

    // PUBLIC ATTRIBUTS
    std::vector<glm::vec3> firstLights;

    // OPERATORS

    //! Operator
    /*!
    * Getter : return the value at the index given
    */
    const char& operator[](const size_t& i) const;
    
    //! Operator
    /*!
    * Setter : return the reference of the value at the index given
    */
    char& operator[](const size_t& i);

    // CONSTRUCTEURS

    //! Constructor
    /*!
    * Constructor by default
    */
    Map();

    // DESTRUCTEURS

    //! Destructor
    /*!
    * Destructor by default.
    */
    ~Map(){};

    // GETTERS

    //! Getter
    /*!
    *\fn size_t getSize() const
    *\return the number of elements contain in the std::vector<char> _map attribut 
    */
    size_t getSize() const;

    //! Getter
    /*!
    *\fn unsigned short int getMapWidth() const
    *\return the number of cases in the map width.
    */
    unsigned short int getMapWidth() const;

    // METHODS

    //! Method
    /*!
    *\fn void initGame()
    * Method that reinitialise the map parameters to create a new one
    */
    void initMap();

    //! Method
    /*!
    *\fn void add(const char c)
    * Method that add a new element to the _map attribut
    */
    void add(const char c);

    //! Method
    /*!
    *\fn void reloadMap()
    * Method that refill the _map attribut by randomly picking a map element into the mapElement attribut.
    */
    void reloadMap();

    //! Method
    /*!
    *\fn void deleteFirstLigne()
    * Method that delete the first line of the map.
    */
    void deleteFirstLigne();
};


