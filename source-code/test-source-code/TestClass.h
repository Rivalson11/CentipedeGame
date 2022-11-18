#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>

#include "../game-source-code/header_files/Player.h"
#include "../game-source-code/header_files/Centipede.h"
#include "../game-source-code/header_files/GameTextures.h"
#include "../game-source-code/header_files/GameSounds.h"
#include "../game-source-code/header_files/Shoot.h"
#include "../game-source-code/header_files/Centipede.h"
#include "../game-source-code/header_files/MushroomField.h"
#include "../game-source-code/header_files/DDTField.h"
#include "../game-source-code/header_files/Flea.h"
#include "../game-source-code/header_files/Spider.h"

#include<windows.h>

//////////////////////////////////////////////////////////////
//GAME CONSTANTS
//////////////////////////////////////////////////////////////

/** \brief Game Constants
*/

//Game dimensions
const int gameWidth = 800;
const int gameHeight = 600;
const float PlayerCeiling = 420;

//Hitbox Sizes (Player hit box based of current sprite size)
const sf::Vector2f Standby(48,112);
const sf::Vector2f Up(58,114);
const sf::Vector2f Down(58,108);
const sf::Vector2f Left(68,102);
const sf::Vector2f Right(88,74);
const sf::Vector2f Power(126,154);
const sf::Vector2f Shooting(69,104);

//Sprite sizes
const sf::Vector2f CentipedeSize(20,20);
const sf::Vector2f ShootSize(7,7);
const sf::Vector2f MushroomSize = CentipedeSize;
const sf::Vector2f FleaSize = CentipedeSize;
const sf::Vector2f SpiderSize(40,40);
const sf::Vector2f DDTSize = CentipedeSize;

//Object Speeds
const float PlayerSpeed = 10.f;
const float ShootSpeed = 18.f;
const float FleaSpeed = 5.f;
const float SpiderSpeed = 2;

//Misc Object setttings
const int CentipedeStartSegments = 1;// for purpose of testing
const float reloadTimeConst = 0.2;
const int FleaMushroomSpawn = 14;//Spawn Randomness (1/(value+1)) *100 = percentage), 6.6 percent chance flea spawns a mushroom
const int DDTSpawnTimeConst = 4;
const int DDTSpawnChance = 3;
const int SpiderEatChance = 50;
const sf::Vector2f DDTExplosionRange = sf::Vector2f(MushroomSize.x*3, MushroomSize.y*3);

//scoring
const int headshot = 3000;
const int bodyshot = 500;
const int MushroomPoints = 50;
const int FleaPoints = 2000;
const int SpiderPoints = 2000;

//Difficulty settings

const float CentipedeSpeed = 5;
const int MushroomSpawnChance = 9999999;
const float FleaSpawnTimeConst = 0.1;
const float SpiderSpawnTimeConst = 0.1;

/////////////////////////////////////////////////////////////


class TestClass
{
    private:



        //designed objects
        Player PlayerObject;
        Centipede CentipedeObject;
        MushroomField MushroomFieldObject;
        DDTField DDTFieldObject;
        std::vector<Shoot> ShotsVector;
        std::vector<Flea> FleaVector;
        std::vector<Spider> SpiderVector;

        //Clocks
        sf::Clock reloadClock;
        sf::Clock FleaSpawnClock;
        sf::Clock SpiderSpawnClock;
        sf::Clock DDTSpawnClock;
        sf::Clock DDTExplosionClock;

        int score;
        int oldscore;
        std::vector<int> highscore;

    public:



        //Constructor and destructor

        /** \brief TestClass() constructor
            \return return game object creation
        */

        TestClass();

        /** \brief TestClass() destructor
            \return return game object deletion
        */

        virtual ~TestClass();

        /////////////////////////////////////////////////////////////
        //ACCESSORS
        /////////////////////////////////////////////////////////////
        //positional returns

        /** \brief Accessor to find current position of Player
            \return return Vector2f coords
        */

        sf::Vector2f getPlayerPosition();

        /** \brief Accessor to find current position of Centipede
            \return return Vector2f coords
        */

        sf::Vector2f getCentipedePosition();

        /** \brief Accessor to find current position of Shoot
            \return return Vector2f coords
        */

        sf::Vector2f getShootPosition();

        /** \brief Accessor to find current position of Mushroom
            \return return Vector2f coords
        */

        sf::Vector2f getMushroomPosition();

        /** \brief Accessor to find current position of Spider
            \return return Vector2f coords
        */

        sf::Vector2f getSpiderPosition();

        /** \brief Accessor to find current position of Flea
            \return return Vector2f coords
        */

        sf::Vector2f getFleaPosition();

        /** \brief Accessor to find current position of DDT
            \return return Vector2f coords
        */

        sf::Vector2f getDDTPosition();

        /** \brief Accessor to find current direction of Centipede
            \return return bool
        */

        bool getCentipeDirectionIsRight();

        //Shoot interactions

        /** \brief Checks if Centipede vector is empty
            \return return bool
        */

        bool CentipedeIsEmpty();

        /** \brief Checks if Spider vector is empty
            \return return bool
        */

        bool spiderIsEmpty();

        /** \brief Checks if Flea vector is empty
            \return return bool
        */

        bool FleaIsEmpty();

        /** \brief Checks if Mushroom vector is empty
            \return return bool
        */

