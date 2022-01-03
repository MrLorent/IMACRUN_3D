#pragma once
#define MAP_RENDERER_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.hpp"
#include "Game.hpp"
#include "Text2D.hpp"

class GameRenderer
{
    private:
        // PRIVATE ATTRIBUTS
        /* Window parameters */
        int _WINDOW_WIDTH;
        int _WINDOW_HEIGHT;
        glm::mat4 _PROJECTION_MATRIX;
        glm::mat4 _TEXT_PROJECTION_MATRIX;

        glimac::FilePath _applicationPath;
        unsigned int _renderingLength;
        short int _rotationDirection;
        Text2D _text;


        std::deque<glm::vec3> _currentLights;

        /* 3D Models */
        Model _player3DModel;
        Model _wall3DModel;
        Model _floor3DModel;
        Model _barrel3DModel;
        Model _light3DModel;
        Model _bottle3DModel;
        Model _skybox3DModel;
        Model _arch3DModel;
        Model _plank3DModel;

        // PRIVATE METHODS

        //! Method
        /*!
        *\fn void load3DModels()
        *\ Method that load every model the application needs.
        */
        void load3DModels();

        //! Method
        /*!
        *\fn void drawMap(Game& game, glm::mat4& VMatrix)
        *\param game : the current game.
        *\param VMatrix : the view Matrix
        *\ Method that draw the map.
        */
        void drawMap(Game& game, glm::mat4& VMatrix);

        //! Method
        /*!
        *\fn void drawPlayer(Game& game,const Player& player, glm::mat4& VMatrix)
        *\param game : the current game.
        *\param player : the current player.
        *\param VMatrix : the view Matrix.
        *\ Method that draw the character at the right place.
        */
        void drawPlayer(Game& game,const Player& player, glm::mat4& VMatrix);

        //! Method
        /*!
        *\fn void drawSkyBox(glm::mat4& VMatrix, glm::mat4& MMatrix)
        *\param VMatrix : the view matrix.
        *\param MMatrix : the model matrix.
        *\Method that draw the skybox at the right place.
        */
        void drawSkyBox(glm::mat4& VMatrix, glm::mat4& MMatrix);

        //! Method
        /*!
        *\fn void setLights(const glm::mat4& MMatrix,std::vector<glm::vec3>& firstLights, std::deque<glm::vec3>& lights, const unsigned short  int rank)
        *\param MMatrix : MMatrix of the light_marker placed 5 case before the actual light.
        *\param firstLights : first lights contained in the map
        *\param light : two actual pontual lights position
        *\param rank : 0 if the light is on the left, else it's on the right
        *\Method that .
        */
        void setLights(const glm::mat4& MMatrix,std::vector<glm::vec3>& firstLights, const unsigned short  int rank);

        //! Method
        /*!
        *\fn void drawWall(glm::mat4 &projMatrix, glm::mat4 &VMatrix, const glm::mat4 &MMatrix, std::deque<glm::vec3> &_currentLights);
        *\param projMatrix : the projection matrix
        *\param VMatrix : the view matrix.
        *\param MMatrix : the model matrix.
        *\Method that draw the wall at the right place.
        */
        void drawWall(glm::mat4 &projMatrix,
        glm::mat4 &VMatrix,
        const glm::mat4 &MMatrix,
        std::deque<glm::vec3> &_currentLights);

        //! Method
        /*!
        *\fn void drawBarel(glm::mat4 &projMatrix, glm::mat4 &VMatrix, const glm::mat4 &MMatrix, std::deque<glm::vec3> &_currentLights);
        *\param projMatrix : the projection matrix
        *\param VMatrix : the view matrix.
        *\param MMatrix : the model matrix.
        *\Method that draw the Barel at the right place.
        */
        void drawBarel(glm::mat4 &projMatrix,
        glm::mat4 &VMatrix,
        const glm::mat4 &MMatrix,
        std::deque<glm::vec3> &_currentLights);

