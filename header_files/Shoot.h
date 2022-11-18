#ifndef SHOOT_H
#define SHOOT_H
/** \file Shoot.h
    \brief Contains code for constructing the Shoot object
    The Shoot object is a user controlled creation.
    The Shoot object moves up until collision occurs.
 */
#include <SFML/Graphics.hpp>
/** \class Shoot
    \brief Contains code for constructing the Shoot object
    The Shoot object is a user controlled creation.
    The Shoot object moves up until collision occurs.
    The shoot mechanic has a reload time stopping continuous firing.
    When the shoot object collides with the wall, Centipede segment, Spider, Flea, Mushroom, or DDT bomb the shoot object gets erased
 */
class Shoot
{
    private:

        //Shoot
        float ShootSpeed;
        sf::RectangleShape ShootRect;

    public:

        //Constructor

        /** \brief Shoot object construction
            \return Shoot object created
        */

        Shoot(sf::Vector2f Position, sf::Vector2f ShootSize, float _ShootSpeed);

        //Accessors

        /** \brief Shoot object Accessor for position
            \return Shoot object coords
        */

        sf::Vector2f getCoords();

        /** \brief Shoot object Accessor for rect
            \return Shoot object SFML rect
        */

        sf::RectangleShape getShootRect();

        //Mutators

        /** \brief Shoot object Mutator for movement
            \return Shoot object position change
        */

        void Move();

        /** \brief Shoot object Mutator for position
            \return Shoot object position change
        */

        void resetShootPosition(sf::Vector2f Position);//resets starting point for new shot

        /** \brief Shoot object destruction
            \return
        */

        virtual ~Shoot();

};

#endif // SHOOT_H
