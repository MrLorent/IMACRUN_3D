#include "Map.hpp"

Map::Map()
    :_index(0)
{
    for(int i; i<200;i++)
    {
        if(i%5 == 0 || i%5 ==4)
        {
            _map.push_back('w');
        }
        else
        {
            _map.push_back('f');
        }
    }
}

Map::~Map()
{
}

unsigned int Map::getIndex()
{
    return _index;
}

void Map::incrementIndex()
{
    if(_index < _map.size())
        _index++;
}