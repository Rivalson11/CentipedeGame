#include "..\header_files\DDT.h"

///////////////////////////////////////////////////////
//CONSTRUCTOR AND DESTRUCTOR
///////////////////////////////////////////////////////

DDT::DDT(sf::Vector2f DDTSize, int posX, int posY)
{
    DDTRect.setSize(DDTSize);
    DDTRect.setOrigin(DDTSize / 2.f);
    DDTRect.setPosition(posX, posY);
    //DDTRect.setOutlineThickness(0);
    //DDTRect.setOutlineColor(sf::Color::Red);
    //DDTRect.setFillColor(sf::Color(100, 250, 50));

    isExploding = false;
}

DDT::~DDT()
{
    //dtor
}

///////////////////////////////////////////////////////
//ACCESSORS
///////////////////////////////////////////////////////

sf::RectangleShape DDT::getDDTRect()
{
    return DDTRect;
}

sf::Vector2f DDT::getCoords()
{
    return DDTRect.getPosition();
}

sf::Time DDT::getExplodedTime()
{
    return ExplodedTime;
}

bool DDT::getIsExploding()
{
    return isExploding;
}

///////////////////////////////////////////////////////
//MUTATORS
///////////////////////////////////////////////////////

void DDT::setDDTBlockSize(sf::Vector2f _DDTSize)
{
    DDTRect.setSize(_DDTSize);
    DDTRect.setOrigin(_DDTSize / 2.f);
}

void DDT::setIsExploding()
{
    isExploding = true;
}

void DDT::setExplodedTime(sf::Time _ExplodedTime)
{
    ExplodedTime = _ExplodedTime;
}

