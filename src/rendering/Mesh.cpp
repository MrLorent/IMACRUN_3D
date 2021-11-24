#include "Mesh.hpp"

Mesh::Mesh(
    const std::vector<Vertex>& vertices,
    const std::vector<unsigned int>& indices,
    std::vector<Texture>&& textures
)
    :_vertices(vertices),
     _indices(indices),
     _textures(std::move(textures))
{
    initVbo();
    initVao();
}

void Mesh::initVbo()
{
    // VBO
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo); 

        glBufferData(
            GL_ARRAY_BUFFER,
            _vertices.size()*sizeof(Vertex),
            _vertices.data(),
            GL_STATIC_DRAW
        );

    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void Mesh::initVao()
{
    // VAO
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXTURE = 2;

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
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
                (const void*)(offsetof(Vertex, _position))
            );

                //NORMAL
            glVertexAttribPointer(
                VERTEX_ATTR_NORMAL,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                (const void*)(offsetof(Vertex, _normal))
            );

            //TEXTURE
            glVertexAttribPointer(
                VERTEX_ATTR_TEXTURE,
                2,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                (const void*)(offsetof(Vertex, _texCoords))
            );

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Mesh::draw(glimac::Program& shaders)
{
    for(uint i=0; i < _textures.size(); i++)
    {
        glUniform1i(glGetUniformLocation(shaders.getGLId(), "uTexture"), i);
        _textures[i].bind(i);
    }

    glBindVertexArray(_vao);
        glDrawArrays(
            GL_TRIANGLES,
            0,
            _vertices.size()
        );
    glBindVertexArray(0);
}