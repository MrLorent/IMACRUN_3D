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
        //L'ouverture s'est bien passée, on peut donc lire
        //On commence à lire le fichier
        /*int roadLength;
        file >> roadLength;
        std::cout << "\nLongueur route : " << roadLength << std::endl ;*/

        std::vector<char> line ;
        //std::string line;
        //char cases[6];
        char caractere;
        int j=0;
        while ( j!=25 ) {  
            std::cout << "\nLigne : " ;
            for (unsigned int i = 0 ; i != 5 ; i ++){ 
                //std::getline(file, line); 
                //char caseu;
                file.get(caractere); 
                //std::strcpy(cases, line.c_str());
                //cases[i] = line[i];
                line.push_back(caractere);
                std::cout << line[j] << " - " ;
                j++;
            }
            
            //std::cout << std::endl ;
            _mapElements.push_back(line);
            //file.seekg(2+5*j, iostream::beg);
            //std::cout << _map[0,1] << " ";
        }
        std::cout << std::endl ;
        std::cout << "La map a ete chargée." << std::endl;
        remove("map_elements2.txt");
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