#ifndef DDTFIELD_H
#define DDTFIELD_H
/** \file DDTField.h
    \brief Contains code for constructing DDTField object with DDT bomb on it
    The DDT bomb randomly spawns on the screen with a limit of 4 bombs at a time.
    If shot, the DDT bomb explodes.
 */
#include "..\header_files\DDT.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <iostream>
/** \class DDTField
    \brief DDTField is a field across the screen where DDT bombs can be placed on.
    The DDTField controls the placement and generation of DDT game objects.
    These placements are randomly made.
 */
class DDTField
{
 private:
        std::vector<DDT> DDTObjects;//vector of all mushrooms

    public:
        //Constructor and destructor

        /** \brief DDT object constructor
            \return DDT object
        */

        DDTField();

        /** \brief DDT object destructor
            \return
        */

        virtual ~DDTField();

        //Accessors
        std::vector<DDT> getDDTField();

        /** \brief Accessor function DDT object rect retrival
            \return SFML rect
        */

        sf::RectangleShape getDDTBlock(int DDTNum);

        /** \brief Accessor function DDT object position
            \return coords
        */

        sf::Vector2f getRectCoords(int DDTNum);

        /** \brief Accessor function DDT object explode timer
            \return time since explosion activated
        */

        sf::Time getDDTExplodedTime(int DDTNum);

        /** \brief Accessor function DDT object explode bool
            \return true if activated
        */

        bool getDDTIsExploded(int DDTNum);

        //Mutators

        /** \brief Mutator function DDT object deletion
            \return delete object
        */

        void DestroyDDT(int DDTNum);

        /** \brief Mutator function DDT object position chances
            \return field positions
        */

        void ResetDDTField();

        /** \brief Mutator function DDT object creation
            \return DDT object creation
        */

        void SpawnDDT(float _gameWidth, float _PlayerCeiling, sf::Vector2f _DDTSize);

        /** \brief Mutator function DDT object function for explode
            \return creates DDT bomb
        */

        void setDDTExplosion(sf::Vector2f DDTExplosionRange, int _DDTNum, sf::Time _ExplodedTime);//sets explosion characteristics of ddt bomb

};
#endif // DDTFIELD_H
