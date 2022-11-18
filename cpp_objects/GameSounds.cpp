#include "..\header_files\GameSounds.h"

#include <SFML/Audio.hpp>

GameSounds::GameSounds()
{
    //////////////////////////////////////////////////////////////
    //LOADING SOUNDS
    //////////////////////////////////////////////////////////////

    //Load Sound Buffers
    Bbomb.loadFromFile("resources/sounds/bomb.wav");
    Bcentipede.loadFromFile("resources/sounds/centipede.wav");
    Bflea.loadFromFile("resources/sounds/flea.wav");
    Bgame.loadFromFile("resources/sounds/game.wav");
    Blost.loadFromFile("resources/sounds/lost.wav");
    Bmenu.loadFromFile("resources/sounds/menu.wav");
    Bmushroom.loadFromFile("resources/sounds/mushroom.wav");
    Bshoot.loadFromFile("resources/sounds/shoot.wav");
    Bspider.loadFromFile("resources/sounds/spider.wav");
    Bwon.loadFromFile("resources/sounds/won.wav");

    //Create Sounds
    Sbomb.setBuffer(Bbomb);
    Scentipede.setBuffer(Bcentipede);
    Sflea.setBuffer(Bflea);
    Sgame.setBuffer(Bgame);
    Slost.setBuffer(Blost);
    Smenu.setBuffer(Bmenu);
    Smushroom.setBuffer(Bmushroom);
    Sshoot.setBuffer(Bshoot);
    Sspider.setBuffer(Bspider);
    Swon.setBuffer(Bwon);

}

//Accessors
sf::Sound GameSounds::getBombSound()
{
    return Sbomb;
}
sf::Sound GameSounds::getCentipedeSound()
{
    return Scentipede;
}
sf::Sound GameSounds::getFleaSound()
{
    return Sflea;
}
sf::Sound GameSounds::getGameSound()
{
    return Sgame;
}
sf::Sound GameSounds::getLostSound()
{
    return Slost;
}
sf::Sound GameSounds::getMenuSound()
{
    return Smenu;
}
sf::Sound GameSounds::getMushroomSound()
{
    return Smushroom;
}
sf::Sound GameSounds::getShootSound()
{
    return Sshoot;
}
sf::Sound GameSounds::getSpiderSound()
{
    return Sspider;
}
sf::Sound GameSounds::getWonSound()
{
    return Swon;
}

GameSounds::~GameSounds()
{
    //dtor
}
