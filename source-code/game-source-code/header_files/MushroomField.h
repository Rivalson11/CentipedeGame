#ifndef MUSHROOMFIELD_H
#define MUSHROOMFIELD_H
/** \file MushroomField.h
    \brief Contains code for constructing the MushroomField object
    The MushroomField object holds all the Mushroom Objects.
 */
#include "..\header_files\Mushroom.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <iostream>
/** \class MushroomField
    \brief Contains code for constructing the MushroomField object
    The MushroomField object holds all the Mushroom Objects.
    The MushroomField controls the spawning of Mushroom on the field when the game starts.
    This placement of Mushrooms is random and gets effected by chance that gets altered based on the game difficulty selected.
 */
class MushroomField
{
 private:
        std::vector<Mushroom> MushroomObjects;//vector of all mushrooms

    public:
        //Constructor and destructor

        /** \brief Mushroom object field constructor
            \return mushroom field object
        */

        MushroomField(float _gameWidth, float _gameHeight, sf::Vector2f _centipedeSize, int MushroomSpawnChance);

        /** \brief Mushroom object field destructor
            \return
        */

        virtual ~MushroomField();

        //Accessors

        /** \brief Accessor for Mushroom object field
            \return get mushroom field object
        */

        std::vector<Mushroom> getMushroomField();

        /** \brief Accessor for Mushroom object block
            \return get mushroom rect
        */

        sf::RectangleShape getMushroomBlock(int MushroomNum);

        /** \brief Accessor for Mushroom object field position
            \return get mushroom object coords
        */

        sf::Vector2f getBlockCoords(int MushroomNum);

        /** \brief Accessor for Mushroom object field
            \return get mushroom object coords
        */

        sf::Vector2f getMushroomCoords(int MushroomNum);

        /** \brief Accessor for Mushroom object health
            \return get mushroom health
        */

        int getMushroomHealth(int MushroomNum);

        //Mutators

        /** \brief Mutator for Mushroom object create rect
            \return Mushroom object creation
        */

        void SpawnMushroom(sf::Vector2f SpawnPosition, bool currentDirectionRight, sf::Vector2f MushroomSize);//when body of centipede shot

        /** \brief Mutator for Mushroom object delete rect
            \return Mushroom object deletion
        */

        void DestroyMushroom(int MushroomNum);//when mushroom is destroyed

        /** \brief Mutator for Mushroom object set health
            \return set Mushroom object health
        */

        void setMushroomHealth(int MushroomNum);

         /** \brief Mutator for Mushroom object set field positions
            \return set Mushroom object field
        */

        void setMushroomField(float _gameWidth, float _gameHeight, sf::Vector2f _centipedeSize, int MushroomSpawnChance);

         /** \brief Mutator for Mushroom object delete entire field
            \return delete Mushroom object field
        */

        void ClearMushroomField();
};

#endif // MUSHROOMFIELD_H
