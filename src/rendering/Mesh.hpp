#pragma once
#define MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "Texture.hpp"

struct Vertex{
    glm::vec3 _position;
    glm::vec3 _normal;
    glm::vec2 _texCoords;

    Vertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 tex)
        :_position(pos), _normal(norm), _texCoords(tex)
    {}
};

class Mesh
{
    public:
        std::vector<Vertex> _vertices;
        std::vector<unsigned int> _indices;
        std::vector<Texture> _textures;

        Mesh(const glimac::FilePath applicationPath, const std::string& fileName);
        void draw();
    private:
        unsigned int _vao;
        unsigned int _vbo;
        unsigned int _ibo;

        void initVbo();
        void initVao();
};