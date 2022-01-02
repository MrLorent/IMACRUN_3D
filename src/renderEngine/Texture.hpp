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
        std::string _type;

    public:
        // OPERATORS
        /* Move assignment operator */

        Texture& operator=(Texture&& rhs) noexcept;

        /* Copy assignment operator */
        Texture& operator=(const Texture&) = delete; // We disable copying

        // CONSTRUCTORS
        /* basic constructor */
        
        Texture();
        Texture(const std::string &filePath);
        
        /* Copy constructor */

        Texture(const Texture&) = delete; // We disable copying

        /* move constructor */
        
        Texture(Texture&& rhs) noexcept;

        // DESTRUCTOR
        
        ~Texture();

        // ACCESSORS
        
        inline GLuint getId()const{ return _id; }
        inline std::string getType()const{return _type;}

        // METHODS
        
        bool load(const std::string& filePath);
};