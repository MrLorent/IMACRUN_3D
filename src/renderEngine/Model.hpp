#pragma once
#define MODEL_H

#include <deque>
#include <dirent.h>
#include <tiny_obj_loader.h>
#include "Mesh.hpp"
#include "FilePath.hpp"

//! The ModelParams structure contains the filePath of the app and 3 differents file names.
/*!
 * AppPath is the filePath of the app.  
 * FileName is a string name of the .obj file,
 * vsShader and fsShader are two string names of shaders files (.vs et .fs).
 */

struct ModelParams
{
    // PRIVATE ATTRIBUTS
    glimac::FilePath appPath;
    std::string fileName;
    std::string vsShader;
    std::string fsShader;

    // CONSTRUCTOR

    //! Constructor
    /*!
    *\fn ModelParams(const glimac::FilePath appPath, const std::string fileName, const std::string vsShader, const std::string fsShader)
    *\param appPath : path of the app
    *\param fileName : name of the .obj file
    *\param vsShader : name of the .vs file
    *\param fsShader : name of the .fs file
    */
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

    //! Constructor
    /*! 
    * \fn ModelParams(glimac::FilePath &appPath)
    *   Constructor 
    */
    ModelParams(
        glimac::FilePath &appPath
    ):appPath(appPath),
      fileName("unknown"),
      vsShader("unknown"),
      fsShader("unknown")
    {}
};


//! The Model class can get gether all of meshes to display. It contains meshes, shaders and 6 GLuint attributs.
/*!
 *  _meshes is a std::vector of meshes.
 *  _shaders correspond to the program shaders.
 *  _uMMatrix is a GLint corresponding to the uniform variable uMMatrix of the Model' shaders 
 *  _uVMatrix is a GLint corresponding to the uniform variable uVMatrix of the Model' shaders
 *  _uMVPMatrix is a GLint corresponding to the uniform variable uMVPMatrix of the Model' shaders
 *  _uNormalMatrix is a GLint corresponding to the uniform variable uNormalMatrix of the Model' shaders
 *  _uLightPos1 is a GLint corresponding to the uniform variable uLightPos1 of the Model' shaders
 *  _uLightPos2 is a GLint corresponding to the uniform variable uLightPos2 of the Model' shaders
 */ 

class Model
{
    private:
        // PRIVATE ATTRIBUTS

        std::vector<Mesh> _meshes;
        glimac::Program _shaders;

        /* Shader's uniform globals */
        GLint _uMMatrix;
        GLint _uVMatrix;
        GLint _uMVPMatrix;
        GLint _uNormalMatrix;

        // LIGHTS
        GLint _uLightPos1;
        GLint _uLightPos2;
        
        // PRIVATE METHODS

        //! Method
        /*!
        *\fn void loadModel(const glimac::FilePath appPath, const std::string& fileName)
        * Method that loads the Model thanks to the appPath and the fileName .obj.
        */
        void loadModel(
            glimac::FilePath& appPath,
            std::string& fileName
        );

        //! Method
        /*!
        *\fn void loadModel(loadTextures(glimac::FilePath appPath,std::string filePath, Textures& textures,tinyobj::material_t material)
        * Method that loads all of the textures the model will need to be displayed.s
        */
        void loadTextures(
            glimac::FilePath& appPath,
            std::string& filePath,
            Textures& textures,
            tinyobj::material_t material
        );

    public:
        // OPERATORS

        //! Move assignment operator
        Model& operator=(Model&& rhs) noexcept;

        //! Copy assignment operator
        Model& operator=(const Model&) = delete; // We disable copying

        // CONSTRUCTORS
        /* basic constructors */
        
        //! Constructor
        /*! 
         *  Constructor by default
         */
        Model(){}

        //! Constructor
        /*!
        *\fn Model(ModelParams params)
        *\param params : all of ModelParams attributes
        */
        Model(ModelParams params);

        //! Copy constructor
        Model(const Model&) = delete; // We disable copying

        //! Move constructor
        Model(Model&& rhs) noexcept;

        //! Destructor
        /*! 
         *  Destructor by default
         */
        ~Model(){}

        // METHODS
        
        //! Method
        /*!
        *\fn void draw(const glm::mat4& ProjMatrix, const glm::mat4& MVMatrix, const glm::mat4& MMatrix, const std::deque<glm::vec3>& lights)
        * Method that draws the model in its 3 dimensions position and with lights on it
        */
        void draw(
            const glm::mat4& ProjMatrix,
            const glm::mat4& MVMatrix,
            const glm::mat4& MMatrix,
            const std::deque<glm::vec3>& lights
        );
};