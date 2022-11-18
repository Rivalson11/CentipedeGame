#include "..\header_files\GameTextures.h"
#include "..\header_files\Player.h"
#include "..\header_files\Shoot.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>


///////////////////////////////////////////////////////
//CONSTRUCTOR
///////////////////////////////////////////////////////
GameTextures::GameTextures()
{
    //////////////////////////////////////////////////////////////
    //LOADING TEXTURES
    //////////////////////////////////////////////////////////////

    //Player Sprites
    TplayerSprites[0].loadFromFile("resources/textures/sprites/gokusprites/standby.png");
    TplayerSprites[1].loadFromFile("resources/textures/sprites/gokusprites/up.png");
    TplayerSprites[2].loadFromFile("resources/textures/sprites/gokusprites/down.png");
    TplayerSprites[3].loadFromFile("resources/textures/sprites/gokusprites/left.png");
    TplayerSprites[4].loadFromFile("resources/textures/sprites/gokusprites/right.png");
    TplayerSprites[5].loadFromFile("resources/textures/sprites/gokusprites/power.png");
    TplayerSprites[6].loadFromFile("resources/textures/sprites/gokusprites/shoot.png");

    //Game Backgrounds
    TbackgroundSprites[0].loadFromFile("resources/textures/backgrounds/GameScreen.png");
    TbackgroundSprites[1].loadFromFile("resources/textures/backgrounds/SplashScreen.png");
    TbackgroundSprites[2].loadFromFile("resources/textures/backgrounds/LostScreen.png");
    TbackgroundSprites[3].loadFromFile("resources/textures/backgrounds/WonScreen.png");
    TbackgroundSprites[4].loadFromFile("resources/textures/backgrounds/DifficultyScreen.png");
    TbackgroundSprites[5].loadFromFile("resources/textures/backgrounds/OptionsScreen.png");

    //Shoot Sprite
    TshootSprites.loadFromFile("resources/textures/sprites/fireballsprites/fireball.png");

    //Centipede Sprite
    TcentipedeSprites[0].loadFromFile("resources/textures/sprites/snakesprites/body.png");
    TcentipedeSprites[1].loadFromFile("resources/textures/sprites/snakesprites/headright.png");
    TcentipedeSprites[2].loadFromFile("resources/textures/sprites/snakesprites/headleft.png");

    //Mushroom Sprites
    TmushroomSprites[0].loadFromFile("resources/textures/sprites/dragonballsprites/fullball.png");
    TmushroomSprites[1].loadFromFile("resources/textures/sprites/dragonballsprites/brokenball.png");

    //DDT Sprites
    TddtSprites[0].loadFromFile("resources/textures/sprites/bombsprites/small.png");
    TddtSprites[1].loadFromFile("resources/textures/sprites/bombsprites/big.png");

    //Flea Sprites
    TfleaSprites.loadFromFile("resources/textures/sprites/majinboosprites/majinboo.png");

    //Spider Sprites
    TspiderSprites[0].loadFromFile("resources/textures/sprites/friezasprites/right.png");
    TspiderSprites[1].loadFromFile("resources/textures/sprites/friezasprites/left.png");

    //////////////////////////////////////////////////////////////
    //SPRITE CREATION
    //////////////////////////////////////////////////////////////

    //Create Player Sprites
    SplayerSprites[0].setTexture(TplayerSprites[0]);
    SplayerSprites[1].setTexture(TplayerSprites[1]);
    SplayerSprites[2].setTexture(TplayerSprites[2]);
    SplayerSprites[3].setTexture(TplayerSprites[3]);
    SplayerSprites[4].setTexture(TplayerSprites[4]);
    SplayerSprites[5].setTexture(TplayerSprites[5]);
    SplayerSprites[6].setTexture(TplayerSprites[6]);

    //Create Game Background Sprites
    SbackgroundSprites[0].setTexture(TbackgroundSprites[0]);
    SbackgroundSprites[1].setTexture(TbackgroundSprites[1]);
    SbackgroundSprites[2].setTexture(TbackgroundSprites[2]);
    SbackgroundSprites[3].setTexture(TbackgroundSprites[3]);
    SbackgroundSprites[4].setTexture(TbackgroundSprites[4]);
    SbackgroundSprites[5].setTexture(TbackgroundSprites[5]);

    //Create Shoot Sprite
    SshootSprites.setTexture(TshootSprites);

    //Create Centipede Sprite
    ScentipedeSprites[0].setTexture(TcentipedeSprites[0]);
    ScentipedeSprites[1].setTexture(TcentipedeSprites[1]);
    ScentipedeSprites[2].setTexture(TcentipedeSprites[2]);

    //Create Mushroom Sprite
    SmushroomSprites[0].setTexture(TmushroomSprites[0]);
    SmushroomSprites[1].setTexture(TmushroomSprites[1]);

    //Create DDT Sprite
    SddtSprites[0].setTexture(TddtSprites[0]);
    SddtSprites[1].setTexture(TddtSprites[1]);

    //Create Flea Sprite
    SfleaSprites.setTexture(TfleaSprites);

    //Create Spider Sprite
    SspiderSprites[0].setTexture(TspiderSprites[0]);
    SspiderSprites[1].setTexture(TspiderSprites[1]);

    //set Starting game screen to splashscreem
    ScurrentBackgroundSprite = SbackgroundSprites[1];
}

