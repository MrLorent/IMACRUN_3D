#pragma once
#define MESH_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

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

    // OPERATORS

    bool operator==(const Vertex& other) const {
        return _position == other._position && _normal == other._normal && _texCoords == other._texCoords;
    }

    // CONSTRUCTOR
    
    Vertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 tex)
        :_position(pos), _normal(norm), _texCoords(tex){}

};

namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex._position) ^
                   (hash<glm::vec3>()(vertex._normal) << 1)) >> 1) ^
                   (hash<glm::vec2>()(vertex._texCoords) << 1);
        }
    };
}

class Mesh
{
    private:
        // ATTRIBUTS
        
        uint _vao;
        uint _vbo;
        uint _ibo;

        // PRIVATE METHODS

        void initVbo();
        void initIbo();
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