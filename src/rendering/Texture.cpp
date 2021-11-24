#include "Texture.hpp"

// CONSTRUCTORS
/* basic constructors */
Texture::Texture()
    :_id(0){}

Texture::Texture(const glimac::FilePath applicationPath, const std::string& fileName)
    :_id(0)
{
    load(applicationPath, fileName);
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
bool Texture::load(const glimac::FilePath applicationPath, const std::string& fileName)
{
    std::unique_ptr<glimac::Image> image = glimac::loadImage(
        applicationPath.dirPath()+"assets/textures/"+fileName
    );
    
    if(image == nullptr)
    {
        std::cout << "Couldn't load " << applicationPath.dirPath()+"assets/textures/"+fileName << std::endl;
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