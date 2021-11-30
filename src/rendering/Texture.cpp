#include "Texture.hpp"

// CONSTRUCTORS
/* basic constructors */

Texture::Texture()
    :_id(0){}

Texture::Texture(const std::string filePath)
    :_id(0)
{
    if(filePath.find("/.") == std::string::npos)
    {
        load(filePath);
    }
}

/* move constructor */

Texture::Texture(Texture&& rhs) noexcept
    :_id(rhs._id)
{
    rhs._id = 0;
}

// DESTRUCTOR

Texture::~Texture()
{
    glDeleteTextures(1, &_id);
    _id = 0;
}

// METHODS

bool Texture::load(const std::string& filePath)
{
    std::unique_ptr<glimac::Image> image = glimac::loadImage(
        "./assets/models/"+filePath
    );
    
    if(image == nullptr)
    {
        std::cout << "Couldn't load " << "./assets/Models/"+filePath << std::endl;
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