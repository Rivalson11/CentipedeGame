#include <SFML/Graphics.hpp>
#include <iostream>
#include "..\header_files\Shoot.h"

//////////////////////////////////////////////////////////////
//CONSTRUCTOR AND DESTRUCTOR
//////////////////////////////////////////////////////////////

Shoot::Shoot(sf::Vector2f Position, sf::Vector2f ShootSize, float _ShootSpeed)
{
    ShootSpeed = _ShootSpeed;

    ShootRect.setSize(ShootSize);
    ShootRect.setOrigin(ShootSize/2.f);
    ShootRect.setPosition(Position);//shoot from location of player
    //ShootRect.setOutlineThickness(3);
    //ShootRect.setOutlineColor(sf::Color::Red);
    //ShootRect.setFillColor(sf::Color(100, 100, 200));
}

Shoot::~Shoot()
{
    //dtor
}

//////////////////////////////////////////////////////////////
//ACCESSORS
//////////////////////////////////////////////////////////////

sf::Vector2f Shoot::getCoords()
{
    return ShootRect.getPosition();
}

sf::RectangleShape Shoot::getShootRect()
{
    return ShootRect;
}

//////////////////////////////////////////////////////////////
//MUTATORS
//////////////////////////////////////////////////////////////

void Shoot::Move()
{
        ShootRect.move(0.f, - ShootSpeed);
}

void Shoot::resetShootPosition(sf::Vector2f Position)
{
    ShootRect.setPosition(Position);
}


