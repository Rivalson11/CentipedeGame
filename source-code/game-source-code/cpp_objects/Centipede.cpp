#include "../header_files/Centipede.h"
#include <iostream>
///////////////////////////////////////////////////////
//CONSTRUCTOR AND DESTRUCTOR
///////////////////////////////////////////////////////

Centipede::Centipede(float _gameWidth, float _gameHeight, sf::Vector2f _CentipedeSize, int NumSegments, float CentipedeSpeed)
{
    setCentipede(_gameWidth, _gameHeight, _CentipedeSize, NumSegments, CentipedeSpeed);
}

Centipede::~Centipede()
{

}

///////////////////////////////////////////////////////
//ACCESSORS
///////////////////////////////////////////////////////

std::vector<CentipedeSegment> Centipede::getCentipede()
{
    return CentipedeSegments;
}

sf::RectangleShape Centipede::getSegmentRect(int SegmentNum)
{
    return CentipedeSegments[SegmentNum].getCentipedeRect();
}

sf::Vector2f Centipede::getSegmentCoords(int SegmentNum)
{
    return CentipedeSegments[SegmentNum].getCentipedeRectCoords();
}

bool Centipede::getSegmentCurrentDirectionX(int SegmentNum)
{
    return CentipedeSegments[SegmentNum].getCurrentDirectionX();
}

bool Centipede::getSegmentIsHead(int SegmentNum)
{
    return CentipedeSegments[SegmentNum].getIsHead();
}

bool Centipede::getSegmentIsInPlayerArea(int SegmentNum)
{
    return CentipedeSegments[SegmentNum].getIsInPlayerArea();
}



///////////////////////////////////////////////////////
//MUTATORS
///////////////////////////////////////////////////////


void Centipede::MoveX(int SegmentNum)
{
    CentipedeSegments[SegmentNum].MoveX();
}

void Centipede::MoveY(int SegmentNum)
{
    CentipedeSegments[SegmentNum].MoveY();
}

void Centipede::setSegmentDirectionY(int SegmentNum,  bool DirectionIsDown)
{
    CentipedeSegments[SegmentNum].setCurrentDirectionY(DirectionIsDown);
}

void Centipede::CentipedeShotCollision(int SegmentNum)
{
    if (CentipedeSegments.size() != 1)
    {
        CentipedeSegments[SegmentNum + 1].setHead();
    }
    CentipedeSegments.erase(CentipedeSegments.begin() + SegmentNum);
}

void Centipede::setCentipede(float _gameWidth, float _gameHeight, sf::Vector2f _CentipedeSize, int NumSegments, float CentipedeSpeed)
{
    int SegmentPos;
    CentipedeSegments.clear();
    while (CentipedeSegments.size() < NumSegments)
    {
        SegmentPos = NumSegments - CentipedeSegments.size() - 1;
        CentipedeSegment TempCentipedSeg(_gameWidth, _gameHeight, _CentipedeSize, SegmentPos, CentipedeSpeed);
        CentipedeSegments.push_back(TempCentipedSeg);
    }

}

void Centipede::setSegmentIsInPlayerArea(int SegmentNum)
{
    CentipedeSegments[SegmentNum].setInPlayerArea();
}
