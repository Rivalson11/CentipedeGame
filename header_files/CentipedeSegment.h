#ifndef CENTIPEDESEGMENT_H
#define CENTIPEDESEGMENT_H
/** \file CentipedeSegments.h
    \brief Contains code for constructing Centipede segment object within Centipede vector
    The Centipede moves right/left, until a collision shifts it down/up once, across the screen.
 */
#include <SFML/Graphics.hpp>

/** \class CentipedeSegment
    \brief Centipede moves right/left until collision with the wall or a mushroom then it shifts down.
    Creates a rectangle to be used as a base for a sprite.
    Game object with vertical and horizontal movement, spawning from a set coordinate.
    Collision with Player causes Lose Life.
    CentipedeSegment is the individual segment within a Centipede vector.
 */
class CentipedeSegment
{
    private:
        float CentipedeSpeed;
        sf::RectangleShape CentipedeRect;
        sf::Vector2f CentipedeSize;

        bool isHead = false;
        bool isCurrentDirectionRight;//true is right, false is left, set as bool to save memory
        bool isCurrentDirectionDown;//true is down, false is up
        bool isInPlayerArea;

        float gameWidth;

    public:
        //constructor and destructor

        /** \brief Centipede object creation
            \return Centipede object
        */

        CentipedeSegment(float _gameWidth, float _gameHeight, sf::Vector2f _CentipedeSize, int pos, float _CentipedeSpeed);

        /** \brief Centipede object deletion
            \return
        */

        virtual ~CentipedeSegment();

        //Accessors

         /** \brief Centipede object
            \return SFML rectangle
        */

        sf::RectangleShape getCentipedeRect();

        /** \brief Centipede position
            \return vector2f coords
        */

        sf::Vector2f getCentipedeRectCoords();

        /** \brief Centipede object type
            \return true if type head
        */

        bool getCurrentDirectionX();

        /** \brief Centipede object type
            \return true if type head
        */

        bool getIsHead();

        /** \brief Centipede get position
            \return true if in player area
        */

        bool getIsInPlayerArea();

        //Mutators

        /** \brief Centipede object type
            \return set centipede segment to head
        */

        void setHead();//Changes segment to a head if it is split;

        /** \brief Centipede movement
            \return movement direction up/down
        */

        void MoveY();//direction of vertical movement to flip when top or bottom boundary hit

        /** \brief Centipede movement
            \return movement direction right/left
        */

        void MoveX();

        /** \brief Centipede movement set
            \return movement direction up/down set
        */

        void setCurrentDirectionY(bool DirectionIsDown);

        /** \brief Centipede movement set
            \return movement direction right/left set
        */

        void setCurrentDirectionX();

        /** \brief Centipede position
            \return bool if in area
        */

        void setInPlayerArea();


};

#endif // CENTIPEDESEGMENT_H
