#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include "Mesh.hpp"

Mesh::Mesh(
    const glimac::FilePath applicationPath,
    const std::string& fileName)
{
    //Chargement du model 3D
    std::string inputfile = "./assets/models/alliance.obj";
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials; 
    
    std::string warn;
    std::string err;
    bool ret = tinyobj::LoadObj(&attrib,&shapes,&materials, &warn, &err, inputfile.c_str(), nullptr);
    
    if (!err.empty()) { // `err` may contain warning message.
        std::cerr << err << std::endl;
    }

    if (!ret) {
        exit(1);
    }

    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            int fv = shapes[s].mesh.num_face_vertices[f];

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {

                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                // access to vertex
                Vertex newVertex = Vertex(
                    
                    // POSITION
                    glm::vec3(
                        tinyobj::real_t(attrib.vertices[3*idx.vertex_index+0]), // vx
                        tinyobj::real_t(attrib.vertices[3*idx.vertex_index+1]), // vy
                        tinyobj::real_t(attrib.vertices[3*idx.vertex_index+2])  // vz
                    ),

                    // NORMAL
                    glm::vec3(
                        tinyobj::real_t(attrib.normals[3*idx.normal_index+0]),  // nx
                        tinyobj::real_t(attrib.normals[3*idx.normal_index+1]),  // ny
                        tinyobj::real_t(attrib.normals[3*idx.normal_index+2])   // nz
                    ),

                    // TEXTURE_COORDINATES
                    glm::vec2(
                        tinyobj::real_t(attrib.texcoords[2*idx.texcoord_index+0]),  //tx
                        tinyobj::real_t(attrib.texcoords[2*idx.texcoord_index+1])   //ty
                    )
                );

                _vertices.push_back(newVertex);
            }
            index_offset += fv;
        }
    }

    setupMesh();
}

void Mesh::setupMesh()
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

void Mesh::draw()
{
    glBindVertexArray(_vao);
        glDrawArrays(
                GL_TRIANGLES,
                0,
                _vertices.size()
            );
    glBindVertexArray(0);
}