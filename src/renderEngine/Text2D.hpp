#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include "glimac/Program.hpp"
#include <map>
#include <glimac/glm.hpp>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H


//! The Character structure contain a TextureID, the size of the character, the bearing and the advance 

struct Character {
    unsigned int TextureID;  //!< ID handle of the glyph texture
    glm::ivec2   Size;       //!< Size of glyph
    glm::ivec2   Bearing;    //!< Offset from baseline to left/top of glyph
    unsigned int Advance;    //!< Offset to advance to next glyph
};

struct Shader{
    glimac::Program program;
    
    //! Constructor
    /*!
     * Constructor by default
     */
    Shader(){}
    
    //! Constructor
    /*!
    *\fn  Shader(const glimac::FilePath& applicationPath)
    *\param applicationPath : FilePath to the application.
    */
    Shader(const glimac::FilePath& applicationPath)
    :program(glimac::loadProgram(
        applicationPath.dirPath() + "src/renderEngine/shaders/text2D.vs.glsl",
        applicationPath.dirPath() + "src/renderEngine/shaders/text2D.fs.glsl")
    )
    {}
};

class Text2D
{
    private:
        // PRIVATE ATTRIBUTS

        std::map<char, Character> _alphabet;
        GLuint _vao;
        GLuint _vbo; 
        GLuint _ibo;
    
    public:
        // OPERATORS
        /* Move assignment operator */

        //! Move assignment operator
        Text2D& operator=(Text2D&& rhs) noexcept;

        //! Copy assignment operator
        Text2D& operator=(const Text2D&) = delete; // We disable copying

        // CONSTRUCTORS
        /* basic constructors */

        //! Constructor
        /*!
        *   Constructor by default
        */
        Text2D(){};

        //! Constructor
        /*!
        *\fn  Text2D(const unsigned int fontSize,const glimac::FilePath path, const std::string &fontName="Arial.ttf")
        *\param fontSize : Size of the font.
        *\param name : FilePath to the application.
        *\param fontName : name of the font, Arial by default.
        */
        Text2D(const unsigned int fontSize,const glimac::FilePath path, const std::string &fontName="Arial.ttf");

        /* Copy constructor */

        //! Copy constructor
        Text2D(const Text2D&) = delete; // We disable copying

        /* move constructor */

        //! Move constructor
        Text2D(Text2D&& rhs) noexcept;

        // DESTRUCTORS
        //! Destructor
        /*!
         * Destructor by default.
         */
        ~Text2D();
        
        // METHODS
        //! Method
        /*!
        *\fn void draw(std::string text, glm::vec2 pos, glm::vec3 color, glm::mat4 projectionMatrix);
        *\param text : the text we want to display.
        *\param pos : glm::vec2 giving the position of the begining of the text.
        *\param color : glm::vec3 giving the color of the text.
        *\param projetctionMatrix : the text projection matrix.
        * Method that draw the given text to the right place and with the right color.
        */
        void draw(
            std::string text,   /* Text to write */
            glm::vec2 pos,      /* Position in screen, starting from bottom left */
            glm::vec3 color,    /* Text color */
            glm::mat4 projectionMatrix
        );

        //PUBLIC ATTRIBUTES
        
        Shader shader;
};