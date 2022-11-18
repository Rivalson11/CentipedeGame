#ifndef CENTIPEDE_H
#define CENTIPEDE_H
/** \file Centipede.h
    \brief Contains code for constructing Centipede class hierarchy
    The Centipede moves towards the player from set position
 */
#include <SFML/Graphics.hpp>
#include <vector>
#include "../header_files/CentipedeSegment.h"
/** \class Centipede
    \brief Centipede moves right/left until collision with the wall or a mushroom then it shifts down.
    Creates a rectangle to be used as a base for a sprite.
    Game object with vertical and horizontal movement, spawning from a set coordinate.
    Collision with Player causes Lose Life.
 */
class Centipede
{
    private:
        std::vector<CentipedeSegment> CentipedeSegments;

    public:
        //constructor and destructor

        /** \brief Centipede object creation
            \return return centipede object
        */

        Centipede(float _gameWidth, float _gameHeight, sf::Vector2f _CentipedeSize, int NumSegments, float CentipedeSpeed);

        /** \brief Centipede object deletion
            \return
        */

        virtual ~Centipede();

        //Accessors

        /** \brief Centipede object retrival
            \return return vector
        */

        std::vector<CentipedeSegment> getCentipede();

        /** \brief Centipede object position
            \return SFML rectangle
        */

        sf::RectangleShape getSegmentRect(int SegmentNum);

        /** \brief Centipede object position
            \return Vector2f coords
        */

        sf::Vector2f getSegmentCoords(int SegmentNum);

        /** \brief Centipede segment direction check
            \return bool true if moving right
        */

        bool getSegmentCurrentDirectionX(int SegmentNum);

        /** \brief Centipede body type check
            \return bool true if head
        */

        bool getSegmentIsHead(int SegmentNum);

        /** \brief Centipede position check
            \return bool
        */

        bool getSegmentIsInPlayerArea(int SegmentNum);


        //Mutators

        /** \brief Centipede movement function
            \return Moves Centipede object up/down
        */

        void MoveY(int SegmentNum);

        /** \brief Centipede movement function
            \return Moves Centipede object right/left
        */

        void MoveX(int SegmentNum);

        /** \brief Collision check if Centipede and Shoot object collide
            \return Erase Centipede object
        */

        void CentipedeShotCollision(int SegmentNum);

        /** \brief Set Direction for movement of Centipede Segment
            \return Centipede object movement direction
        */

        void setSegmentDirectionY(int SegmentNum, bool DirectionIsDown);

         /** \brief Creates and Sets Centipede
            \return Centipede object creation
        */

        void setCentipede(float _gameWidth, float _gameHeight, sf::Vector2f _CentipedeSize, int NumSegments, float CentipedeSpeed);

        /** \brief Checks if the Centipede segment is in the player area
            \return set InArea in CentipedeSegments
        */

        void setSegmentIsInPlayerArea(int SegmentNum);

};

#endif // CENTIPEDE_H
