#pragma once
#define TEXTURE_H
#include <iostream>
#include <string>
#include <glad/glad.h>
#include "FilePath.hpp"
#include "Image.hpp"

class Texture
{
    public:
        Texture();
        Texture(const int id);
        ~Texture();

        // ACCESSORS
        uint getId(){ return _id; }

        bool load(const glimac::FilePath applicationPath, const std::string& fileName);
        void bind(const int index);
    private:
        uint _id;
};