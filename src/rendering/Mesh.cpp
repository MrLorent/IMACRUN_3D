#include "Mesh.hpp"

// CONSTRUCTORS
/* basic constructors */

Mesh::Mesh(
    const std::vector<Vertex>& vertices,
    const std::vector<unsigned int>& indices,
    std::vector<Texture>&& textures
)
    :vertices(vertices),
     indices(indices),
     textures(std::move(textures))
{
    initVbo();
    initIbo();
    initVao();
}

// DESTRUCTOR

Mesh::~Mesh()
{
    glDeleteBuffers(1, &_vbo);
    glDeleteVertexArrays(1, &_vao);
}

Mesh::Mesh(Mesh&& rhs) noexcept
    :vertices(rhs.vertices),
     indices(rhs.indices),
     textures(std::move(rhs.textures)),
     _vbo(rhs._vbo),
     _ibo(rhs._ibo),
     _vao(rhs._vao)
{
   rhs._vbo = 0;
   rhs._ibo = 0;
   rhs._vao = 0;
}

// PRIVATE METHODS

void Mesh::initVbo()
{
    // VBO
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo); 

        glBufferData(
            GL_ARRAY_BUFFER,
            vertices.size()*sizeof(Vertex),
            vertices.data(),
            GL_STATIC_DRAW
        );

    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void Mesh::initIbo()
{
    glGenBuffers(1, &_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
        
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            indices.size() * sizeof(GLuint),
            indices.data(),
            GL_STATIC_DRAW
        );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::initVao()
{
    // VAO
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXTURE = 2;

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);

        glBindBuffer(GL_ARRAY_BUFFER, _vbo);

            //POSITION
            glVertexAttribPointer(
                VERTEX_ATTR_POSITION,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                (const void*)(offsetof(Vertex, position))
            );

                //NORMAL
            glVertexAttribPointer(
                VERTEX_ATTR_NORMAL,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                (const void*)(offsetof(Vertex, normal))
            );

            //TEXTURE
            glVertexAttribPointer(
                VERTEX_ATTR_TEXTURE,
                2,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                (const void*)(offsetof(Vertex, texCoords))
            );

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// PUBLIC METHODS

void Mesh::draw(glimac::Program& shaders)
{
    for (size_t i=0; i < textures.size(); i++)
    {
        glUniform1i(glGetUniformLocation(shaders.getGLId(), "uTexture"), i);
        textures[i].bind(i);
    }

    glBindVertexArray(_vao);
        glDrawElements(
            GL_TRIANGLES,
            indices.size(),
            GL_UNSIGNED_INT,
            0
        );
    glBindVertexArray(0);
}
