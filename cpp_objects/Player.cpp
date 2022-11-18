    #include <SFML/Graphics.hpp>
    #include <iostream>
    #include "..\header_files\Player.h"

///////////////////////////////////////////////////////
//CONSTRUCTOR
///////////////////////////////////////////////////////

Player::Player(float _gameWidth, float _gameHeight , sf::Vector2f _PlayerSize, float _PlayerSpeed) //Constructor with parameters
{
    PlayerSize = _PlayerSize;
    PlayerSpeed = _PlayerSpeed;

    PlayerRect.setSize(PlayerSize - sf::Vector2f(7, 7));//subtract to make more reasonable sized hitbox
    PlayerRect.setOrigin(PlayerSize / 2.f);
    PlayerRect.setPosition(_gameWidth / 2, _gameHeight - PlayerSize.y/2);
    //PlayerRect.setOutlineThickness(3);
    //PlayerRect.setOutlineColor(sf::Color::Blue);
    //PlayerRect.setFillColor(sf::Color(100, 100, 200));

    lives = 3;

}

///////////////////////////////////////////////////////
//ACCESSORS
///////////////////////////////////////////////////////

sf::RectangleShape Player::getPlayerRect()
{
    return PlayerRect;
}

sf::Vector2f Player::getCoords()
{
    return PlayerRect.getPosition();
}

int Player::getLives()
{
    return lives;
}

///////////////////////////////////////////////////////
//MUTATORS
///////////////////////////////////////////////////////

void Player::MoveRight()
{
    PlayerRect.move(PlayerSpeed, 0.f);
}

void Player::MoveLeft()
{
    PlayerRect.move(-PlayerSpeed, 0.f);
}

void Player::MoveUp()
{
    PlayerRect.move(0.f, - PlayerSpeed);
}

void Player::MoveDown()
{
    PlayerRect.move(0.f, PlayerSpeed);
}


void Player::setPlayerSize(sf::Vector2f newPlayerSize)//changes hit box size based on player action
{
    PlayerSize = newPlayerSize;
    PlayerRect.setSize(PlayerSize - sf::Vector2f(7, 7));//subtract to make more reasonable sized hitbox
    PlayerRect.setOrigin(PlayerSize / 2.f);
}

void Player::resetPlayerPosition(float _gameWidth, float _gameHeight)
{
    PlayerRect.setPosition(_gameWidth / 2, _gameHeight - PlayerSize.y/2);
}

void Player::setLives(int newlives)
{
    lives = newlives;
}
