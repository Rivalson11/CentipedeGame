#include "../header_files/CentipedeSegment.h"

///////////////////////////////////////////////////////
//CONSTRUCTOR AND DESTRUCTOR
///////////////////////////////////////////////////////

CentipedeSegment::CentipedeSegment(float _gameWidth, float _gameHeight, sf::Vector2f _CentipedeSize, int pos, float _CentipedeSpeed)
{
    gameWidth = _gameWidth;
    CentipedeSpeed = _CentipedeSpeed;

    //creatiopn of centipede rectangle to act as hitbox
    CentipedeRect.setSize(_CentipedeSize);
    CentipedeRect.setOrigin(_CentipedeSize/ 2.f);
    CentipedeRect.setPosition(_CentipedeSize.x/2 + (pos)*_CentipedeSize.x, _CentipedeSize.y/2);
    //CentipedeRect.setOutlineThickness(1);
    CentipedeRect.setOutlineColor(sf::Color::Red);
    CentipedeRect.setFillColor(sf::Color(100, 250, 50));

    CentipedeSize = _CentipedeSize;

    if (pos == 11)
    {
        isHead = true;//make sure creation segment on the far right is the head.
    }

    isCurrentDirectionRight = true; //true is right, false is left, set start direction
    isCurrentDirectionDown = true;// true is down, false is up
    isInPlayerArea = false;

}

CentipedeSegment::~CentipedeSegment()
{
    //dtor
}

///////////////////////////////////////////////////////
//ACCESSORS
///////////////////////////////////////////////////////

bool CentipedeSegment::getCurrentDirectionX()
{
    return isCurrentDirectionRight;
}

bool CentipedeSegment::getIsHead()
{
    return isHead;
}

sf::RectangleShape CentipedeSegment::getCentipedeRect()
{
    return CentipedeRect;
}

sf::Vector2f CentipedeSegment::getCentipedeRectCoords()
{
    return CentipedeRect.getPosition();
}

bool CentipedeSegment::getIsInPlayerArea()
{
    return isInPlayerArea;
}


///////////////////////////////////////////////////////
//MUTATORS
///////////////////////////////////////////////////////

void CentipedeSegment::setCurrentDirectionY(bool DirectionIsDown)
{
    isCurrentDirectionDown = DirectionIsDown;//up
}

void CentipedeSegment::setCurrentDirectionX()//Changes each time Y level changes
{
    if (isCurrentDirectionRight)
    {
        isCurrentDirectionRight = false;//left
    }
    else
    {
        isCurrentDirectionRight = true;//right
    }
}

void CentipedeSegment::MoveX()
{
    if (isCurrentDirectionRight)
    {
        CentipedeRect.move(CentipedeSpeed, 0.f);
    }
    else
    {
        CentipedeRect.move(-CentipedeSpeed, 0.f);
    }

}

void CentipedeSegment::MoveY()
{
    if (isCurrentDirectionDown)
    {
        CentipedeRect.move(0.f, CentipedeSize.y);
    }
    else
    {
        CentipedeRect.move(0.f, -CentipedeSize.y);
    }
    setCurrentDirectionX();
}


void CentipedeSegment::CentipedeSegment::setHead()
{
    isHead = true;
}

void CentipedeSegment::setInPlayerArea()
{
    isInPlayerArea = true;
}