        //! Method
        /*!
        *\fn void drawWall(glm::mat4 &projMatrix, glm::mat4 &VMatrix, const glm::mat4 &MMatrix, std::deque<glm::vec3> &_currentLights);
        *\param projMatrix : the projection matrix
        *\param VMatrix : the view matrix.
        *\param MMatrix : the model matrix.
        *\Method that draw the lantern at the right place.
        */
        void drawLantern(glm::mat4 &projMatrix,
        glm::mat4 &VMatrix,
        const glm::mat4 &MMatrix,
        std::deque<glm::vec3> &_currentLights);

        //! Method
        /*!
        *\fn void drawBottle(glm::mat4 &projMatrix, glm::mat4 &VMatrix, const glm::mat4 &MMatrix, std::deque<glm::vec3> &_currentLights);
        *\param projMatrix : the projection matrix
        *\param VMatrix : the view matrix.
        *\param MMatrix : the model matrix.
        *\Method that draw the bottle at the right place.
        */
        void drawBottle(glm::mat4 &projMatrix,
        glm::mat4 &VMatrix,
        const glm::mat4 &MMatrix,
        std::deque<glm::vec3> &_currentLights);

        //! Method
        /*!
        *\fn void drawArch(glm::mat4 &projMatrix, glm::mat4 &VMatrix, const glm::mat4 &MMatrix, std::deque<glm::vec3> &_currentLights);
        *\param projMatrix : the projection matrix
        *\param VMatrix : the view matrix.
        *\param MMatrix : the model matrix.
        *\Method that draw the arch at the right place.
        */
        void drawArch(glm::mat4 &projMatrix,
        glm::mat4 &VMatrix,
        const glm::mat4 &MMatrix,
        std::deque<glm::vec3> &_currentLights);

        //! Method
        /*!
        *\fn void drawPlank(glm::mat4 &projMatrix, glm::mat4 &VMatrix, const glm::mat4 &MMatrix, std::deque<glm::vec3> &_currentLights);
        *\param projMatrix : the projection matrix
        *\param VMatrix : the view matrix.
        *\param MMatrix : the model matrix.
        *\Method that draw the plank at the right place.
        */
        void drawPlank(glm::mat4 &projMatrix,
        glm::mat4 &VMatrix,
        const glm::mat4 &MMatrix,
        std::deque<glm::vec3> &_currentLights);


    public:
        // OPERATORS
        /* Move assignment operator */

        //! Move assignement operator
        GameRenderer& operator=(GameRenderer&& rhs) noexcept;

        /* Copy assignment operator */
        
        //! Copy assignement operator
        GameRenderer& operator=(const GameRenderer&) = delete; // We disable copying
        
        // CONSTRUCTORS
        
        //! Constructor
        /*!
        * Constructor by default
        */
        GameRenderer(){}

        //! Constructor
        /*!
        *\GameRenderer(glimac::FilePath applicationPath);
        *\param : applicationPath : absolute path to the application 
        */
        GameRenderer(glimac::FilePath applicationPath);

        /* copy constructor */
        
        //! Constructor
        /*!
        *   Copy constructor
        */
        GameRenderer(const GameRenderer&) = delete; // We disable copying

        /* move constructor */
        //! Constructor
        /*!
        *   Move constructor
        */
        GameRenderer(GameRenderer&& rhs) noexcept;

        // DESTRUCTOR
        
        //! Destructor
        /*!
        *   Destructor by default.
        */
        ~GameRenderer(){}

        // METHODS
        //! Method
        /*!
        *\fn void render(Game& game)
        *\param game : the current game
        * Method that render all the game elements.
        */
        void render(
            Game& game
        );

        /* Window parameters */
        
        //! Method
        /*!
        *\fn void setWindowParameters( const unsigned width, const unsigned height, glm::mat4& projection);
        *\param width : the width of the window
        *\param height : the height of the window
        *\param projection : reference to a projection matrix matrix
        *   Method that set all the window parameter in gameRenderer.
        */
        void setWindowParameters(
            const unsigned width,
            const unsigned height,
            glm::mat4& projection
        );

};
