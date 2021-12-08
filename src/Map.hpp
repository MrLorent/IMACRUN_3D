#pragma once
#define MAP_HPP

#include <vector>

class Map
{
private:
    unsigned int _index;
    std::vector<char> _map;

public:
    Map();
    ~Map();
};