//////////////////////////////////////////////////////////////
//ACCESSORS
//////////////////////////////////////////////////////////////

sf::Sprite GameTextures::getCurrentPlayerSprite()
{
    return ScurrentPlayerSprite;
}

sf::Sprite GameTextures::getCurrentBackgroundSprite()
{
    return ScurrentBackgroundSprite;
}

sf::Sprite GameTextures::getCurrentShootSprite()
{
    return ScurrentShootSprite;
}

sf::Sprite GameTextures::getCurrentCentipedeSprite()
{
    return ScurrentCentipedeSprite;
}

sf::Sprite GameTextures::getCurrentMushroomSprite()
{
    return ScurrentMushroomSprite;
}

sf::Sprite GameTextures::getCurrentDDTSprite()
{
    return ScurrentDDTSprite;
}

sf::Sprite GameTextures::getCurrentFleaSprite()
{
    return ScurrentFleaSprite;
}

sf::Sprite GameTextures::getCurrentSpiderSprite()
{
    return ScurrentSpiderSprite;
}

//////////////////////////////////////////////////////////////
//MUTATORS
//////////////////////////////////////////////////////////////

void GameTextures::setPlayerSpriteOrigin(sf::Vector2f SpriteSize)
{
    ScurrentPlayerSprite.setOrigin(SpriteSize.x / 2 , SpriteSize.y / 2);
}

void GameTextures::setCurrentPlayerSprite(int inp)
{
    switch (inp)
    {
    case 0:
            ScurrentPlayerSprite = SplayerSprites[0];//standby
            break;

    case 1:
            ScurrentPlayerSprite = SplayerSprites[1];//up
            break;

    case 2:
            ScurrentPlayerSprite = SplayerSprites[2];//down
            break;

    case 3:
            ScurrentPlayerSprite = SplayerSprites[3];//left
            break;

    case 4:
            ScurrentPlayerSprite = SplayerSprites[4];//right
            break;

    case 5:
            ScurrentPlayerSprite = SplayerSprites[5];//power
            break;

    case 6:
            ScurrentPlayerSprite = SplayerSprites[6];//shoot
            break;

    }
}

void GameTextures::setCurrentBackgroundSprite(int inp)
{
    switch (inp)
    {
    case 0:
            ScurrentBackgroundSprite = SbackgroundSprites[0];//game screen
            break;

    case 1:
            ScurrentBackgroundSprite = SbackgroundSprites[1];//splash screen
            break;

    case 2:
            ScurrentBackgroundSprite = SbackgroundSprites[2];//lost sreen
            break;

    case 3:
            ScurrentBackgroundSprite = SbackgroundSprites[3];//won screen
            break;

    case 4:
            ScurrentBackgroundSprite = SbackgroundSprites[4];//difficulty screen
            break;
    case 5:
            ScurrentBackgroundSprite = SbackgroundSprites[5];//options screen
            break;
    }
}

void GameTextures::setCurrentShootSprite(int inp)
{
    switch (inp)
    {
    case 0:
            ScurrentShootSprite = SshootSprites;//basic fireball
            ScurrentShootSprite.setOrigin(23,8);
            break;
    }
}

void GameTextures::setCurrentCentipedeSprite(int inp)
{
    switch (inp)
    {
    case 0:
            ScurrentCentipedeSprite = ScentipedeSprites[0];//body of snake
            ScurrentCentipedeSprite.setOrigin(10,10);
            break;

    case 1:
            ScurrentCentipedeSprite = ScentipedeSprites[1];//head right of snake
            ScurrentCentipedeSprite.setOrigin(25,30);
            break;

    case 2:
            ScurrentCentipedeSprite = ScentipedeSprites[2];//head left of snake
            ScurrentCentipedeSprite.setOrigin(15,30);
            break;

    }
}

void GameTextures::setCurrentMushroomSprite(int inp)
{
    switch (inp)
    {
    case 0:
            ScurrentMushroomSprite = SmushroomSprites[0];//full solid dragon ball
            ScurrentMushroomSprite.setOrigin(10,10);
            break;

    case 1:
            ScurrentMushroomSprite = SmushroomSprites[1];//broken dragon ball
            ScurrentMushroomSprite.setOrigin(10,10);
            break;

    }
}

void GameTextures::setCurrentDDTSprite(int inp)
{
    switch (inp)
    {
    case 0:
            ScurrentDDTSprite = SddtSprites[0];//small bomb
            ScurrentDDTSprite.setOrigin(10,10);
            break;

    case 1:
            ScurrentDDTSprite = SddtSprites[1];//big bomb
            ScurrentDDTSprite.setOrigin(30,30);
            break;

    }
}

void GameTextures::setCurrentFleaSprite(int inp)
{
    switch (inp)
    {
    case 0:
            ScurrentFleaSprite = SfleaSprites;//majin boo
            ScurrentFleaSprite.setOrigin(20,20);
            break;
    }
}

void GameTextures::setCurrentSpiderSprite(int inp)
{
    switch (inp)
    {
    case 0:
            ScurrentSpiderSprite = SspiderSprites[0];//right
            ScurrentSpiderSprite.setOrigin(60,30);
            break;

    case 1:
            ScurrentSpiderSprite = SspiderSprites[1];//left
            ScurrentSpiderSprite.setOrigin(20,30);
            break;

    }
}

GameTextures::~GameTextures()
{
    //dtor
}
