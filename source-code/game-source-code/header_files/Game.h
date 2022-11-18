#ifndef GAME_H
#define GAME_H
/** \file Game.h
    \brief Contains code for constructing a Game object
    The Game contains the structure of the flow of the game.
    The Game inherits all game objects.
 */
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

#include "../header_files/Player.h"
#include "../header_files/GameTextures.h"
#include "../header_files/GameSounds.h"
#include "../header_files/Shoot.h"
#include "../header_files/Centipede.h"
#include "../header_files/MushroomField.h"
#include "../header_files/DDTField.h"
#include "../header_files/Flea.h"
#include "../header_files/Spider.h"

#include<windows.h>

//////////////////////////////////////////////////////////////
//GAME CONSTANTS
//////////////////////////////////////////////////////////////
/** \brief Game Constants - Game Dimensions
*/
//Game dimensions
const int gameWidth = 800;
const int gameHeight = 600;
const float PlayerCeiling = 420;
/** \brief Game Constants - Player Hitbox sizes
*/
//Hitbox Sizes (Player hit box based of current sprite size)
const sf::Vector2f Standby(48,112);
const sf::Vector2f Up(58,114);
const sf::Vector2f Down(58,108);
const sf::Vector2f Left(68,102);
const sf::Vector2f Right(88,74);
const sf::Vector2f Power(126,154);
const sf::Vector2f Shooting(69,104);
/** \brief Game Constants - Game Object Sizes
*/
//Sprite sizes
const sf::Vector2f CentipedeSize(20,20);
const sf::Vector2f ShootSize(7,7);
const sf::Vector2f MushroomSize = CentipedeSize;
const sf::Vector2f FleaSize = CentipedeSize;
const sf::Vector2f SpiderSize(40,40);
const sf::Vector2f DDTSize = CentipedeSize;
/** \brief Game Constants - Game Object Speeds
*/
//Object Speeds
const float PlayerSpeed = 10.f;
const float ShootSpeed = 18.f;
const float FleaSpeed = 5.f;
const float SpiderSpeed = 2;
/** \brief Game Constants - Object Settings
*/
//Misc Object setttings
const int CentipedeStartSegments = 12;
const float reloadTimeConst = 0.15;
const int FleaMushroomSpawn = 14;//Spawn Randomness (1/(value+1)) *100 = percentage), 6.6 percent chance flea spawns a mushroom
const int DDTSpawnTimeConst = 4;
const int DDTSpawnChance = 3;
const int SpiderEatChance = 50;
const sf::Vector2f DDTExplosionRange = sf::Vector2f(MushroomSize.x*3, MushroomSize.y*3);
/** \brief Game Constants - Scoring system
*/
//scoring
const int headshot = 3000;
const int bodyshot = 500;
const int MushroomPoints = 50;
const int FleaPoints = 2000;
const int SpiderPoints = 2000;

/////////////////////////////////////////////////////////////
/** \class Game
    \brief Contains code for constructing a Game object
    The Game contains the structure of the flow of the game.
    The Game inherits all game objects.
    The Game contains all the global variables used in the game.
 */
//GAME CLASS
class Game
{
    private:
        //Changable Difficulty settings
        float CentipedeSpeed;
        int MushroomSpawnChance;
        float FleaSpawnTimeConst;
        float SpiderSpawnTimeConst;

        //For NewLife() function
        int score;
        int oldscore;

        sf::Text tempText, textLives, textScore, textHighscore;
        sf::Font font;
        std::vector<int> highscore;

        sf::Event event;

        //Clocks
        sf::Clock reloadClock;
        sf::Clock FleaSpawnClock;
        sf::Clock SpiderSpawnClock;
        sf::Clock DDTSpawnClock;
        sf::Clock DDTExplosionClock;

        sf::RenderWindow window;
        sf::Image Iconimage;

        //designed objects
        GameTextures TexturePack1;
        GameSounds SoundPack1;
        Player PlayerObject;
        Centipede CentipedeObject;
        MushroomField MushroomFieldObject;
        DDTField DDTFieldObject;
        std::vector<Shoot> ShotsVector;
        std::vector<Flea> FleaVector;
        std::vector<Spider> SpiderVector;

        //ORDER OF GAME FUNCTIONS
        bool Options();
        void Difficulty();
        void setDifficulty(int inp);

        void StartGame();

        void SetTexts();
        void DisplayBoard(sf::Text text1, sf::Text text2, sf::Text text3);

        //spawners
        void FleaSpawn(sf::Time FleaSpawnTime);
        void SpiderSpawn(sf::Time SpiderSpawnTime);
        void DDTSpawn(sf::Time DDTSpawnTime);

        //movements
        void PlayerControls(sf::Time reloadTime);
        void ShootMovement();
        void CentipedeMovementX();
        void CentipedeMovementY(int SegmentNum);
        void FleaMovement();
        void SpiderMovement();

        //Collision checks
        void MushroomCollisionChecks();
        void DDTCollisionChecks();
        void ShootDDTCollisionCheck(int DDTNum);
        void ShootMushroomCollisionCheck(int MushroomNum);
        bool CentipedeShootCollisionCheck(int CentipedeSegment);
        void FleaShootCollisionCheck(int FleaNum);
        void SpiderShootCollisionCheck(int ShootNum);
        void SpiderPlayerCollisionCheck(int SpiderNum);
        void SpiderMushroomCollisionCheck(int SpiderNum);

        //Game Management functions
        bool WonCheck();
        bool LostCheck();
        void LoseLife();
        void NewLife();
        sf::Vector2f FleaMushroomSpawnY(int FleaNum);//positional spawn of mushroom

        //music control
        bool PlayMenuMusic = true;
        bool PlayGameMusic = true;
        bool PlayedFromOptions = false;
        sf::Sound MenuSound;
        sf::Sound GameSound;

    public:
        //Constructor

        /** \brief Game constructor
            \return
        */

        Game();

        /** \brief Game destructor
            \return
        */

        virtual ~Game();

        /** \brief Mutator Function of the Main Menu function
            \return Exit or Passage on to Select Difficulty Screen
        */

        //Mutator
        void Menu();
};

#endif // GAME_H
