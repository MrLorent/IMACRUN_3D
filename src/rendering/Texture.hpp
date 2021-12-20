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
        // CONSTRUCTORS
        /* basic constructor */
        
        Texture();
        Texture(const std::string filePath);
        
        /* move constructor */
        
        Texture(const Texture&) = delete;            // We disable copying
        Texture& operator=(const Texture&) = delete; // We disable copying
        
        Texture(Texture&& rhs) noexcept;

        /* Move assignment operator */
        
        Texture& operator=(Texture&& rhs) noexcept;

        // DESTRUCTOR
        
        ~Texture();

        // ACCESSORS
        
        inline GLuint getId(){ return _id; }
        inline std::string getType(){return _type;}

        // METHODS
        
        bool load(const std::string& filePath);
        void bind(const int index);
};