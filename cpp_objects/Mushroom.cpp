#include "..\header_files\Mushroom.h"

///////////////////////////////////////////////////////
//CONSTRUCTOR AND DESTRUCTOR
///////////////////////////////////////////////////////

Mushroom::Mushroom(sf::Vector2f MushroomSize, int posX, int posY)
{
    health = 4;

    MushroomRect.setSize(MushroomSize);
    MushroomRect.setOrigin(MushroomSize / 2.f);
    MushroomRect.setPosition(posX, posY);
    //MushroomRect.setOutlineThickness(0);
    //MushroomRect.setOutlineColor(sf::Color::Red);
    //MushroomRect.setFillColor(sf::Color(100, 250, 50));
}

Mushroom::~Mushroom()
{
    //dtor
}

///////////////////////////////////////////////////////
//ACCESSORS
///////////////////////////////////////////////////////

sf::RectangleShape Mushroom::getMushroomRect()
{
    return MushroomRect;
}

sf::Vector2f Mushroom::getCoords()
{
    return MushroomRect.getPosition();
}

int Mushroom::getMushroomHealth()
{
    return health;
}

///////////////////////////////////////////////////////
//MUTATORS
///////////////////////////////////////////////////////

void Mushroom::setMushroomHealth()
{
    health--;
}
