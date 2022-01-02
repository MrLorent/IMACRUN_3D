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
    :_mapWidth(5),
     _seed(5),
     _random(std::mt19937_64(_seed))
{
    loadMapElements();
    _distribution = std::uniform_int_distribution<int>(0,_mapElements.size()-1);
}

Map::~Map()
{
}

void Map::loadMapElements()
{
    std::ifstream file;
    try 
    {
        file.open("./assets/map/map_elements.txt");
        std::vector<char> element;
        char caractere;
        int nbElements;
        int linePerElement;
        file >> nbElements;
        file >> linePerElement;

        for(int k=0; k<nbElements;++k ) {
            for(int j=0; j<_mapWidth*linePerElement; ++j){ 
                file >> caractere;
                element.push_back(caractere);
            }
            _mapElements.push_back(element);
            element.clear();
        }
        file.close();
    }catch(const std::ifstream::failure& e)
    {
        std::cerr << "ERREUR: Impossible d'ouvrir le fichier map_element.txt." << std::endl;
    }
}

void Map::initMap()
{
    std::vector<char> mapStart = {
        'x','f','f','f','x',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'l','f','f','f','l',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'x','f','f','f','x',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'l','f','f','f','l',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','c','f','w',
        'w','f','c','f','w',
        'x','f','c','f','x',
        'w','f','c','f','w',
        'w','f','c','f','w',
        'w','f','c','f','w',
        'l','f','f','f','l',
        'w','f','f','f','w',
        'w','o','o','o','w',
        'w','f','f','f','w',
        'w','f','f','f','w'
    };
    for(size_t i=0; i<mapStart.size(); ++i)
    {
        if(mapStart[i] == LIGHT && firstLights.size() < 2)
        {
            firstLights.push_back(glm::vec3(
                i%_mapWidth-2,
                2.f,
                i/_mapWidth + 1
            ));
        }
        _map.push_back(mapStart[i]);
    }
    
    // for(int i=0; i<_mapElements[0].size() * 2; ++i){
    //     _map.push_back(_mapElements[0][i%_mapElements[0].size()]);
    // }
    while(_map.size() < 25 * _mapWidth)
    {
        int randomIndex = _distribution(_random);
        for(int i=0; i<_mapElements[randomIndex].size(); ++i){
            _map.push_back(_mapElements[randomIndex][i]);
        }
    }

}
void Map::add(const char c)
{
    _map.push_back(c);
}

void Map::reloadMap()
{
    int randomIndex = _distribution(_random);
    for(int i=0; i<_mapElements[randomIndex].size(); ++i){
        _map.push_back(_mapElements[randomIndex][i]);
    }
}

size_t Map::getSize()
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