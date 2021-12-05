#pragma once
#define TEXT_HPP
#include <string>
#include <vector>
#include <map>
#include "glm/glm.hpp"



// -------- structure de Char -----------

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};



class Font
{

private:
    // Attributs 
    std::map<char, Character> _characters;
    
public:
    Font(/* prend chemin vers la fonte et initialise tabkeay de char  */);
    ~Font();
};

Font::Font(/* args */)
{
}

Font::~Font()
{
}
