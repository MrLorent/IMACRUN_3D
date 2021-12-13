#include "Map.hpp"

const char& Map::operator[](const size_t& i) const
{
    return _map[i];
}

char& Map::operator[](const size_t& i)
{
    return _map[i];
}

Map::Map()
    :_index(1),
     _mapWidth(5)
{
    _map = {
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','h','h','f','w',
        'w','h','h','f','w',
        'w','h','h','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','h','h','w',
        'w','f','h','h','w',
        'w','f','h','h','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','f',
        'w','f','f','f','f',
        'w','f','f','f','f',
        'w','w','w','w','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'f','f','f','f','w',
        'f','f','f','f','w',
        'f','f','f','f','w',
        'w','w','w','w','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w'
    };
}

Map::~Map()
{
}

unsigned int Map::getIndex()
{
    return _index;
}

unsigned short int Map::getMapWidth()
{
    return _mapWidth;
}

void Map::incrementIndex()
{
    if(_index < _map.size()){
        _index++;
    }
}

void Map::setIndex(const int newIndex)
{
    _index = newIndex;
}