#include "Text.hpp"

Text::Text(const std::string fontName, const unsigned int fontSize)
{
    if (FT_Init_FreeType(&_ft))
        {
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        }

    if (FT_New_Face(_ft, "fonts/"+fontName , 0, &_face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;  
    }

    FT_Set_Pixel_Sizes(face, 0, fontSize); 
}

Text::~Text()
{
}