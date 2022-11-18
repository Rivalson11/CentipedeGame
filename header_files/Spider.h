#ifndef SPIDER_H
#define SPIDER_H
/** \file Spider.h
    \brief Contains code for constructing the Spider object
    The Spider object appears periodically.
    The Spider object moves in a random zigzag fashion until collision occurs.
 */
#include <SFML/Graphics.hpp>
/** \class Spider
    \brief Contains code for constructing the Spider object
    The Spider object appears periodically.
    The Spider object moves in a random zigzag fashion until collision occurs.
    The Spider colliding with a Player causes the lose of a life.
 */
class Spider
{
        private:
            float SpiderSpeed;
            sf::RectangleShape SpiderRect;
            int CurrentDirection;

            void MoveRight();
            void MoveLeft();
            void MoveUp();
            void MoveDown();

        public:
            //Constructor

            /** \brief Spider object construction
            \return Spider object created
            */

            Spider(float _SpawnY, sf::Vector2f _SpiderSize, float _SpiderSpeed);

            /** \brief Spider object destruction
            \return
            */

            virtual~Spider();

            //Accessors

            /** \brief Spider object Accessor for position
            \return coords
            */

            sf::Vector2f getCoords();

            /** \brief Spider object Accessor for rect
            \return SFML rect
            */

            sf::RectangleShape getSpiderRect();

            /** \brief Spider object Accessor for movement direction currently
            \return variable of direction
            */

            int getCurrentDirection();

            //Mutators

            /** \brief Spider object Mutator for movement
            \return Spider object position change
            */

            void SpiderRandomMovement();

            /** \brief Spider object Mutator for movement direction
            \return Spider object movement setter
            */

            void setCurrentDirection(int MovementType);

};

#endif // SPIDER_H
