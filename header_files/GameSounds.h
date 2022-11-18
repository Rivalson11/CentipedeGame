#ifndef GAMESOUNDS_H
#define GAMESOUNDS_H
/** \file GameSounds.h
    \brief Contains code for constructing the GameSounds object
    GameSounds loads in all the sounds used in the game.
 */
#include <SFML/Audio.hpp>
/** \class GameSounds
    \brief Contains code for constructing the GameSounds object
    GameSounds loads in all the sounds used in the game.
    Creates all the different SoundBuffers and gets inherited by Game so the sounds can get played
 */
class GameSounds
{
    private:

        sf::SoundBuffer Bbomb;
        sf::SoundBuffer Bcentipede;
        sf::SoundBuffer Bflea;
        sf::SoundBuffer Bgame;
        sf::SoundBuffer Blost;
        sf::SoundBuffer Bmenu;
        sf::SoundBuffer Bmushroom;
        sf::SoundBuffer Bshoot;
        sf::SoundBuffer Bspider;
        sf::SoundBuffer Bwon;

        sf::Sound Sbomb;
        sf::Sound Scentipede;
        sf::Sound Sflea;
        sf::Sound Sgame;
        sf::Sound Slost;
        sf::Sound Smenu;
        sf::Sound Smushroom;
        sf::Sound Sshoot;
        sf::Sound Sspider;
        sf::Sound Swon;

    public:

        /** \brief GameSounds object construction
            \return GameSounds
        */

        GameSounds();

        /** \brief GameSounds object destruction
            \return
        */

        virtual ~GameSounds();

        //Accessors

        /** \brief Accessor for GameSounds object bomb
            \return sound
        */

        sf::Sound getBombSound();

        /** \brief Accessor for GameSounds object centipede
            \return sound
        */

        sf::Sound getCentipedeSound();

        /** \brief Accessor for GameSounds object flea
            \return sound
        */

        sf::Sound getFleaSound();

        /** \brief Accessor for GameSounds object game
            \return sound
        */

        sf::Sound getGameSound();

        /** \brief Accessor for GameSounds object lost
            \return sound
        */

        sf::Sound getLostSound();

        /** \brief Accessor for GameSounds object menu
            \return sound
        */

        sf::Sound getMenuSound();

        /** \brief Accessor for GameSounds object mushroom
            \return sound
        */

        sf::Sound getMushroomSound();

        /** \brief Accessor for GameSounds object shoot
            \return sound
        */

        sf::Sound getShootSound();

        /** \brief Accessor for GameSounds object spider
            \return sound
        */

        sf::Sound getSpiderSound();

        /** \brief Accessor for GameSounds object won
            \return sound
        */

        sf::Sound getWonSound();


};

#endif // GAMESOUNDS_H
