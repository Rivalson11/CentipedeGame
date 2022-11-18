#include "..\header_files\Spider.h"

///////////////////////////////////////////////////////
//CONSTRUCTOR AND DESTRUCTOR
///////////////////////////////////////////////////////

Spider::Spider(float _SpawnY, sf::Vector2f _SpiderSize, float _SpiderSpeed)
{
    SpiderSpeed = _SpiderSpeed;
    CurrentDirection = 2; //bottom right
    //ctor
    SpiderRect.setSize(_SpiderSize);
    SpiderRect.setOrigin(_SpiderSize / 2.f);
    SpiderRect.setPosition(0 + _SpiderSize.x/2 , _SpawnY);//spawns near top of player celeing
    //SpiderRect.setOutlineColor(sf::Color::Blue);
    //SpiderRect.setFillColor(sf::Color(100, 100, 200));
}

Spider::~Spider()
{
    //dtor
}


///////////////////////////////////////////////////////
//ACCESSORS
///////////////////////////////////////////////////////
sf::Vector2f Spider::getCoords()
{
    return SpiderRect.getPosition();
}

sf::RectangleShape Spider::getSpiderRect()
{
    return SpiderRect;
}

int Spider::getCurrentDirection()
{
    return CurrentDirection;
}


//////////////////////////////////////////////////////////////
//MUTATORS
//////////////////////////////////////////////////////////////
void Spider::MoveRight()
{
    SpiderRect.move(SpiderSpeed, 0.f);
}

void Spider::MoveLeft()
{
    SpiderRect.move(-SpiderSpeed, 0.f);
}

void Spider::MoveUp()
{
    SpiderRect.move(0.f, - SpiderSpeed);
}

void Spider::MoveDown()
{
    SpiderRect.move(0.f, SpiderSpeed);
}

void Spider::setCurrentDirection(int MovementType)
{
    CurrentDirection = MovementType;
}

void Spider::SpiderRandomMovement()//0 is down, 1 is up, 2 is bottom right diag, 3 is bottom left diag, 4 is upper right diag, 5 is upper left diag
{
    switch (CurrentDirection) // 6 movement options
    {
        case 0://Up Move
            {
                MoveUp();
                break;
            }
        case 1://down Move
            {
                MoveDown();
                break;
            }
        case 2://bottom right diag Move
            {
                MoveDown();
                MoveRight();
                break;
            }
        case 3://bottom Left diag Move
            {
                MoveDown();
                MoveLeft();
                break;
            }
        case 4://Upper right diag Move
            {
                MoveUp();
                MoveRight();
                break;
            }
        case 5://Upper Left diag Move
            {
                MoveUp();
                MoveLeft();
                break;
            }
    }
}
