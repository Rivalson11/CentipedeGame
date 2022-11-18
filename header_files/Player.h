#ifndef PLAYERCHARACTER
#define PLAYERCHARACTER
/** \file Player.h
    \brief Contains code for constructing the Player object
    The Player object is the user controlled Player.
    The Player can move and shoot based on user-input.
 */
#include <SFML/Graphics.hpp>
/** \class Player
    \brief Contains code for constructing the Player object
    The Player object is the user controlled Player.
    The Player can move and shoot based on user-input.
    The Player can lose and gain lives.
    When the Player shoots and destroys all the Centipede segments then the user wins.
    When the Player collides with either a Centipede or a Spider the player loses a life, and when 0, loses the game.
 */
    class Player
    {
        private:
            int lives;
            float PlayerSpeed; //variable player speed from construction
            sf::Vector2f PlayerSize; //Player sizes is not constant and changes based on player movement
            sf::RectangleShape PlayerRect;

        public:
            //Constructor

            /** \brief Player object construction
            \return Player object created
            */

            Player(float _gameWidth, float _gameHeight, sf::Vector2f _PlayerSize, float PlayerSpeed);

            //Accessors

            /** \brief Accessor for Player object position
            \return Player object coords
            */

            sf::Vector2f getCoords();

            /** \brief Accessor for Player object rect
            \return Player object SFML rect
            */

            sf::RectangleShape getPlayerRect();

            /** \brief Accessor for Player object remaining lives
            \return Player object lives
            */

            int getLives();

            //Mutators

            /** \brief Mutator for Player object move right
            \return Player object position change
            */

            void MoveRight();

            /** \brief Mutator for Player object move left
            \return Player object position change
            */

            void MoveLeft();

            /** \brief Mutator for Player object move up
            \return Player object position change
            */

            void MoveUp();

            /** \brief Mutator for Player object move down
            \return Player object position change
            */

            void MoveDown();

            /** \brief Mutator for Player object set position
            \return set Player object position
            */

            void resetPlayerPosition(float _gameWidth, float _gameHeight);//resets starting point for new game

            /** \brief Mutator for Player object set size
            \return set Player object size
            */

            void setPlayerSize(sf::Vector2f newPlayerSize);//changes hitboxes based of movement and actions

             /** \brief Mutator for Player object set lives
            \return set Player object lives
            */

            void setLives(int newlives);

    };


#endif


