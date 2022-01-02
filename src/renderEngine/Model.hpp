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
        const glimac::FilePath &appPath,
        const std::string &fileName,
        const std::string &vsShader,
        const std::string &fsShader 
    ):
    appPath(appPath),
    fileName(fileName),
    vsShader(vsShader),
    fsShader(fsShader) 
    {}

    ModelParams(
        glimac::FilePath &appPath
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
        GLint _uVMatrix;
        GLint _uMVPMatrix;
        GLint _uNormalMatrix;

        // LIGHTS
        GLint _uLightPos1;
        GLint _uLightPos2;
        
        // PRIVATE METHODS

        void loadModel(
            glimac::FilePath& appPath,
            std::string& fileName
        );

        void loadTextures(
            glimac::FilePath& appPath,
            std::string& filePath,
            Textures& textures,
            tinyobj::material_t material
        );

    public:
        // OPERATORS
        /* Move assignment operator */

        Model& operator=(Model&& rhs) noexcept;

        /* Copy assignment operator */
        Model& operator=(const Model&) = delete; // We disable copying

        // CONSTRUCTORS
        /* basic constructors */
        
        Model(){}
        Model(ModelParams params);

        /* Copy constructor */

        Model(const Model&) = delete; // We disable copying

        /* move constructor */
        
        Model(Model&& rhs) noexcept;

        // DESTRUCTOR

        ~Model(){}

        // METHODS
        
        void draw(
            const glm::mat4 &ProjMatrix,
            const glm::mat4 &MVMatrix,
            const glm::mat4 & MMatrix,
            const std::deque<glm::vec3>& lights
        );
};