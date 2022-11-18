#include "..\header_files\Flea.h"


///////////////////////////////////////////////////////
//CONSTRUCTOR AND DESTRUCTOR
///////////////////////////////////////////////////////

Flea::Flea(float _SpawnX, sf::Vector2f _FleaSize, float _FleaSpeed)
{
    FleaSpeed = _FleaSpeed;
    //ctor
    FleaRect.setSize(_FleaSize);//subtract to make more reasonable sized hitbox
    FleaRect.setOrigin(_FleaSize / 2.f);
    FleaRect.setPosition(_SpawnX, -_FleaSize.y);//spawns in theoreticall grid
    //FleaRect.setOutlineColor(sf::Color::Blue);
    //FleaRect.setFillColor(sf::Color(100, 100, 200));
}

Flea::~Flea()
{
    //dtor
}

///////////////////////////////////////////////////////
//ACCESSORS
///////////////////////////////////////////////////////
sf::Vector2f Flea::getCoords()
{
    return FleaRect.getPosition();
}

sf::RectangleShape Flea::getFleaRect()
{
    return FleaRect;
}

///////////////////////////////////////////////////////
//MUTATORS
///////////////////////////////////////////////////////
void Flea::MoveDown()
{
    FleaRect.move(0.f, FleaSpeed);
}
