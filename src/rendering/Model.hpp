#pragma once
#define MODEL_H

#include "vector"
#include "string"
#include "glm.hpp"

#include "FilePath.hpp"
#include "Program.hpp"

#include "Mesh.hpp"

struct ModelParams
{
    glimac::FilePath _appPath;
    std::string _fileName;
    std::string _vsShader;
    std::string _fsShader;

    // CONSTRUCTOR
    ModelParams(
        glimac::FilePath appPath,
        std::string fileName,
        std::string vsShader,
        std::string fsShader
    ):
    _appPath(appPath),
    _fileName(fileName),
    _vsShader(vsShader),
    _fsShader(fsShader) 
    {}
};

class Model
{
    private:
        // ATTRIBUTS

        std::vector<Mesh> _meshes;
        glimac::Program _shaders;

        GLint _uMVPMatrix;
        GLint _uMVMatrix;
        GLint _uNormalMatrix;
        GLint _uTexture;
        
        // PRIVATE METHODS

        void loadModel(
            const glimac::FilePath appPath,
            const std::string fileName
        );

        void linkMatrix();

        std::vector<Texture> loadTextures();

    public:
        // CONSTRUCTORS
        /* basic constructors */
        
        Model(ModelParams params)
            :_shaders(loadProgram(
                params._appPath.dirPath() + "src/shaders/"+params._vsShader,
                params._appPath.dirPath() + "src/shaders/"+params._fsShader
        ))
        {
            loadModel(params._appPath, params._fileName);
            linkMatrix();
        }

        // METHODS
        
        void draw(
            glm::mat4 &ProjMatrix,
            glm::mat4 &MVMatrix,
            glm::mat4 &NormalMatrix
        );
};