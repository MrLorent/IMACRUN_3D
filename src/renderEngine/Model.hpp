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
    glimac::FilePath appPath;
    std::string fileName;
    std::string vsShader;
    std::string fsShader;

    // CONSTRUCTOR

    //! Constructor
    /*!
    *\fn ModelParams(glimac::FilePath appPath, std::string fileName,std::string vsShader,std::string fsShader)
    *\param appPath : path of the app
    *\param fileName : name of the .obj file
    *\param vsShader : name of the .vs file
    *\param fsShader : name of the .fs file
    */
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

    //! Constructor
    /*! 
    *\ Constructor 
    */
    ModelParams(
        glimac::FilePath appPath
    ):appPath(appPath),
      fileName("unknown"),
      vsShader("unknown"),
      fsShader("unknown")
    {}
};


//! The Model class can get gether all of meshes to display. It contains meshes, shaders and 6 GLuint attributs.
/*!
 *  _meshes is a vector of meshes.
 *  _shaders correspond to the program shaders.
 *  _uMMatrix is matrix of ...
 *  _uVMatrix is matrix of ...
 *  _uMVPMatrix is matrix of ...
 *  _uNormalMatrix is matrix of ...
 *  _uLightPos1 is the ...
 *  _uLightPos2 is the ...
 */ 

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

        //! Method
        /*!
        *\fn void loadModel(const glimac::FilePath appPath, const std::string& fileName)
        * Method that loads the Model thanks to the appPath and the fileName .obj.
        */
        void loadModel(
            const glimac::FilePath appPath,
            const std::string& fileName
        );

        //! Method
        /*!
        *\fn void loadModel(loadTextures(glimac::FilePath appPath,std::string filePath, Textures& textures,tinyobj::material_t material)
        * Method that loads all of the textures the model will need to be displayed.s
        */
        void loadTextures(
            glimac::FilePath appPath,
            std::string filePath,
            Textures& textures,
            tinyobj::material_t material
        );

    public:
        // OPERATORS

        //! Move assignment operator
        /*! 
         *\First surcharg of operator =
         */
        Model& operator=(Model&& rhs) noexcept;

        //! Copy assignment operator
        /*! 
         *\Second surcharg of operator =
         */
        Model& operator=(const Model&) = delete; // We disable copying

        // CONSTRUCTORS
        /* basic constructors */
        
        //! Constructor
        /*! 
         *\Constructor by default
         */
        Model(){}

        //! Constructor
        /*!
        *\fn Model(ModelParams params)
        )
        *\param params : all of ModelParams attributes
        */
        Model(ModelParams params);

        //! Copy constructor
        /*! 
         *\ Copy constructor
         */
        Model(const Model&) = delete; // We disable copying

        //! Move constructor
        /*! 
         *\ Move constructor
         */
        Model(Model&& rhs) noexcept;

        //! Destructor
        /*! 
         *\Destructor by default
         */
        ~Model(){}

        // METHODS
        
        //! Method
        /*!
        *\fn void draw(glm::mat4 &ProjMatrix, glm::mat4 &MVMatrix, glm::mat4 const & MMatrix, std::deque<glm::vec3>& lights)
        * Method that draws the model in its 3 dimensions position and with lights on it
        */
        void draw(
            glm::mat4 &ProjMatrix,
            glm::mat4 &MVMatrix,
            glm::mat4 const & MMatrix,
            std::deque<glm::vec3>& lights
        );
};