#ifndef DDT_H
#define DDT_H
/** \file DDT.h
    \brief Contains code for constructing DDT bomb object on DDTField vector
    The DDT bomb randomly spawns on the screen with a limit of 4 bombs at a time.
    If shot, the DDT bomb explodes.
 */
#include <SFML/Graphics.hpp>
/** \class DDT
    \brief Contains code for constructing DDT bomb object on DDTField vector
    The DDT bomb randomly spawns on the screen with a limit of 4 bombs at a time.
    If shot, the DDT bomb explodes. When the DDT bomb explodes, all game objects within
    a range is destroyed.
 */
class DDT
{

    private:
        sf::RectangleShape DDTRect;
        bool isExploding;
        sf::Time ExplodedTime;

    public:
        //Constructor and Destructor

        /** \brief DDT object creation
            \return Centipede object
        */

        DDT(sf::Vector2f DDTSize, int posX, int posY);

        /** \brief DDT object deletion
            \return
        */

        virtual ~DDT();

        //Accessors

        /** \brief DDT object rectangle
            \return SFML rect
        */

        sf::RectangleShape getDDTRect();


        /** \brief DDT object position
            \return vector2f coords
        */

        sf::Vector2f getCoords();

        /** \brief Game mechanic time management
            \return current time elapsed
        */

        sf::Time getExplodedTime();

        /** \brief Function checker
            \return bool true if active
        */

        bool getIsExploding();


        //Mutators

        /** \brief DDT object size alter
            \return DDT rect size
        */

        void setDDTBlockSize(sf::Vector2f _DDTSize);

        /** \brief DDT function check
            \return set value for boolean
        */

        void setIsExploding();

        /** \brief DDT explode function timer
            \return timer
        */

        void setExplodedTime(sf::Time _ExplodedTime);
};

#endif // DDT_H
