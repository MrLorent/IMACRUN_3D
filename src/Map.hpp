#pragma once
#define MAP_HPP

#include <vector>

class Map
{
private:
    unsigned int _index;
    unsigned short int _mapWidth;
    std::vector<char> _map;

public:
    // CONSTANTS
    const static char WALL = 'w';
    const static char FLOOR = 'f';
    const static char HOLE = 'h';

    // OPERATORS
    const char& operator[](const size_t& i) const;

    // CONSTRUCTEURS
    Map();

    // DESTRUCTEURS
    ~Map();

    unsigned int getIndex();
    unsigned short int getMapWidth();

    void incrementIndex();
};


