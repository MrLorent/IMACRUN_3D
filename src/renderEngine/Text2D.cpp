#include "Text2D.hpp"

// OPERATORS
/* Move assignment operator */

Text2D& Text2D::operator=(Text2D&& rhs) noexcept
{
    if(this != &rhs)
    {
        // ALPHABET
        _alphabet.clear();
        _alphabet = rhs._alphabet;
        for(size_t i=0; i < _alphabet.size(); i++)
        {
            rhs._alphabet[i].TextureID = 0;
        }

        // VBO
        glDeleteBuffers(1, &_vbo);
        _vbo = rhs._vbo;
        rhs._vbo = 0;

        // VAO
        glDeleteVertexArrays(1, &_vao);
        _vao = rhs._vao;
        rhs._vao = 0;

        // IBO
        _ibo = rhs._ibo;
        rhs._ibo = 0;

        shader = std::move(rhs.shader);
    }

    return *this;
}

// CONSTRUCTORS
/* basic constructor */
Text2D::Text2D(const unsigned int fontSize, glimac::FilePath path, const std::string &fontName):shader(path)
{
    FT_Library ft; 
    FT_Face font;
    
    if (FT_Init_FreeType(&ft))
    {
        std::cerr << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }

    if (FT_New_Face(ft, ("./assets/fonts/"+fontName).c_str() , 0, &font))
    {
        std::cerr << "ERROR::FREETYPE: Failed to load font" << std::endl;  
    }
    else
    {
        FT_Set_Pixel_Sizes(font, 0, fontSize); 

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
    
        for (unsigned char c = 0; c < 128; c++)
        {
            // load character glyph 
            if (FT_Load_Char(font, c, FT_LOAD_RENDER))
            {
                std::cerr << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                font->glyph->bitmap.width,
                font->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                font->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = {
                texture, 
                glm::ivec2(font->glyph->bitmap.width, font->glyph->bitmap.rows),
                glm::ivec2(font->glyph->bitmap_left, font->glyph->bitmap_top),
                static_cast<unsigned int>(font->glyph->advance.x)
            };
            _alphabet.insert(std::pair<char, Character>(c, character));
        }
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    }
    FT_Done_Face(font);
    FT_Done_FreeType(ft);

    //Create and bind vao,vbo and ibo
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1,&_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    std::vector<uint32_t> indices;
    for(int i=1; i<2; i++){
        indices.push_back(i);
        indices.push_back(i+1);
        indices.push_back(i+2);
    }
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*2 * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    const GLuint VERTEX = 0;
    glEnableVertexAttribArray(VERTEX);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glVertexAttribPointer(VERTEX, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

/* move constructor */

Text2D::Text2D(Text2D&& rhs) noexcept
    :_alphabet(rhs._alphabet),
     _vao(rhs._vao),
     _vbo(rhs._vbo),
     _ibo(rhs._ibo),
     shader(std::move(rhs.shader))
{
    for(size_t i=0; i < _alphabet.size(); i++)
    {
        rhs._alphabet[i].TextureID = 0;
    }
    rhs._vao = 0;
    rhs._vbo = 0;
    rhs._ibo = 0;
}

/* DESTRUCTOR */

Text2D::~Text2D()
{
    for(size_t i=0; i < _alphabet.size(); i++)
    {
        glDeleteTextures(1, &_alphabet[i].TextureID);
    }
    glDeleteBuffers(1, &_vbo);
    glDeleteVertexArrays(1, &_vao);
}

void Text2D::draw(std::string text, glm::vec2 pos, glm::vec3 color, glm::mat4 projectionMatrix){

    // activate corresponding render state	
    shader.program.use();

    /* Send the projection matrix to the shader */
    GLint uProjectionMatrix = glGetUniformLocation(shader.program.getGLId(), "uProjectionMatrix");
    glUniformMatrix4fv(
        uProjectionMatrix,
        1,
        GL_FALSE,
        glm::value_ptr(projectionMatrix)
    );

    /* Send the color to the fragment shader */
    GLint uTextColor = glGetUniformLocation(shader.program.getGLId(), "uTextColor");
    glUniform3f(
        uTextColor,
        color.x,
        color.y,
        color.z
    );

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(_vao);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); ++c) 
    {
        Character ch = _alphabet[*c];
        float xpos = pos.x + ch.Bearing.x;
        float ypos = pos.y - (ch.Size.y - ch.Bearing.y);

        float w = ch.Size.x;
        float h = ch.Size.y;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },            
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }           
        };
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        

        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        pos.x += (ch.Advance >> 6) ; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        glDisable(GL_BLEND);
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
