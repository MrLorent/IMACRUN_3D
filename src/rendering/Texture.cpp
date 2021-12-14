#include "Texture.hpp"

// CONSTRUCTORS
/* basic constructors */

Texture::Texture()
    :_id(0),_type(""){}

Texture::Texture(const std::string filePath)
    :_id(0)
{
    const size_t lastSlashIndex = filePath.rfind('/');
    _type=filePath.substr(lastSlashIndex+1, _type.size()-4);
    if(filePath.find("/.") == std::string::npos)
    {
        load(filePath);
    }
}

/* move constructor */ 

Texture::Texture(Texture&& rhs) noexcept
    :_id(rhs._id),_type(rhs._type)
{
    rhs._id = 0;
    rhs._type ="";
}

// DESTRUCTOR

Texture::~Texture()
{
    glDeleteTextures(1, &_id);
    _id = 0;
    _type ="";
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