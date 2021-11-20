#pragma once

#define MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "Shader.hpp"

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TextCoords;
};

struct Texture
{
    unsigned int id;
    std::string type;
};

class Mesh
{
    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        // CONSTRUCTOR
        Mesh(
            std::vector<Vertex> vertices,
            std::vector<unsigned int> indices,
            std::vector<Texture> textures
        );

        // METHODES
        void draw(glimac::Shader &shader);
        
    private:
};