#ifndef MUSHROOM_H
#define MUSHROOM_H
/** \file Mushroom.h
    \brief Contains code for constructing the Mushroom object
    The Mushroom object gets placed in a vector of MushroomField.
 */
#include <SFML/Graphics.hpp>
/** \class Mushroom
    \brief Contains code for constructing the Mushroom object
    The Mushroom object gets placed in a vector of MushroomField.
    The Mushroom has health that needs to reach 0 before being destroyed - 4 shot collisions needed.
 */
class Mushroom
{

    private:
        sf::RectangleShape MushroomRect;
        int health;

    public:
        //Constructor and Destructor

         /** \brief Mushroom object constructor
            \return mushroom object
        */

        Mushroom(sf::Vector2f MushroomSize, int posX, int posY);

        /** \brief Mushroom object destructor
            \return
        */

        virtual ~Mushroom();

        //Accessors

        /** \brief Accessor for Mushroom rect
            \return get SFML rect
        */

        sf::RectangleShape getMushroomRect();

        /** \brief Accessor for Mushroom position
            \return get coords
        */

        sf::Vector2f getCoords();

        /** \brief Accessor for Mushroom health
            \return get health
        */

        int getMushroomHealth();

        //Mutators

        /** \brief Mutator for Mushroom health
            \return set health
        */

        void setMushroomHealth();

};

#endif // MUSHROOM_H
