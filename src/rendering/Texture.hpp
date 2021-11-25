#pragma once
#define TEXTURE_H
#include <iostream>
#include <glad/glad.h>
#include "Image.hpp"

class Texture
{
    private:
        // ATTRIBUTS

        GLuint _id;

    public:
        // CONSTRUCTORS
        /* basic constructor */
        
        Texture();
        Texture(const std::string filePath);
        
        /* move constructor */
        
        Texture(Texture&& rhs) noexcept;

        // DESTRUCTOR
        
        ~Texture();

        // ACCESSORS
        
        GLuint getId(){ return _id; }

        // METHODS
        
        bool load(const std::string& filePath);
        void bind(const int index);
};