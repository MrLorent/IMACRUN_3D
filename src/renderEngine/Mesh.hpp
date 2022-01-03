#pragma once
#define MESH_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

#include "Program.hpp"
#include "Texture.hpp"

//! The Textures structure contains 2 different textures and a shininess value.
/*!
 *  The two textures correspond to a diffuse and a specular one.
 *  The float shininess defines a shininess level.
 */

struct Textures{
    Texture diffuse;
    Texture specular;
    float shininess; 

    Textures():shininess(0){};
};

//! The Vertex structure contains a position, a normal and texture coords.
/*!
 *  position is a 3 dimensions vector with x, y and z value.
 *  normal is also a 3 dimensions vector with x, y and z value.
 *  texCoords is a 2 dimensions vector with x and y value.
 */

struct Vertex{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;

    // OPERATORS

    //! Boolean operator
    /*! 
    *\Surcharg of operator == for a vertex
    */
    bool operator==(const Vertex& other) const {
        return position == other.position && normal == other.normal && texCoords == other.texCoords;
    }

    // CONSTRUCTOR

    //! Constructor
    /*! 
    *   Constructor by default
    */
    Vertex(){}

    //! Constructor
    /*!
    *\fn Vertex(const glm::vec3 p, const glm::vec3 n, const glm::vec2 t)
    *\param p : position of vertex
    *\param n : normal vector of the vextex plan
    *\param t : textCoords vector of the texture 2D
    */
    Vertex(const glm::vec3 p, const glm::vec3 n, const glm::vec2 t)
        :position(p), normal(n), texCoords(t)
    {}
};

//! Method
/*!
*\fn size_t operator()(Vertex const& vertex) const
* Method that hashes a vertex structure to arrange them in in a hash list
*/
namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.position) ^
                   (hash<glm::vec3>()(vertex.normal) << 1)) >> 1) ^
                   (hash<glm::vec2>()(vertex.texCoords) << 1);
        }
    };
}

//! The Mesh class contains 3 GLuint attributs, a vector vertices, a vector of indices and a instance of Testures structure
/*!
 *  vertices is a vector of vertex.
 *  indices is a vector of unsigned int.
 *  textures is a textures struct to display.
 */

class Mesh
{
    private:
        // PRIVATE ATTRIBUTS
        
        GLuint _vao;
        GLuint _vbo;
        GLuint _ibo;

        // PRIVATE METHODS

        //! Method
        /*!
        *\fn void initVbo()
        * Method that initialises the Vbo
        */
        void initVbo();

        //! Method
        /*!
        *\fn void initIbo()
        * Method that initialises the Ibo
        */
        void initIbo();

        //! Method
        /*!
        *\fn void initVao()
        * Method that initialises the Vao
        */
        void initVao();

        //! Method
        /*!
        *\fn void bindTexture(const int index,const GLint textureId, const char* uniformName, const GLuint shadersId) const
        * Method that binds the texture in shaders
        */
        void bindTexture(const int index,const GLint textureId, const char* uniformName, const GLuint shadersId) const;
    
    public:
        // PUBLIC ATTRIBUTS
        
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        Textures textures;

        // OPERATORS

        //! Move assignment operator
        Mesh& operator=(Mesh&& rhs) noexcept;

        //! Copy assignment operator
        Mesh& operator=(const Mesh&) = delete; // We disable copying

        // CONSTRUCTORS
        /* basic constructor */
        
        //! Constructor
        /*! 
         *  Constructor by default
         */
        Mesh();

        //! Constructor
        /*!
        *\fn Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, Textures&& textures)
        *\param vertices : vector of all vertex
        *\param indices : vector of all indices
        *\param textures : Textures of texture to display
        */
        Mesh(
            const std::vector<Vertex>& vertices,
            const std::vector<unsigned int>& indices,
            Textures&& textures
        );

        //! Copy constructor
        Mesh(const Mesh&) = delete; // We disable copying

        //! Move constructor
        Mesh(Mesh&& rhs) noexcept;

        //! Destructor
        /*! 
         *  Destructor by default
         */
        ~Mesh();

        // METHODS
        
        //! Method
        /*!
        *\fn void draw(glimac::Program& shaders)
        * Method that draws the mesh thanks to shaders 
        */
        void draw(glimac::Program& shaders);

};