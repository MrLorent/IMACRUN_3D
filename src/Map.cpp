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
    initMap();
}

Map::~Map()
{
}

void Map::loadMapElements()
{
    std::ifstream file("./assets/map/map_elements.txt");
    if(file) {
        std::vector<char> element;
        char caractere;
        int nbElements;
        int linePerElement;
        file >> nbElements;
        file >> linePerElement;
        std::cout << nbElements << std::endl;
        std::cout << linePerElement << std::endl;

        for(int k=0; k<nbElements;++k ) {
            for(int j=0; j<_mapWidth*linePerElement; ++j){ 
                file >> caractere;
                element.push_back(caractere);
                std::cout << " " << caractere << " ";
                if(j%_mapWidth == 4) std::cout << std::endl;
            }
            _mapElements.push_back(element);
            element.clear();
            std::cout << std::endl;
        }
        file.close();
    }else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
    }
    for(int i=0; i<_mapElements.size(); ++i)
    {
        std::cout << _mapElements[i].size() << std::endl;
    }
    // std::vector<char> floor = {
    //     'w','f','f','f','w',
    //     'w','f','f','f','w',
    //     'w','f','f','f','w',
    //     'w','f','f','f','w',
    //     'w','f','f','f','w'
    // };
    // _mapElements.push_back(floor);

    // std::vector<char> leftHole = {
    //     'w','f','f','f','w',
    //     'w','f','h','h','w',
    //     'w','f','h','h','w',
    //     'w','f','h','h','w',
    //     'w','f','f','f','w'
    // };
    // _mapElements.push_back(leftHole);

    // std::vector<char> rightHole = {
    //     'w','f','f','f','w',
    //     'w','h','h','f','w',
    //     'w','h','h','f','w',
    //     'w','h','h','f','w',
    //     'w','f','f','f','w'
    // };
    // _mapElements.push_back(rightHole);

    // std::vector<char> leftTurn = {
    //     'w','f','f','f','w',
    //     'w','f','f','f','f',
    //     'w','f','f','f','f',
    //     'w','f','f','f','f',
    //     'w','w','w','w','w'
    // };
    // _mapElements.push_back(leftTurn);

    // std::vector<char> rightTurn = {
    //     'w','f','f','f','w',
    //     'f','f','f','f','w',
    //     'f','f','f','f','w',
    //     'f','f','f','f','w',
    //     'w','w','w','w','w'
    // };
    // _mapElements.push_back(rightTurn);
}

void Map::initMap()
{
    std::vector<char> mapStart = {
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','f','f','w',
        'w','f','c','f','w',
        'w','f','c','f','w',
        'w','f','c','f','w',
        'w','f','c','f','w',
        'w','f','c','f','l'
    };
    for(size_t i=0; i<mapStart.size(); ++i)
    {
        if(mapStart[i] == LIGHT && firstLights.size() < 4)
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
    while(_map.size() < 20 * _mapWidth)
    {
        int randomIndex = _distribution(_random);
        for(int i=0; i<_mapElements[randomIndex].size(); ++i){
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
    for(int i=0; i<_mapElements[randomIndex].size(); ++i){
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