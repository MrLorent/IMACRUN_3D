#pragma once
#define MODEL_H

#include <dirent.h>
#include "Mesh.hpp"

struct ModelParams
{
    glimac::FilePath appPath;
    std::string fileName;
    std::string vsShader;
    std::string fsShader;

    // CONSTRUCTOR
    ModelParams(
        glimac::FilePath appPath,
        std::string fileName,
        std::string vsShader,
        std::string fsShader
    ):
    appPath(appPath),
    fileName(fileName),
    vsShader(vsShader),
    fsShader(fsShader) 
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
        
        // PRIVATE METHODS

        void loadModel(
            const glimac::FilePath appPath,
            const std::string& fileName
        );

        void linkMatrix();

        void loadTextures(
            glimac::FilePath appPath,
            std::string filePath,
            std::vector<Texture>& textures
        );

    public:
        // CONSTRUCTORS
        /* basic constructors */
        
        Model(){};
        Model(ModelParams params);

        // METHODS
        
        void draw(
            glm::mat4 &ProjMatrix,
            glm::mat4 &MVMatrix
        );
};