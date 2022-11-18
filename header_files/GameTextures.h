#ifndef GAMETEXTURES_H
#define GAMETEXTURES_H
/** \file GameTextures.h
    \brief Contains code for constructing the GameTextures object
    GameTextures loads in all the images and sprites used in the game.
 */
#include <SFML/Graphics.hpp>
/** \class GameTextures
    \brief Contains code for constructing the GameTextures object
    GameTextures loads in all the images and sprites used in the game.
    Creates all the different Sprites and gets inherited by Game so the Sprites can get applied on all the Game Objects
 */
class GameTextures
{
    private:

        sf::Texture TplayerSprites[7];
        sf::Texture TbackgroundSprites[6];
        sf::Texture TshootSprites;
        sf::Texture TcentipedeSprites[3];
        sf::Texture TmushroomSprites[2];
        sf::Texture TddtSprites[2];
        sf::Texture TfleaSprites;
        sf::Texture TspiderSprites[2];

        sf::Sprite SplayerSprites[7];
        sf::Sprite SbackgroundSprites[6];
        sf::Sprite SshootSprites;
        sf::Sprite ScentipedeSprites[3];
        sf::Sprite SmushroomSprites[2];
        sf::Sprite SddtSprites[2];
        sf::Sprite SfleaSprites;
        sf::Sprite SspiderSprites[2];

        sf::Sprite ScurrentPlayerSprite;
        sf::Sprite ScurrentBackgroundSprite;
        sf::Sprite ScurrentShootSprite;
        sf::Sprite ScurrentCentipedeSprite;
        sf::Sprite ScurrentMushroomSprite;
        sf::Sprite ScurrentDDTSprite;
        sf::Sprite ScurrentFleaSprite;
        sf::Sprite ScurrentSpiderSprite;

        sf::Text Lives;
        sf::Text LiveScore;
        sf::Text HighScore;

    public:

        //Constructors
        GameTextures();
        virtual ~GameTextures();

        //Accessors

        /** \brief Accessor for GameTextures object player
            \return sprite
        */

        sf::Sprite getCurrentPlayerSprite();

        /** \brief Accessor for GameTextures object background
            \return sprite
        */

        sf::Sprite getCurrentBackgroundSprite();

        /** \brief Accessor for GameTextures object shoot
            \return sprite
        */

        sf::Sprite getCurrentShootSprite();

        /** \brief Accessor for GameTextures object centipede
            \return sprite
        */

        sf::Sprite getCurrentCentipedeSprite();

        /** \brief Accessor for GameTextures object mushroom
            \return sprite
        */

        sf::Sprite getCurrentMushroomSprite();

        /** \brief Accessor for GameTextures object DDT
            \return sprite
        */

        sf::Sprite getCurrentDDTSprite();

        /** \brief Accessor for GameTextures object flea
            \return sprite
        */

        sf::Sprite getCurrentFleaSprite();

        /** \brief Accessor for GameTextures object spider
            \return sprite
        */

        sf::Sprite getCurrentSpiderSprite();

        //Mutators

        /** \brief Mutator for GameTextures object player
            \return set sprite
        */

        void setCurrentPlayerSprite(int inp);

        /** \brief Mutator for GameTextures object backgrounds
            \return set sprite
        */

        void setCurrentBackgroundSprite(int inp);

        /** \brief Mutator for GameTextures object shoot
            \return set sprite
        */

        void setCurrentShootSprite(int inp);

        /** \brief Mutator for GameTextures object centipede
            \return set sprite
        */

        void setCurrentCentipedeSprite(int inp);

        /** \brief Mutator for GameTextures object mushroom
            \return set sprite
        */

        void setCurrentMushroomSprite(int inp);

        /** \brief Mutator for GameTextures object ddt
            \return set sprite
        */

        void setCurrentDDTSprite(int inp);

        /** \brief Mutator for GameTextures object flea
            \return set sprite
        */

        void setCurrentFleaSprite(int inp);

        /** \brief Mutator for GameTextures object spider
            \return set sprite
        */

        void setCurrentSpiderSprite(int inp);

        /** \brief Mutator for GameTextures object player
            \return set sprite
        */

        void setPlayerSpriteOrigin(sf::Vector2f SpriteSize);


};

#endif // GAMETEXTURES_H
