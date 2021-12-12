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
        applicationPath.dirPath() + "src/shaders/text.vs.glsl",
        applicationPath.dirPath() + "src/shaders/text.fs.glsl")
    )
    {}
};

class Text
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
        Text(){};
        Text(const std::string fontName, const unsigned int fontSize, glimac::FilePath name);
        //~Text();
        void draw(std::string text, float x, float y, float scale, glm::vec3 color, unsigned int window_width, const unsigned int window_height);

        Shader shader;
};