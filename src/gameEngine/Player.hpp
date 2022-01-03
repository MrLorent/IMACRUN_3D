#pragma once
#define PLAYER_HPP

#include <iostream>
#include "glm/glm.hpp"

class Player
{
    private:
        glm::vec3 _position;
        unsigned int _score;

        unsigned int _jumpingIndex;
        unsigned int _jumpingTiming;
        unsigned int _crouchingIndex;
        unsigned int _crouchingTiming;
    public:
        // CONSTANTS
        static constexpr int LEFT = -1;
        static constexpr int MIDDLE = 0;
        static constexpr int RIGHT = 1;

        bool _isJumping;
        bool _isCrouching;

        // CONSTRUCTORS

            //! Constructor
            /*!
            *\ Constructor by default 
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
            *\ Destructor by default 
            */ 
        ~Player(){};

        // GETTER

            //! Getter
            /*!
            *\fn getPosition() const;
            * \return A vector 3 containing the position of the player
            */ 
        glm::vec3 getPosition() const;

            //! Getter
            /*!
            *\fn getScore()const;
            *\return the player's score
            */ 
        unsigned int getScore()const;

        // SETTER

            //! Setter
            /*!
            *\fn setPosition(const glm::vec3 newPosition);
            *\param newPosition : The new position of the player
            */ 
        void setPosition(const glm::vec3 newPosition);

            //! Setter
            /*!
            *\fn setScore(const int score);
            *\param score : The new score of the player
            */ 
        void setScore(const int score);

            //! Setter
            /*!
            *\fn goLeft();
            *\ Permit to turn left
            */ 
        void goLeft();

            //! Setter
            /*!
            *\fn goRight();
            *\ Permit to turn right
            */ 
        void goRight();

        // METHODS

            //! Method
            /*!
            *\fn jump();
            *\ Permit to jump
            */ 
        void jump();

            //! Method
            /*!
            *\fn crouch();
            *\ Permit to crouch
            */ 
        void crouch();

            //! Method
            /*!
            *\fn upScore();
            *\ Up the score of the player
            */ 
        void upScore();
};
