#pragma once
#define TEXTURE_H
#include <iostream>
#include <string>
#include <glad/glad.h>
#include "FilePath.hpp"
#include "Image.hpp"

class Texture
{
    private:
        // ATTRIBUTS
        uint _id;

    public:
        // CONSTRUCTOR
        // basic
        Texture();
        Texture(const glimac::FilePath applicationPath, const std::string& fileName);
        // move
        Texture(Texture&& rhs) noexcept;

        // DESTRUCTOR
        ~Texture();

        // ACCESSORS
        uint getId(){ return _id; }

        bool load(const glimac::FilePath applicationPath, const std::string& fileName);
        void bind(const int index);
};