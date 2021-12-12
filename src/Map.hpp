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
    static constexpr char WALL = 'w';
    static constexpr char FLOOR = 'f';
    static constexpr char HOLE = 'h';

    // OPERATORS
    const char& operator[](const size_t& i) const;

    // CONSTRUCTEURS
    Map();

    // DESTRUCTEURS
    ~Map();

    unsigned int getIndex();
    unsigned short int getMapWidth();

    void incrementIndex();
    void setIndex(const int newIndex);
};


