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

bool Texture::load(const glimac::FilePath applicationPath, const std::string& fileName)
{
    std::unique_ptr<glimac::Image> image = glimac::loadImage(
        applicationPath.dirPath()+"assets/textures/"+fileName
    );
    
    if(image == nullptr)
    {
        std::cout << "Couldn't load " << applicationPath.dirPath()+fileName << std::endl;
        return false;
    }

    
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            image->getWidth(),
            image->getHeight(),
            0,
            GL_RGBA,
            GL_FLOAT,
            image->getPixels()
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER,
            GL_LINEAR
        );

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MAG_FILTER,
            GL_LINEAR
        );

    glBindTexture(GL_TEXTURE_2D,0);

    return true;
}

void Texture::bind(const int index)
{
    if(_id != 0)
    {
        glActiveTexture(GL_TEXTURE0 + index);
        glBindTexture(GL_TEXTURE_2D, _id);
    }
}