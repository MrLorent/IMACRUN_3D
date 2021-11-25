#pragma once
#define TEXTURE_H
#include <iostream>
#include <glad/glad.h>
#include "FilePath.hpp"
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
        Texture(const glimac::FilePath applicationPath, const std::string& fileName);
        
        /* move constructor */
        
        Texture(Texture&& rhs) noexcept;

        // DESTRUCTOR
        
        ~Texture();

        // ACCESSORS
        
        GLuint getId(){ return _id; }

        // METHODS
        
        bool load(const glimac::FilePath applicationPath, const std::string& fileName);
        void bind(const int index);
};