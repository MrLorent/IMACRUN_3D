#pragma once
#define MESH_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

#include "Program.hpp"
#include "Texture.hpp"

struct Textures{
    Texture diffuse;
    Texture specular;
    float shininess; 

    Textures():shininess(0){};
};


struct Vertex{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;

    // OPERATORS

    bool operator==(const Vertex& other) const {
        return position == other.position && normal == other.normal && texCoords == other.texCoords;
    }

    // CONSTRUCTOR

    Vertex(){}
    Vertex(glm::vec3 p, glm::vec3 n, glm::vec2 t)
        :position(p), normal(n), texCoords(t)
    {}
};

namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.position) ^
                   (hash<glm::vec3>()(vertex.normal) << 1)) >> 1) ^
                   (hash<glm::vec2>()(vertex.texCoords) << 1);
        }
    };
}

class Mesh
{
    private:
        // ATTRIBUTS
        
        GLuint _vao;
        GLuint _vbo;
        GLuint _ibo;

        // PRIVATE METHODS

        void initVbo();
        void initIbo();
        void initVao();
        void bindTexture(int index, GLint textureId, const char* uniformName, const GLuint shadersId) const;
    
    public:
        // PUBLIC ATTRIBUTS
        
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        Textures textures;

        // OPERATORS
        /* Move assignment operator */

        Mesh& operator=(Mesh&& rhs) noexcept;

        /* Copy assignment operator */
        Mesh& operator=(const Mesh&) = delete; // We disable copying

        // CONSTRUCTORS
        /* basic constructor */
        
        Mesh();
        Mesh(
            const std::vector<Vertex>& vertices,
            const std::vector<unsigned int>& indices,
            Textures&& textures
        );

        /* Copy constructor */

        Mesh(const Mesh&) = delete; // We disable copying

        /* move constructor */

        Mesh(Mesh&& rhs) noexcept;

        // DESTRUCTOR

        ~Mesh();

        // METHODS
        
        void draw(glimac::Program& shaders);

};