        bool MushroomIsEmpty();

        /** \brief Checks if DDT is shot
            \return return bool
        */

        bool DDTIsShot();

        /** \brief Accessor to get number of Mushrooms
            \return return variable
        */

        int getnumMushrooms();

        /** \brief Accessor to get Mushroom current health
            \return return variable
        */

        int getMushroomHealth();

        /** \brief Accessor to get Player lives remaining
            \return return variable
        */

        int getPlayerHealth();

        //random events

        /** \brief Random Event That Checks if Mushroom is destroyed
            \return return bool
        */

        bool MushroomIsEaten();

        /** \brief Random Event That Checks if DDT bomb is created
            \return return bool
        */

        bool DDTIsSpawned();

        /////////////////////////////////////////////////////////////
        //MUTATORS
        /////////////////////////////////////////////////////////////

        /** \brief Mutator Function That Clears all Mushroom Objects
            \return Delete Mushroom Objects
        */

        void clearMushrooms();

        //spawners

        /** \brief Spawning Function That Creates a new Flea Object
            \return Flea Object creation
        */

        void FleaSpawn(sf::Vector2f SpawnPos);

        /** \brief Spawning Function That Creates a new Spider Object
            \return Spider Object creation
        */

        void SpiderSpawn();

        /** \brief Spawning Function That Creates a new DDT Object
            \return DDT Object creation
        */

        void DDTSpawn();

        /** \brief Spawning Function That Creates a new shoot Object
            \return shoot Object creation
        */

        void ShootSpawn(sf::Vector2f spawnPos);

        /** \brief Spawning Function That Creates a new Mushroom Object
            \return Mushroom Object creation
        */

        void MushroomSpawner(sf::Vector2f spawnPos);

        //movements

        /** \brief Movement Function That Moves Player Object in any direction
            \return Player position change
        */

        void PlayerControls(std::string Direction);

        /** \brief Movement Function That Moves Shoot Object Up
            \return Shoot position change
        */

        void ShootMovement();

        /** \brief Movement Function That Moves Centipede Segment Right/Left
            \return Centipede position change
        */

        void CentipedeMovementX();

        /** \brief Movement Function That Moves Centipede Segment Down/Up
            \return Centipede position change
        */

        void CentipedeMovementY(int SegmentNum);

        /** \brief Movement Function That Moves Flea Object
            \return Flea position change
        */

        void FleaMovement();

         /** \brief Movement Function That Moves Spider Object
            \return Spider position change
        */

        void SpiderMovement(int Direction);

        //Collision checks

        /** \brief Collision checks Function That Checks if the Centipede and Mushroom Object collide
            \return Check Shoot Mushroom collision. Centipede Direction Change
        */

        void MushroomCollisionChecks();

        /** \brief Collision checks Function That Checks if the DDT and all Game Object collide
            \return Check all game object position. Possible Game object deletion, DDT Deletion
        */

        void DDTCollisionChecks();

        /** \brief Collision checks Function That Checks if the DDT and Shoot Object collide
            \return DDT set Explosion, Shoot Deletion
        */

        void ShootDDTCollisionCheck(int DDTNum);

        /** \brief Collision checks Function That Checks if the Mushroom and Shoot Object collide
            \return Mushroom Health Check. Possible Mushroom Deletion, Score Update, and New Life Function Called, Shoot Deletion
        */

        void ShootMushroomCollisionCheck(int MushroomNum);

        /** \brief Collision checks Function That Checks if the Centipede and Shoot Object collide
            \return Centipede Segment Deletion, Score Update, and New Life Function Called, Shoot Deletion
        */

        bool CentipedeShootCollisionCheck(int CentipedeSegment);

        /** \brief Collision checks Function That Checks if the Flea and Shoot Object collide
            \return Flea Deletion, Score Update, and New Life Function Called, Shoot Deletion
        */

        void FleaShootCollisionCheck(int FleaNum);

        /** \brief Collision checks Function That Checks if the Spider and Shoot Object collide
            \return Spider Deletion, Score Update, and New Life Function Called, Shoot Deletion
        */

        void SpiderShootCollisionCheck(int ShootNum);

        /** \brief Collision checks Function That Checks if the Spider and Player Object collide
            \return Lose Life Function Called, Shoot Deletion
        */

        void SpiderPlayerCollisionCheck(int SpiderNum);

        /** \brief Collision checks Function That Checks if the Spider and Mushroom Object collide
            \return Destroy Mushroom Object
        */

        void SpiderMushroomCollisionCheck(int SpiderNum);

        //Game Management functions

        /** \brief Game Management function That Checks if the User has Won the Game
            \return End Game Bool
        */

        bool WonCheck();

        /** \brief Game Management function That Checks if the User has Lost the Game
            \return End Game Bool
        */

        bool LostCheck();

        /** \brief Game Management function That Checks if the Player has Lost a life
            \return Lose Life Bool
        */

        void LoseLife();

        /** \brief Game Management function That Checks if the Player gains an extra life
            \return New Life Bool
        */

        void NewLife();

         /** \brief Game Object Mushroom Creation from Flea
            \return New Mushroom Coords
        */

        sf::Vector2f FleaMushroomSpawnY(int FleaNum);//positional spawn of mushroom

};

#endif // TESTCLASS_H
