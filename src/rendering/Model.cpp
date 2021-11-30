#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include "Model.hpp"

// CONSTRUCTORS
/* basic constructeur */

Model::Model(ModelParams params)
    :_shaders(loadProgram(
        params._appPath.dirPath() + "src/shaders/"+params._vsShader,
        params._appPath.dirPath() + "src/shaders/"+params._fsShader
))
{
    /* Load the model and its textures */
    loadModel(params._appPath, params._fileName);
    
    /* Link the matrix attribut to the shaders matrix */
    _uMVPMatrix = glGetUniformLocation(_shaders.getGLId(), "uMVPMatrix");
    _uMVMatrix = glGetUniformLocation(_shaders.getGLId(), "uMVMatrix"); 
    _uNormalMatrix = glGetUniformLocation(_shaders.getGLId(), "uNormalMatrix");
}

void Model::draw(
    glm::mat4 &ProjMatrix,
    glm::mat4 &MVMatrix)
{
    /* Link the shaders of the model */
    _shaders.use();
    
    // MV MATRIX
    glUniformMatrix4fv(
        _uMVMatrix,
        1,
        GL_FALSE,
        glm::value_ptr(MVMatrix)
    );
    
    // MVPMATRIX
    glUniformMatrix4fv(
        _uMVPMatrix,
        1,
        GL_FALSE,
        glm::value_ptr(ProjMatrix*MVMatrix)
    );
    
    // NORMAL MATRIX
    glUniformMatrix4fv(
        _uNormalMatrix,
        1,
        GL_FALSE,
        glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))) // Normal Matrix = glm::transpose(glm::inverse(MVMatrix))
    );

    /* Draw all the meshes that compose the model */
    for(unsigned int i = 0; i < _meshes.size(); i++)
    {
        _meshes[i].draw(_shaders);
    }
}

// PRIVATE METHODS

void Model::loadModel(
    const glimac::FilePath appPath,
    const std::string& filePath
)
{
    // VARIABLES TEMPORAIRES
    std::vector<Vertex> tmpVertices;
    std::vector<unsigned int> tmpIndices;
    std::vector<Texture> tmpTextures;
    std::unordered_map<Vertex, uint32_t> uniqueVertices;
 
    //Chargement du model 3D
    std::string inputfile = "./assets/models/"+filePath;
    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = "./assets/textures/"; // Path to material files

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(inputfile, reader_config))
    {
        if (!reader.Error().empty())
        {
            std::cerr << "TinyObjReader: " << reader.Error();
        }
        exit(1);
    }

    if (!reader.Warning().empty())
    {
        std::cout << "TinyObjReader: " << reader.Warning();
    }

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();
    auto& materials = reader.GetMaterials();

    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
        {
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++)
            {
                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                Vertex vertex;

                // POSITION
                vertex._position = glm::vec3(
                    tinyobj::real_t(attrib.vertices[3*idx.vertex_index+0]), // vx
                    tinyobj::real_t(attrib.vertices[3*idx.vertex_index+1]), // vy
                    tinyobj::real_t(attrib.vertices[3*idx.vertex_index+2])  // vz
                );

                // NORMAL
                vertex._normal = glm::vec3(
                    tinyobj::real_t(attrib.normals[3*idx.normal_index+0]),  // nx
                    tinyobj::real_t(attrib.normals[3*idx.normal_index+1]),  // ny
                    tinyobj::real_t(attrib.normals[3*idx.normal_index+2])   // nz
                );

                // TEXTURE_COORDINATES
                if (idx.texcoord_index >= 0)
                {
                    vertex._texCoords = glm::vec2(
                        tinyobj::real_t(attrib.texcoords[2*idx.texcoord_index+0]),  //tx
                        tinyobj::real_t(attrib.texcoords[2*idx.texcoord_index+1])   //ty
                    );
                }else{
                    vertex._texCoords = glm::vec2(0.f);
                }

                // Optional: vertex colors
                // tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
                // tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
                // tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];

                if(uniqueVertices.count(vertex) == 0)
                {
                    uniqueVertices[vertex] = static_cast<uint32_t>(tmpVertices.size());
                    tmpVertices.push_back(vertex);
                }

                tmpIndices.push_back(uniqueVertices[vertex]);
            }
            index_offset += fv;

            // per-face material
            shapes[s].mesh.material_ids[f];
        }
    }

    // CHARGEMENT DES TEXTURES
    loadTextures(appPath, filePath, tmpTextures);
    
    _meshes.push_back(std::move(Mesh(tmpVertices, tmpIndices, std::move(tmpTextures))));
}

void Model::loadTextures(
    glimac::FilePath appPath,
    std::string filePath,
    std::vector<Texture>& textures
)
{
    #ifdef _WIN32
    const size_t lastSlashIndex = filePath.rfind('\\');
    #else
    const size_t lastSlashIndex = filePath.rfind('/');
    #endif
    std::string dirName;
    std::string objFile;
    
    /* Get the path to the current file and the .obj file name */
    if (std::string::npos != lastSlashIndex)
    {
        objFile = filePath.substr(lastSlashIndex+1);
        dirName = filePath.substr(0, lastSlashIndex);
    }

    DIR *dir;
    struct dirent *file;

    if ((dir = opendir (("./assets/models/" + dirName).c_str())) != nullptr) {
        /* print all the files and directories within directory */
        while ((file = readdir (dir)) != nullptr) {
            if(file->d_name != objFile)
            {
                textures.push_back(Texture(dirName + "/" + file->d_name));
            }
        }
        closedir (dir);
    }else{
        std::cout << "Error: fail to open " << dirName << " directory" << std::endl;
    }
}