#include "Screen.hpp"

// OPERATORS
/* move assignment operator */

Screen& Screen::operator=(Screen&& rhs) noexcept
{
    if(this != &rhs)
    {
        _shaders = std::move(rhs._shaders);
        _background = std::move(rhs._background);
    }

    return *this;
}

// CONSTRUCTORS
/* basic constructors */

Screen::Screen(ScreenParams params)
    :_shaders(loadProgram(
        params.appPath.dirPath() + "src/shaders/texture2D.vs.glsl",
        params.appPath.dirPath() + "src/shaders/texture2D.fs.glsl"
     ))
{
    std::vector<Vertex> vertices = {
        // TOP LEFT
        Vertex(
            glm::vec3(-1.f, 1.f, 0.5f),  // Top left of the screen
            glm::vec3(0.f, 0.f, 1.f),   // normal of xy plan
            glm::vec2(0.f, 1.f)         // Top left of the texture image
        ),
        // TOP RIGHT
        Vertex(
            glm::vec3(1.f, 1.f, 0.5f),   // Top right of the screen
            glm::vec3(0.f, 0.f, 1.f),   // normal of xy plan
            glm::vec2(1.f, 1.f)         // Top right of the texture image
        ),
        // BOTTOM RIGHT
        Vertex(
            glm::vec3(1.f, -1.f, 0.5f),  // Bottom right of the screen
            glm::vec3(0.f, 0.f, 1.f),   // normal of xy plan
            glm::vec2(1.f, 0.f)         // Bottom right of the texture image
        ),
        // BOTTOM LEFT
        Vertex(
            glm::vec3(-1.f, -1.f, 0.5f), // Bottom left of the screen
            glm::vec3(0.f, 0.f, 1.f),   // normal of xy plan
            glm::vec2(0.f, 0.f)         // Bottom left of the texture image
        )
    };

    std::vector<unsigned int> indices = {
        3,0,2,  // Bottom left triangle
        1,0,2   // Top right triangle
    };

    std::vector<Texture> textures;
    textures.push_back(Texture(params.backgroundPath));

    _background = Mesh(vertices, indices, std::move(textures));
}

/* move constructor */
Screen::Screen(Screen&& rhs) noexcept
    :_shaders(std::move(rhs._shaders)),
     _background(std::move(rhs._background))
{
}

// DESTRUCTOR

Screen::~Screen()
{
}

// METHODS

void Screen::draw()
{
    _shaders.use();
    _background.draw(_shaders);
}