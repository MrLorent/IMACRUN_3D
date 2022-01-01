#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include "glimac/Program.hpp"
#include <map>
#include <glimac/glm.hpp>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H



struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

struct Shader{
    glimac::Program program;
    Shader(){}
    Shader(const glimac::FilePath& applicationPath)
    :program(glimac::loadProgram(
        applicationPath.dirPath() + "src/shaders/text2D.vs.glsl",
        applicationPath.dirPath() + "src/shaders/text2D.fs.glsl")
    )
    {}
};

class Text2D
{
    private:
        std::map<char, Character> _alphabet;
        FT_Library _ft;
        FT_Face _font;
        GLuint _vao;
        GLuint _vbo; 
        GLuint _ibo;
        
        unsigned int _window_width, _window_height;
    
    public:
        // OPERATORS
        /* Move assignment operator */

        Text2D& operator=(Text2D&& rhs) noexcept;

        /* Copy assignment operator */
        Text2D& operator=(const Text2D&) = delete; // We disable copying

        // CONSTRUCTORS
        /* basic constructors */

        Text2D(){};
        Text2D(const unsigned int fontSize, glimac::FilePath name, std::string fontName="Arial.ttf");

        /* Copy constructor */

        Text2D(const Text2D&) = delete; // We disable copying

        /* move constructor */
        
        Text2D(Text2D&& rhs) noexcept;

        // DESTRUCTORS

        ~Text2D();
        
        // METHODS
        
        void draw(
            std::string text,   /* Text to write */
            glm::vec2 pos,      /* Position in screen, starting from bottom left */
            glm::vec3 color,    /* Text color */
            glm::mat4 projectionMatrix
        );

        Shader shader;
};