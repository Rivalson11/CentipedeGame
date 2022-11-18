#include "..\header_files\DDTField.h"

///////////////////////////////////////////////////////
//CONSTRUCTOR AND DESTRUCTOR
///////////////////////////////////////////////////////

DDTField::DDTField()
{

}

DDTField::~DDTField()
{
    //dtor
}

///////////////////////////////////////////////////////
//ACCESSORS
///////////////////////////////////////////////////////

std::vector<DDT> DDTField::getDDTField()
{
    return DDTObjects;
}

sf::RectangleShape DDTField::getDDTBlock(int DDTNum)
{
    return DDTObjects[DDTNum].getDDTRect();
}

sf::Vector2f DDTField::getRectCoords(int DDTNum)
{
    return DDTObjects[DDTNum].getCoords();
}

sf::Time DDTField::getDDTExplodedTime(int DDTNum)
{
    return DDTObjects[DDTNum].getExplodedTime();
}

bool DDTField::getDDTIsExploded(int DDTNum)
{
    return DDTObjects[DDTNum].getIsExploding();
}

///////////////////////////////////////////////////////
//MUTATORS
///////////////////////////////////////////////////////

void DDTField::DestroyDDT(int DDTNum)
{
    DDTObjects.erase(DDTObjects.begin() + DDTNum);
}

void DDTField::ResetDDTField()
{
    if (!DDTObjects.empty())
    {
        DDTObjects.clear();
    }
}

void DDTField::SpawnDDT(float _gameWidth, float _PlayerCeiling, sf::Vector2f _DDTSize)
{
    int Xpos = (((rand() % (int)(_gameWidth/_DDTSize.x -1)) + 1) * _DDTSize.x) + _DDTSize.x/2;//cant spawn on X boundaries
    if (Xpos == ((_gameWidth/_DDTSize.x - 1) * _DDTSize.x) + _DDTSize.x/2)
    {
        Xpos = Xpos - _DDTSize.x;
    }
    int Ypos = ((rand() % (int)((_PlayerCeiling + 4*_DDTSize.y)/_DDTSize.y))* _DDTSize.y) + _DDTSize.y/2;//Cant spawn to close to y bottom boundaries
    DDT tempDDT(_DDTSize, Xpos, Ypos);
    DDTObjects.push_back(tempDDT);
}

void DDTField::setDDTExplosion(sf::Vector2f DDTExplosionRange, int _DDTNum, sf::Time _ExplodedTime)
{
    DDTObjects[_DDTNum].setDDTBlockSize(DDTExplosionRange);
    DDTObjects[_DDTNum].setExplodedTime(_ExplodedTime);
    DDTObjects[_DDTNum].setIsExploding();
}

