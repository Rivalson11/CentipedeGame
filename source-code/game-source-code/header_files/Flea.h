#ifndef FLEA_H
#define FLEA_H
/** \file Flea.h
    \brief Contains code for constructing a Flea object
    The Flea drops down vertically and disappears upon collision with the bottom of the screen.
 */
#include <SFML/Graphics.hpp>
/** \class Flea
    \brief Contains code for constructing a Flea object
    The Flea drops down vertically and disappears upon collision with the bottom of the screen.
    The Flea occasionally leaves a trail of newly spawned mushrooms in its path (when the mushroom count on the screen is low)
 */
class Flea
{
        private:
            sf::RectangleShape FleaRect;
            float FleaSpeed;

        public:
            //Constructor

            /** \brief Flea object constructor
            \return Flea object
            */

            Flea(float _SpawnX, sf::Vector2f _FleaSize, float _FleaSpeed);

            /** \brief Flea object destructor
            \return
            */

            virtual ~Flea();

            //Accessors

            /** \brief Accessor for Flea object position
            \return coords
            */

            sf::Vector2f getCoords();

            /** \brief Accessor for Flea object rect
            \return SFML rect
            */

            sf::RectangleShape getFleaRect();

            //Mutators

            /** \brief Mutator for Flea object move function
            \return Flea object position change
            */

            void MoveDown();

};

#endif // FLEA_H
