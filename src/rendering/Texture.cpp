#include "Texture.hpp"

// CONSTRUCTEURS
Texture::Texture()
    :_id(0)
{}

Texture::Texture(const int id)
    :_id(id)
{}

// DESTRUCTEURS
Texture::~Texture()
{
    glDeleteTextures(1, &_id);
    _id = 0;
}

bool Texture::load(const std::string& fileName)
{
    
}