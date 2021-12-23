#pragma once
#define MAP_HPP

#include <vector>
#include <deque>
#include <random>
#include <iostream>

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
    static constexpr char PASSED_TURN = 'p';

    // OPERATORS
    const char& operator[](const size_t& i) const;
    char& operator[](const size_t& i);

    // CONSTRUCTEURS
    Map();

    // DESTRUCTEURS
    ~Map();

    // GETTERS
    size_t size();
    unsigned short int getMapWidth();

    // METHODS
    void initMap();
    void empty();
    void reloadMap();
    void deleteFirstLigne();
};


