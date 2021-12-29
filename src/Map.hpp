#pragma once
#define MAP_HPP

#include <vector>
#include <deque>
#include <random>
#include <iostream>
#include <fstream>

#include "glm/glm.hpp"
#include "iostream"

class Map
{
private:
    unsigned short int _mapWidth;
    std::deque<char> _map;
    std::vector<std::vector<char>> _mapElements;
    
    unsigned _seed;
    std::mt19937_64 _random;
    std::uniform_int_distribution<int> _distribution;

    void loadMapElements();

public:
    // CONSTANTS
    static constexpr char WALL = 'w';
    static constexpr char LIGHT = 'l';
    static constexpr char FLOOR = 'f';
    static constexpr char HOLE = 'h';
    static constexpr char BAREL = 'b';
    static constexpr char PASSED_TURN = 'p';
    static constexpr char COLLECTIBLE = 'c';
    static constexpr char ARCH = 'a';
    static constexpr char PLANK = 'o';



    // ATTRIBUTS
    std::vector<glm::vec3> firstLights;

    // OPERATORS
    const char& operator[](const size_t& i) const;
    char& operator[](const size_t& i);

    // CONSTRUCTEURS
    Map();

    // DESTRUCTEURS
    ~Map();

    // GETTERS
    size_t getSize();
    unsigned short int getMapWidth();

    // METHODS
    void initMap();
    void add(const char c);
    void reloadMap();
    void deleteFirstLigne();
};


