#pragma once
#define TEXTURE_H
#include <iostream>
#include <glad/glad.h>
#include "Image.hpp"

class Texture
{
    private:
        // ATTRIBUTS

        GLuint _id;
        std::string _type;

    public:
        // OPERATORS
        /* Move assignment operator */

        //! Move assignment operator
        Texture& operator=(Texture&& rhs) noexcept;

        /* Copy assignment operator */

        //! Copy assignment operator
        Texture& operator=(const Texture&) = delete; // We disable copying

        // CONSTRUCTORS
        /* basic constructor */
        
        //! Constructor
        /*!
        *   Constructor by default
        */ 
        Texture();

        //! Constructor
        /*!
        *\fn Texture(const std::string filePath);
        *\param filePath : Relative path from the asset file to the texture file
        */ 
        Texture(const std::string &filePath);
        
        /* Copy constructor */

        //! Copy constructor
        Texture(const Texture&) = delete; // We disable copying

        /* move constructor */

        //! Move Constructor  
        Texture(Texture&& rhs) noexcept;

        // DESTRUCTOR
        
        //! Destructor
        /*!
        *   Destructor by default
        */     
        ~Texture();
        
        // GETTER

        //! Getter
        /*!
        *\fn inline GLuint getId() const
        *\return the texture id 
        */    
        inline GLuint getId() const { return _id; }

        //! Getter
        /*!
        *\fn inline std::string getType() const
        *\return the type of the texture
        */    
        inline std::string getType() const {return _type;}

        // METHODS
        
        //! Method
        /*!
        *\fn bool load(const std::string& filePath)
        *\param filePath Relative path from the asset to the texture
        *\return true if the texture loading is successfull or false if the texture loading failed
        */ 
        bool load(const std::string& filePath);
    
};