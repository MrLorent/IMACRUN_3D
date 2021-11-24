#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include "Mesh.hpp"
#include "Model.hpp"

void Model::draw(
    glm::mat4 &ProjMatrix,
    glm::mat4 &MVMatrix,
    glm::mat4 &NormalMatrix)
{
    // Link the shaders of the model
    _shaders.use();
    glUniformMatrix4fv(_uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(_uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix));
    glUniformMatrix4fv(_uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

    // Draw all the meshes that compose the model
    for(unsigned int i = 0; i < _meshes.size(); i++)
    {
        _meshes[i].draw(_shaders);
    }
}

void Model::loadModel(
    const glimac::FilePath appPath,
    const std::string fileName
)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
 
    //Chargement du model 3D
    std::string inputfile = "./assets/models/"+fileName;
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials; 
    
    std::string warn;
    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str(), nullptr);
    
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

                vertices.push_back(newVertex);
            }
            index_offset += fv;
        }
    }

    // CHARGEMENT DES TEXTURES
    Texture tex(1);
    tex.load(appPath, "alliance.png");
    textures.push_back(tex);

    _meshes.push_back(Mesh(vertices, indices, textures));
}

void Model::linkMatrix()
{
    _uMVPMatrix = glGetUniformLocation(_shaders.getGLId(), "uMVPMatrix");
    _uMVMatrix = glGetUniformLocation(_shaders.getGLId(), "uMVMatrix"); 
    _uNormalMatrix = glGetUniformLocation(_shaders.getGLId(), "uNormalMatrix");
    _uTexture = glGetUniformLocation(_shaders.getGLId(), "uTexture");
}