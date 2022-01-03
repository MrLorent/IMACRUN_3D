#pragma once
#define PLAYER_HPP

#include <iostream>
#include "glm/glm.hpp"

class Player
{
    private:
        // PRIVATE ATTRIBUTS

        glm::vec3 _position;
        unsigned int _score;

        /* Jumping state parameters */
        unsigned int _jumpingIndex;
        unsigned int _jumpingTiming;

        /* Crouching state parameters */
        unsigned int _crouchingIndex;
        unsigned int _crouchingTiming;

    public:
        // CONSTANTS
        static constexpr int LEFT = -1;
        static constexpr int MIDDLE = 0;
        static constexpr int RIGHT = 1;

        // ATTRIBUTS
        bool _isJumping;
        bool _isCrouching;

        // CONSTRUCTORS

        //! Constructor
        /*!
        *   Constructor by default 
        */ 
        Player(){}

        //! Constructor
        /*!
        *\fn Player(const unsigned short int caseSubdivision);
        * \param caseSubdivisions : Number of steps needed for a map element to move one meter.
        */ 
        Player(const unsigned short int caseSubdivision);
        
        // DESTRUCTORS

        //! Destructor
        /*!
        *   Destructor by default 
        */ 
        ~Player(){};

        // GETTER

        //! Getter
        /*!
        *\fn glm::vec3 getPosition() const;
        * \return A vector 3 containing the position of the player
        */ 
        glm::vec3 getPosition() const;

        //! Getter
        /*!
        *\fn nsigned int getScore()const;
        *\return the player's score
        */ 
        unsigned int getScore()const;

        // SETTER

        //! Setter
        /*!
        *\fn void setPosition(const glm::vec3 newPosition);
        *\param newPosition : The new position of the player
        */ 
        void setPosition(const glm::vec3 newPosition);

        //! Setter
        /*!
        *\fn void setScore(const int score);
        *\param score : The new score of the player
        */ 
        void setScore(const int score);

        //! Setter
        /*!
        *\fn void goLeft();
        *\ move the player of one step on the left if he isn't allready on left side
        */ 
        void goLeft();

        //! Setter
        /*!
        *\fn goRight();
        *\ move the player of one step on the right if he isn't allready on left side
        */ 
        void goRight();

        // METHODS

        //! Method
        /*!
        *\fn jump();
        *\ Make the player to jump
        */ 
        void jump();

        //! Method
        /*!
        *\fn crouch();
        *\ Make the player crouch
        */ 
        void crouch();

        //! Method
        /*!
        *\fn upScore();
        *\ Increase the score of the player
        */ 
        void upScore();
};
