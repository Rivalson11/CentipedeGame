#include "..\header_files\MushroomField.h"

///////////////////////////////////////////////////////
//CONSTRUCTOR AND DESTRUCTOR
///////////////////////////////////////////////////////
MushroomField::MushroomField(float _gameWidth, float _gameHeight, sf::Vector2f _centipedeSize, int MushroomSpawnChance)
{
    setMushroomField(_gameWidth, _gameHeight, _centipedeSize, MushroomSpawnChance);
}

MushroomField::~MushroomField()
{
    //dtor
}

///////////////////////////////////////////////////////
//ACCESSORS
///////////////////////////////////////////////////////
std::vector<Mushroom> MushroomField::getMushroomField()
{
    return MushroomObjects;
}

sf::RectangleShape MushroomField::getMushroomBlock(int MushroomNum)
{
    return MushroomObjects[MushroomNum].getMushroomRect();
}

sf::Vector2f MushroomField::getBlockCoords(int MushroomNum)
{
    return MushroomObjects[MushroomNum].getCoords();
}

sf::Vector2f MushroomField::getMushroomCoords(int MushroomNum)
{
  return MushroomObjects[MushroomNum].getMushroomRect().getPosition();
}

int MushroomField::getMushroomHealth(int MushroomNum)
{
    return MushroomObjects[MushroomNum].getMushroomHealth();
}

///////////////////////////////////////////////////////
//MUTATORS
///////////////////////////////////////////////////////

void MushroomField::SpawnMushroom(sf::Vector2f SpawnPosition, bool currentDirectionRight, sf::Vector2f MushroomSize)
{
    float gridSpawnPositionX;
    if (currentDirectionRight)
    {
        //spawns in grid block closest too but not touching next centipedesegment
        gridSpawnPositionX =  (floor((SpawnPosition.x - MushroomSize.x/2) / MushroomSize.x)) * MushroomSize.x;
        gridSpawnPositionX  = gridSpawnPositionX  + MushroomSize.x + MushroomSize.x/2;
    }
    else
    {
        //spawns in grid block closest too but not touching next centipedesegment
        gridSpawnPositionX =  (floor((SpawnPosition.x + MushroomSize.x/2) / MushroomSize.x)) * MushroomSize.x;
        gridSpawnPositionX  = gridSpawnPositionX - MushroomSize.x/2;
    }
    Mushroom tempMushroom(MushroomSize,  gridSpawnPositionX, SpawnPosition.y);
    MushroomObjects.push_back(tempMushroom);
}

void MushroomField::DestroyMushroom(int MushroomNum)
{
    MushroomObjects.erase(MushroomObjects.begin() + MushroomNum);
}

void MushroomField::setMushroomHealth(int MushroomNum)
{
    MushroomObjects[MushroomNum].setMushroomHealth();
}

void MushroomField::setMushroomField(float _gameWidth, float _gameHeight, sf::Vector2f MushroomSize, int MushroomSpawnChance)
{
    if (!MushroomObjects.empty())
    {
        MushroomObjects.clear();
    }
    //loops through a grid like structure of the game screen to place mushroom in exact grid like locations
    for (int row = 1; row < (_gameHeight - 120)/MushroomSize.y; row++)//Do not spawn any musrooms in the first row so the centipede cannot collide with mushroom in its spawn area
    {
        for (int column = 1; column < _gameWidth/MushroomSize.x - 1; column++)
        {
            int _MushroomSpawnChance = rand() % MushroomSpawnChance;
            if (_MushroomSpawnChance == 0)
            {
                Mushroom tempMushroom(MushroomSize, column*MushroomSize.x + MushroomSize.x/2, row*MushroomSize.y + MushroomSize.y/2);
                MushroomObjects.push_back(tempMushroom);
            }
        }
    }
}

void MushroomField::ClearMushroomField()
{
    MushroomObjects.clear();
}
