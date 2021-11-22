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

        bool load(const glimac::FilePath applicationPath, const std::string& fileName);
        void bind(const int index);
    private:
        GLuint _id;
};