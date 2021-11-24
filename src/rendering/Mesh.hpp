#pragma once
#define MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "Program.hpp"

#include "Texture.hpp"

struct Vertex{
    glm::vec3 _position;
    glm::vec3 _normal;
    glm::vec2 _texCoords;

    // CONSTRUCTOR
    Vertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 tex)
        :_position(pos), _normal(norm), _texCoords(tex){}
};

class Mesh
{
    private:
        // ATTRIBUTS
        
        unsigned int _vao;
        unsigned int _vbo;
        unsigned int _ibo;

        // PRIVATE METHODS

        void initVbo();
        void initVao();
    
    public:
        // PUBLIC ATTRIBUTS
        
        std::vector<Vertex> _vertices;
        std::vector<unsigned int> _indices;
        std::vector<Texture> _textures;

        // CONSTRUCTORS
        /* basic constructor */
        
        Mesh(
            const std::vector<Vertex>& vertices,
            const std::vector<unsigned int>& indices,
            std::vector<Texture>&& textures
        );

        // METHODS
        
        void draw(glimac::Program& shaders);
};