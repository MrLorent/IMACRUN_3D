#pragma once
#define MODEL_H

#include <deque>
#include <dirent.h>
#include <tiny_obj_loader.h>
#include "Mesh.hpp"
#include "FilePath.hpp"


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

    ModelParams(
        glimac::FilePath appPath
    ):appPath(appPath),
      fileName("unknown"),
      vsShader("unknown"),
      fsShader("unknown")
    {}
};

class Model
{
    private:
        // ATTRIBUTS

        std::vector<Mesh> _meshes;
        glimac::Program _shaders;

        GLint _uMMatrix;
        GLint _uMVPMatrix;
        //GLint _uMVMatrix;
        GLint _uVMatrix;
        GLint _uNormalMatrix;

        // LIGHTS
        GLint _uLightPos1;
        GLint _uLightPos2;
        GLint _uLightPos3;
        GLint _uLightPos4;
        
        // PRIVATE METHODS

        void loadModel(
            const glimac::FilePath appPath,
            const std::string& fileName
        );

        void loadTextures(
            glimac::FilePath appPath,
            std::string filePath,
            Textures& textures,
            tinyobj::material_t material
        );

    public:
        // CONSTRUCTORS
        /* basic constructors */
        
        Model(){};
        Model(ModelParams params);

        // METHODS
        
        void draw(
            glm::mat4 &ProjMatrix,
            glm::mat4 &MVMatrix,
            glm::mat4 const & MMatrix,
            std::deque<glm::vec3>& lights
        );

        static glm::mat4 MMatrixLight;
};