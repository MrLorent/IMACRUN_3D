#include "Map.hpp"
#include <iostream>
#include <fstream>
#include <cstring>

const char& Map::operator[](const size_t& i) const
{
    return _map[i];
}

char& Map::operator[](const size_t& i)
{
    return _map[i];
}

Map::Map()
    :_mapWidth(5),
     _seed(5),
     _random(std::mt19937_64(_seed))
{
    loadMapElements();
    _distribution = std::uniform_int_distribution<int>(0,_mapElements.size()-1);
    initMap();
}

Map::~Map()
{
}

void Map::loadMapElements()
{
    std::ifstream file("./assets/map/map_elements.txt");
      if(file) {
        std::vector<char> line ;
        char caractere;
        int j=0;
        int k=0;
        while ( k!=5 ) {  
            while ( j!=25 ) {  
                for (unsigned int i = 0 ; i != 5 ; i ++){ 
                    file.get(caractere); 
                    line.push_back(caractere);
                    j++;
                }
                _mapElements.push_back(line);
            }
            k++;
        }
        std::cout << "La map a ete chargée." << std::endl;
        remove("map_elements.txt");
    }else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
    }
}
    
/*
    std::vector<char> floor = {
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w'
    };
*/

void Map::initMap()
{
    for(unsigned int i=0; i<_mapElements[0].size() * 2; ++i){
        _map.push_back(_mapElements[0][i%_mapElements[0].size()]);
    }
    while(_map.size() < 20 * _mapWidth)
    {
        int randomIndex = _distribution(_random);
        for(unsigned int i=0; i<_mapElements[randomIndex].size(); ++i){
            _map.push_back(_mapElements[randomIndex][i]);
        }
    }
}

void Map::empty()
{
    _map.empty();
}

void Map::reloadMap()
{
    int randomIndex = _distribution(_random);
    for(unsigned int i=0; i<_mapElements[randomIndex].size(); ++i){
        _map.push_back(_mapElements[randomIndex][i]);
    }
}

size_t Map::size()
{
    return _map.size();
}

unsigned short int Map::getMapWidth()
{
    return _mapWidth;
}

void Map::deleteFirstLigne()
{
    for(short unsigned int i=0;i<_mapWidth;++i) _map.pop_front();
}