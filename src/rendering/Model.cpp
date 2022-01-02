#define TINYOBJLOADER_IMPLEMENTATION
#include "Model.hpp"

// OPERATORS
/* Move assignment operator */

Model& Model::operator=(Model&& rhs) noexcept
{
    _meshes         = std::move(rhs._meshes);
    _shaders        = std::move(rhs._shaders);
    
    // MATRICES
    _uMMatrix       = rhs._uMMatrix;
    _uVMatrix       = rhs._uVMatrix;
    _uMVPMatrix     = rhs._uMVPMatrix;
    _uNormalMatrix  = rhs._uNormalMatrix;
    
    // LIGTHS
    _uLightPos1     = rhs._uLightPos1;
    _uLightPos2     = rhs._uLightPos2;
}

// CONSTRUCTORS
/* basic constructeur */

Model::Model(ModelParams params)
    :_shaders(loadProgram(
        params.appPath.dirPath() + "src/shaders/"+params.vsShader,
        params.appPath.dirPath() + "src/shaders/"+params.fsShader
))
{
    /* Load the model and its textures */
    loadModel(params.appPath, params.fileName);
    
    /* Link the matrix attribut to the shaders matrix */
    _uMVPMatrix = glGetUniformLocation(_shaders.getGLId(), "uMVPMatrix");
    _uVMatrix = glGetUniformLocation(_shaders.getGLId(), "uVMatrix");
    _uNormalMatrix = glGetUniformLocation(_shaders.getGLId(), "uNormalMatrix");
    _uMMatrix = glGetUniformLocation(_shaders.getGLId(), "uMMatrix");

    // LIGHTS
    _uLightPos1 = glGetUniformLocation(_shaders.getGLId(), "uLightPos1");
    _uLightPos2 = glGetUniformLocation(_shaders.getGLId(), "uLightPos2");
}

void Model::draw(
    glm::mat4 &ProjMatrix,
    glm::mat4 &VMatrix,
    glm::mat4 const & MMatrix,
    std::deque<glm::vec3>& lights // Position of the lights in WordCoordinate
)
{
    /* Link the shaders of the model */
    _shaders.use();

    glUniform3fv(
        _uLightPos1,
        1,
        /* Compute the position of the first light in MVMatrix */
        glm::value_ptr(glm::vec3(VMatrix * glm::vec4(lights[0],1)))
    );

    glUniform3fv(
        _uLightPos2,
        1,
        /* Compute the position of the second light in MVMatrix */
        glm::value_ptr(glm::vec3(VMatrix * glm::vec4(lights[1],1)))
    );

   // MODEL MATRIX
    glUniformMatrix4fv(
        _uMMatrix,
        1,
        GL_FALSE,
        glm::value_ptr(MMatrix)
    );

    // VIEW MATRIX
    glUniformMatrix4fv(
        _uVMatrix,
        1,
        GL_FALSE,
        glm::value_ptr(VMatrix)
    );
    
    // MODEL VIEW PROJECTION MATRIX
    glUniformMatrix4fv(
        _uMVPMatrix,
        1,
        GL_FALSE,
        glm::value_ptr(ProjMatrix*VMatrix*MMatrix)
    );
    
    // NORMAL MATRIX
    glUniformMatrix4fv(
        _uNormalMatrix,
        1,
        GL_FALSE,
        glm::value_ptr(glm::transpose(glm::inverse(VMatrix*MMatrix))) // Normal Matrix = glm::transpose(glm::inverse(MVMatrix))
    );

    /* Draw all the meshes that compose the model */
    for(unsigned int i = 0; i < _meshes.size(); i++)
    {
        _meshes[i].draw(_shaders);
    }
}

/* move constructor */
        
Model::Model(Model&& rhs) noexcept
    :_meshes(std::move(rhs._meshes)),
     _shaders(std::move(rhs._shaders)),
     // MATRICES
     _uMMatrix(rhs._uMMatrix),
     _uVMatrix(rhs._uVMatrix),
     _uMVPMatrix(rhs._uMVPMatrix),
     _uNormalMatrix(rhs._uNormalMatrix),
     // LIGTHS
     _uLightPos1(rhs._uLightPos1),
     _uLightPos2(rhs._uLightPos2)
{
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
    Textures tmpTextures;
    std::unordered_map<Vertex, uint32_t> uniqueVertices;
 
    //Chargement du model 3D
    std::string inputfile = "./assets/models/"+filePath;
    tinyobj::ObjReaderConfig reader_config;
      #ifdef _WIN32
    const size_t lastSlashIndex = filePath.rfind('\\');
    #else
    const size_t lastSlashIndex = filePath.rfind('/');
    #endif
    std::string dirName;
    
    /* Get the path to the current file and the .obj file name */
    if (std::string::npos != lastSlashIndex)
    {
        dirName = filePath.substr(0, lastSlashIndex);
    }
     reader_config.mtl_search_path = "./assets/models/"+dirName; 
    //reader_config.mtl_search_path = "/Users/admin/Documents/Cours/A2/projet/IMACRUN_3D/assets/models/"+dirName;  // Path to material files

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
                vertex.position = glm::vec3(
                    tinyobj::real_t(attrib.vertices[3*idx.vertex_index+0]), // vx
                    tinyobj::real_t(attrib.vertices[3*idx.vertex_index+1]), // vy
                    tinyobj::real_t(attrib.vertices[3*idx.vertex_index+2])  // vz
                );

                // NORMAL
                if (idx.normal_index >= 0) {
                    vertex.normal = glm::vec3(
                        tinyobj::real_t(attrib.normals[3*idx.normal_index+0]),  // nx
                        tinyobj::real_t(attrib.normals[3*idx.normal_index+1]),  // ny
                        tinyobj::real_t(attrib.normals[3*idx.normal_index+2])   // nz
                    );
                }

                // TEXTURE_COORDINATES
                if (idx.texcoord_index >= 0)
                {
                    vertex.texCoords = glm::vec2(
                        tinyobj::real_t(attrib.texcoords[2*idx.texcoord_index+0]),  //tx
                        tinyobj::real_t(attrib.texcoords[2*idx.texcoord_index+1])   //ty
                    );
                }else{
                    vertex.texCoords = glm::vec2(0.f);
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
    loadTextures(appPath, filePath, tmpTextures, materials[0]);
    
    _meshes.push_back(std::move(Mesh(tmpVertices, tmpIndices, std::move(tmpTextures))));
}

void Model::loadTextures( 
    glimac::FilePath appPath,
    std::string filePath,
    Textures& textures,
    tinyobj::material_t material 
)
{
    #ifdef _WIN32
    const size_t lastSlashIndex = filePath.rfind('\\');
    #else
    const size_t lastSlashIndex = filePath.rfind('/');
    #endif
    std::string dirName;
    
    /* Get the path to the current file and the .obj file name */
    if (std::string::npos != lastSlashIndex)
    {
        dirName = filePath.substr(0, lastSlashIndex);
    }
                textures.diffuse=Texture("models/" + dirName +"/"+ material.diffuse_texname);
                textures.specular=Texture("models/" + dirName + "/"+ material.specular_texname);
                textures.shininess=material.shininess;
}