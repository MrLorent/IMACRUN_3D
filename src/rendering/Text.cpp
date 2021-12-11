// #include "Text.hpp"

Text::Text(const std::string fontName, const unsigned int fontSize, glimac::FilePath path):shader(path)
{
    if (FT_Init_FreeType(&_ft))
        {
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        }

    if (FT_New_Face(_ft, ("./assets/fonts/"+fontName).c_str() , 0, &_font))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;  
    }else{

        FT_Set_Pixel_Sizes(_font, 0, fontSize); 
        

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
    
        for (unsigned char c = 0; c < 128; c++)
        {
            // load character glyph 
            if (FT_Load_Char(_font, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
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
                _font->glyph->bitmap.width,
                _font->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                _font->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = {
                texture, 
                glm::ivec2(_font->glyph->bitmap.width, _font->glyph->bitmap.rows),
                glm::ivec2(_font->glyph->bitmap_left, _font->glyph->bitmap_top),
                static_cast<unsigned int>(_font->glyph->advance.x)
            };
            _alphabet.insert(std::pair<char, Character>(c, character));
        }
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    }
    FT_Done_Face(_font);
    FT_Done_FreeType(_ft);

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


// Text::~Text()
// {
// }

void Text::draw(Shader &shader, std::string text, float x, float y, float scale, glm::vec3 color, const unsigned int window_width, const unsigned int window_height){
    _window_width=window_width;
    _window_height=window_height; 
    // activate corresponding render state	
    shader.program.use();

     glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(_window_width), 0.0f, static_cast<float>(_window_height));
    glUniformMatrix4fv(glGetUniformLocation(shader.program.getGLId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));


    glUniform3f(glGetUniformLocation(shader.program.getGLId(), "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(_vao);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) 
    {
        Character ch = _alphabet[*c];
        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },            
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }           
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            std::cout << "ch.texture : "<< ch.TextureID << std::endl;

        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
