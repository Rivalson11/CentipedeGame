#include "TestClass.h"

/////////////////////////////////////////////////////////////
//CONSTRUCTOR AND DESTRUCTOR
/////////////////////////////////////////////////////////////

TestClass::TestClass():
PlayerObject(gameWidth, gameHeight, Standby, PlayerSpeed),//Player constructor
CentipedeObject(gameWidth, gameHeight, CentipedeSize, CentipedeStartSegments, CentipedeSpeed),//Centipede constructor with 12 segments, speed gets changed upon difficulty selection
MushroomFieldObject(gameWidth, gameHeight, MushroomSize, 1),//spawn chance gets changed upon difficulty selection
DDTFieldObject()
{

    MushroomFieldObject.ClearMushroomField();
}

TestClass::~TestClass()
{

}


/////////////////////////////////////////////////////////////
//ACCESSORS
/////////////////////////////////////////////////////////////
//positional returns
sf::Vector2f TestClass::getPlayerPosition()
{
    return PlayerObject.getCoords();
}

sf::Vector2f TestClass::getCentipedePosition()
{
    return CentipedeObject.getSegmentCoords(0);
}

sf::Vector2f TestClass::getShootPosition()
{
    return ShotsVector[0].getCoords();
}

sf::Vector2f TestClass::getMushroomPosition()
{
    return MushroomFieldObject.getMushroomCoords(0);
}

sf::Vector2f TestClass::getSpiderPosition()
{
    return SpiderVector[0].getCoords();
}

sf::Vector2f TestClass::getFleaPosition()
{
    return FleaVector[0].getCoords();
}

sf::Vector2f TestClass::getDDTPosition()
{
    return DDTFieldObject.getRectCoords(0);
}

bool TestClass::getCentipeDirectionIsRight()
{
    return CentipedeObject.getSegmentCurrentDirectionX(0);
}

//Shoot interactions
bool TestClass::CentipedeIsEmpty()
{
    if (CentipedeObject.getCentipede().empty())
    {
        return true;
    }
    else return false;
}

bool TestClass::spiderIsEmpty()
{
    if (SpiderVector.empty())
    {
        return true;
    }
    else return false;
}

bool TestClass::FleaIsEmpty()
{
    if (FleaVector.empty())
    {
        return true;
    }
    else return false;
}

bool TestClass::MushroomIsEmpty()
{
    if (MushroomFieldObject.getMushroomField().empty())
    {
        return true;
    }
    else return false;
}

int TestClass::getnumMushrooms()
{
    return MushroomFieldObject.getMushroomField().size();
}

int TestClass::getMushroomHealth()
{
    return MushroomFieldObject.getMushroomHealth(0);
}

int TestClass::getPlayerHealth()
{
    return PlayerObject.getLives();
}

bool TestClass::DDTIsShot()
{
    if (DDTFieldObject.getDDTField().empty())
    {
        return true;
    }
    else return false;
}

//random events
bool TestClass::MushroomIsEaten()
{
    if (MushroomFieldObject.getMushroomField().empty())
    {
        return true;
    }
    else return false;
}

bool TestClass::DDTIsSpawned()
{
    if (!DDTFieldObject.getDDTField().empty())
    {
        return true;
    }
    else return false;
}

/////////////////////////////////////////////////////////////
//MUTATORS
/////////////////////////////////////////////////////////////

void TestClass::clearMushrooms()
{
    MushroomFieldObject.ClearMushroomField();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//GAME SPAWNERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//FLEA SPAWN
//////////////////////////////////////////////////////////////

void TestClass::FleaSpawn(sf::Vector2f SpawnPos)
{
    Flea FleaObject(SpawnPos.x, FleaSize, FleaSpeed);//construct flea object at random x position
    FleaVector.push_back(FleaObject);//make copy in vector, made as a vector in the case you want to have multiple flea objects active at the same time i.e very low flea spawn time
}

//////////////////////////////////////////////////////////////
//SPIDER SPAWN
//////////////////////////////////////////////////////////////

void TestClass::SpiderSpawn()
{
    Spider SpiderObject(PlayerCeiling, SpiderSize, SpiderSpeed);//construct Spider object at top of player ceiling area
    SpiderVector.push_back(SpiderObject);//make copy in vector, made as a vector in the case you want to have multiple flea objects active at the same time i.e very low flea spawn time
    SpiderSpawnClock.restart();
}

//////////////////////////////////////////////////////////////
//DDT SPAWN
//////////////////////////////////////////////////////////////

void TestClass::DDTSpawn()
{
    DDTFieldObject.SpawnDDT(gameWidth, PlayerCeiling, DDTSize);
}

void TestClass::ShootSpawn(sf::Vector2f spawnPos)
{//SHOOTING: CREATION OF SHOOT OBJECTS AND POPULATION OF SHOOT VECTOR
    PlayerObject.setPlayerSize(Shooting);
    Shoot ShootObject(spawnPos, ShootSize, ShootSpeed);//construct shoot object
    ShotsVector.push_back(ShootObject);//make copy in vector
}

void TestClass::MushroomSpawner(sf::Vector2f spawnPos)
{//SHOOTING: CREATION OF SHOOT OBJECTS AND POPULATION OF SHOOT VECTOR
    MushroomFieldObject.SpawnMushroom(spawnPos, true, MushroomSize);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//GAME OBJECT MOVEMENT
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//PLAYER MOVEMENT CONTROLS
//////////////////////////////////////////////////////////////

void TestClass::PlayerControls(std::string Direction)
{
    sf::Sprite PlayerSprite;
        if (Direction == "up")
        {
            PlayerObject.setPlayerSize(Up);
            if (PlayerObject.getCoords().y > PlayerCeiling )//Player area ristricted vertically
            {
                PlayerObject.MoveUp();
            }
        }
        else //STANDBY
        {
            PlayerObject.setPlayerSize(Standby);
        }

        //DOWN MOVEMENT
        if (Direction == "down")
        {
            PlayerObject.setPlayerSize(Down);
            if (PlayerObject.getCoords().y < gameHeight - Down.y / 2)
            {
                PlayerObject.MoveDown();
            }
        }

        //LEFT MOVEMENT
        if (Direction == "left")
        {
            PlayerObject.setPlayerSize(Left);
            if (PlayerObject.getCoords().x > Left.x / 2)
            {
                PlayerObject.MoveLeft();
            }
        }

        //RIGHT MOVEMENT
        if (Direction == "right")
        {
            PlayerObject.setPlayerSize(Right - sf::Vector2f(30, 0));//additional hitbox size change to accommodate irregular sprite shape by decreasing sprite size values
            if (PlayerObject.getCoords().x  < gameWidth - Right.x / 2)
            {
                PlayerObject.MoveRight();
            }
        }

}



//////////////////////////////////////////////////////////////
//SHOOT MOVEMENT
//////////////////////////////////////////////////////////////

void TestClass::ShootMovement()
{
    if (!ShotsVector.empty())
    {
        for (int ShootNum = 0; ShootNum < ShotsVector.size(); ShootNum++)
        {

            ShotsVector[ShootNum].Move();
            //!CENTIPEDE AND SHOOT COLLISION
            if (CentipedeShootCollisionCheck(ShootNum))
            {
                ShotsVector.erase(ShotsVector.begin() + ShootNum);
            }

            if (ShotsVector[ShootNum].getCoords().y <= -20 )//sets boundary for deletion of missed shots, set to slightly above top to remove bug that occured
            {
                ShotsVector.erase(ShotsVector.begin() + ShootNum);
            }
        }
    }
}

//////////////////////////////////////////////////////////////
//CENTIPEDE MOVEMENT X DIRECTION
//////////////////////////////////////////////////////////////

void TestClass::CentipedeMovementX()
{
    for (int SegmentNum = 0; SegmentNum < CentipedeObject.getCentipede().size(); SegmentNum++)//Move head first
    {
        if ((CentipedeObject.getSegmentCoords(SegmentNum).x  >= gameWidth - CentipedeSize.x / 2) || (CentipedeObject.getSegmentCoords(SegmentNum).x <= CentipedeSize.x / 2) && (CentipedeObject.getSegmentCoords(SegmentNum).y != CentipedeSize.y / 2))//right and left boundary collision check
        {
            CentipedeMovementY(SegmentNum);//Move in the Y Direction in the case Boundary is hit.
        }

        CentipedeObject.MoveX(SegmentNum);


        //CENTIPEDE AND PLAYER COLLISION CHECK
        if  (CentipedeObject.getSegmentRect(SegmentNum).getGlobalBounds().intersects(PlayerObject.getPlayerRect().getGlobalBounds()))//check collision
        {
            LoseLife();
            break;
        }
    }

}

//////////////////////////////////////////////////////////////
//CENTIPEDE MOVEMENT Y DIRECTION
//////////////////////////////////////////////////////////////

void TestClass::CentipedeMovementY(int SegmentNum)
{
    CentipedeObject.MoveY(SegmentNum);//when it moves on y axis it changes player x direction
    if (CentipedeObject.getSegmentIsInPlayerArea(SegmentNum))//Makes sure centipede stays in player section
    {
        if (CentipedeObject.getSegmentCoords(SegmentNum).y >= gameHeight - CentipedeSize.y/2)
        {
            CentipedeObject.setSegmentDirectionY(SegmentNum, false);//set direction to go up
        }

        if (CentipedeObject.getSegmentCoords(SegmentNum).y <= PlayerCeiling)
        {
            CentipedeObject.setSegmentDirectionY(SegmentNum, true); //set direction to go down
        }
    }
    else
    {
        if (CentipedeObject.getSegmentCoords(SegmentNum).y >= PlayerCeiling)
        {
            CentipedeObject.setSegmentIsInPlayerArea(SegmentNum);
        }
    }

}

//////////////////////////////////////////////////////////////
//FLEA MOVEMENT
//////////////////////////////////////////////////////////////

void TestClass::FleaMovement()
{
    sf::RectangleShape MushroomRectSpawnTest;
    MushroomRectSpawnTest.setSize(FleaSize);//subtract to make more reasonable sized hitbox
    MushroomRectSpawnTest.setOrigin(FleaSize / 2.f);

    for (int FleaNum = 0; FleaNum < FleaVector.size(); FleaNum++)
    {
        //FLEA AND SHOOT COLLISION
        FleaShootCollisionCheck(FleaNum);

        bool isNotInCentipede = true;
        FleaVector[FleaNum].MoveDown();
        if (FleaVector[FleaNum].getCoords().y > gameHeight + FleaSize.y/2)//destroy object as it leaves player screen
        {
            FleaVector.erase(FleaVector.begin() + FleaNum);
        }

        //MUSHROOM SPAWNING
        if (FleaVector[FleaNum].getCoords().y < PlayerCeiling + 6*MushroomSize.y &&
            MushroomFieldObject.getMushroomField().size() < ((gameHeight*gameWidth)/(MushroomSize.x*MushroomSize.x)/8)&&
            FleaVector[FleaNum].getCoords().y > FleaSize.y) //flea spawns mushrooms if less than an 8th of the map has mushrooms and not in near bottom or top boundry of screen
        {
            for (int CentipedeNum = 0; CentipedeNum < CentipedeObject.getCentipede().size(); CentipedeNum++)
            {
                MushroomRectSpawnTest.setPosition(FleaMushroomSpawnY(FleaNum));
                if (MushroomRectSpawnTest.getGlobalBounds().intersects(CentipedeObject.getSegmentRect(CentipedeNum).getGlobalBounds()))//wont spawn mushroom inside centipede
                {
                    isNotInCentipede = false;//If flea is inside centipede region a mushroom will not spawn
                }
            }

            if (rand() % FleaMushroomSpawn == 0 && isNotInCentipede) //Chance Flea spawns mushroom at its location, is chance it spawns 2 mushrooms in the same location
            {
                MushroomFieldObject.SpawnMushroom(FleaMushroomSpawnY(FleaNum), true, MushroomSize);
            }
        }

    }
}

//////////////////////////////////////////////////////////////
//SPIDER MOVEMENT
//////////////////////////////////////////////////////////////

/*void TestClass::SpiderMovement()
{
    sf::Sprite SpiderSprite;

    for (int SpiderNum = 0; SpiderNum < SpiderVector.size(); SpiderNum++)
    {
        //!SPIDER AND SHOOT COLLISION
        SpiderShootCollisionCheck(SpiderNum);


        int CurrentDirection = SpiderVector[SpiderNum].getCurrentDirection();
        if (SpiderVector[SpiderNum].getCoords().x <= 0 + SpiderSize.y/2)
        {
            CurrentDirection = 1;
        }
        if (SpiderVector[SpiderNum].getCoords().x >= gameWidth - SpiderSize.y/2)
        {
            CurrentDirection = 0;
        }
        if (SpiderVector[SpiderNum].getCoords().y <= PlayerCeiling - SpiderSize.y)//spider moves in same x direction bouncing of upper boundary and changing diagonal movement
        {
            if (SpiderVector[SpiderNum].getCurrentDirection() == 5 || SpiderVector[SpiderNum].getCurrentDirection() == 0) //upper right diag
            {
                CurrentDirection = 3;
            }
            else//6 upper left diag
            {
                CurrentDirection = 2;
            }
        }
        if (SpiderVector[SpiderNum].getCoords().y >= gameHeight - SpiderSize.y/2)//spider moves in same x direction bouncing of bottom boundary and changing diagonal movement
        {
            if (SpiderVector[SpiderNum].getCurrentDirection() == 2 || SpiderVector[SpiderNum].getCurrentDirection() == 1) //bottom right diag
            {
                CurrentDirection = 4;
            }
            else//4 bottom left diag
            {
                CurrentDirection = 5;
            }
        }
        SpiderVector[SpiderNum].setCurrentDirection(CurrentDirection);
        SpiderVector[SpiderNum].SpiderRandomMovement();

        //SPIDER COLLISIONS
        SpiderMushroomCollisionCheck(SpiderNum);
        SpiderPlayerCollisionCheck(SpiderNum);

    }

}*/

void TestClass::SpiderMovement(int Direction)
{
    int CurrentDirection;
    for (int SpiderNum = 0; SpiderNum < SpiderVector.size(); SpiderNum++)
    {
        //!SPIDER AND SHOOT COLLISION
        SpiderShootCollisionCheck(SpiderNum);

        switch (Direction)
        {
        case 1:
            {
                CurrentDirection = 0;//up
                break;
            }

        case 2:
            {
                CurrentDirection = 1;//down
                break;
            }

        case 3:
            {
                CurrentDirection = 3;//bottom Left diag Move
                break;
            }

        case 4:
            {
                CurrentDirection = 2;//bottom right diag Move
                break;
            }

        case 5:
            {
                CurrentDirection = 4;//Upper right diag Move
                break;
            }

        case 6:
            {
                CurrentDirection = 5;//Upper Left diag Move
                break;
            }
        }
        SpiderVector[SpiderNum].setCurrentDirection(CurrentDirection);
        SpiderVector[SpiderNum].SpiderRandomMovement();

        //SPIDER COLLISIONS
        SpiderMushroomCollisionCheck(SpiderNum);
        SpiderPlayerCollisionCheck(SpiderNum);

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//GAME COLLISIONS CALLS TO COLLISIONS ARE DONE WITHIN THEIR RESPECTIVE MOVEMENT FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//DDT BOMB COLLISIONS AS WELL AS DDT BOMB DISPLAY
//////////////////////////////////////////////////////////////

void TestClass::DDTCollisionChecks()
{
    int numDDTExploded = 0; //used to reset clock timer
    for (int DDTNum = 0; DDTNum < DDTFieldObject.getDDTField().size(); DDTNum++)
    {

        //!DDT AND SHOOT COLLISION
        ShootDDTCollisionCheck(DDTNum);

        if (DDTFieldObject.getDDTIsExploded(DDTNum))
        {
            numDDTExploded++;

            //MUSHROOM IN EXPLOSION
            for (int MushroomNum = 0; MushroomNum < MushroomFieldObject.getMushroomField().size(); MushroomNum++)
            {
                if (DDTFieldObject.getDDTBlock(DDTNum).getGlobalBounds().intersects(MushroomFieldObject.getMushroomBlock(MushroomNum).getGlobalBounds()))
                {
                    MushroomFieldObject.DestroyMushroom(MushroomNum);
                    oldscore = score;
                    score = score + MushroomPoints;
                    NewLife();
                }
            }

            //CENTIPEDE IN EXPLOSION
            for (int CentipedeSegment = 0; CentipedeSegment < CentipedeObject.getCentipede().size(); CentipedeSegment++)
            {
                if  (DDTFieldObject.getDDTBlock(DDTNum).getGlobalBounds().intersects(CentipedeObject.getSegmentRect(CentipedeSegment).getGlobalBounds()))
                {
                    oldscore = score;
                    if (CentipedeObject.getSegmentIsHead(CentipedeSegment))
                    {
                        score = score + headshot;//head collision
                    }
                    else
                    {
                        score = score + bodyshot;//body collision
                    }
                    NewLife();
                    CentipedeObject.CentipedeShotCollision(CentipedeSegment);//destroy segment
                }
            }

            //SPIDER IN EXPLOSION
            for (int SpiderNum = 0; SpiderNum < SpiderVector.size(); SpiderNum++)
            {
                if (DDTFieldObject.getDDTBlock(DDTNum).getGlobalBounds().intersects(SpiderVector[SpiderNum].getSpiderRect().getGlobalBounds()))
                {
                    SpiderVector.erase(SpiderVector.begin() + SpiderNum);
                    oldscore = score;
                    score = score + SpiderPoints;
                    NewLife();
                }
            }

            //FLEA IN EXPLOSION
            for (int FleaNum = 0; FleaNum < FleaVector.size(); FleaNum++)
            {
                if (DDTFieldObject.getDDTBlock(DDTNum).getGlobalBounds().intersects(FleaVector[FleaNum].getFleaRect().getGlobalBounds()))
                {
                    FleaVector.erase(FleaVector.begin() + FleaNum);
                    oldscore = score;
                    score = score + FleaPoints;
                    NewLife();
                }
            }
        }
        else
        {

        }

        if ((DDTFieldObject.getDDTIsExploded(DDTNum)) && (DDTExplosionClock.getElapsedTime().asSeconds() - DDTFieldObject.getDDTExplodedTime(DDTNum).asSeconds() > 0.6))//explosion remains for 1 second destroying all objects that enter it
        {
            DDTFieldObject.DestroyDDT(DDTNum);//after explosion DDt is removed
        }
    }

    if (numDDTExploded == 0)
    {
        DDTExplosionClock.restart();// reset clock so it never increases indefinetly
    }
}


//////////////////////////////////////////////////////////////
//MUSHROOM CENTIPEDE COLLISIONS AS WELL AS MUSHROOM DISPLAY
//////////////////////////////////////////////////////////////

void TestClass::MushroomCollisionChecks()
{
    for (int MushroomNum = 0; MushroomNum < MushroomFieldObject.getMushroomField().size(); MushroomNum++)
    {
        //CENTIPEDE AND MUSHROOM COLLISION
        for (int SegmentNum = 0; SegmentNum < CentipedeObject.getCentipede().size(); SegmentNum++)
        {
            if (CentipedeObject.getSegmentCurrentDirectionX(SegmentNum))
            {
                //Check intersection between side wall of centipede and mushroom based on centipede direction,
                //implemented to accomodate for spawning spawning of mushrooms when centipede is shot at odd spawn sites.
                if  ((CentipedeObject.getSegmentCoords(SegmentNum).y == (MushroomFieldObject.getMushroomCoords(MushroomNum).y)) &&
                     (CentipedeObject.getSegmentCoords(SegmentNum).x + CentipedeSize.x/2 >= MushroomFieldObject.getMushroomCoords(MushroomNum).x - MushroomSize.x/2  )&&
                     (CentipedeObject.getSegmentCoords(SegmentNum).x + CentipedeSize.x/2 <= MushroomFieldObject.getMushroomCoords(MushroomNum).x + MushroomSize.x/2))
                {
                    CentipedeMovementY(SegmentNum);
                }
            }
            else
            {
                if  ((CentipedeObject.getSegmentCoords(SegmentNum).y == (MushroomFieldObject.getMushroomCoords(MushroomNum).y)) &&
                     (CentipedeObject.getSegmentCoords(SegmentNum).x - CentipedeSize.x/2 <= MushroomFieldObject.getMushroomCoords(MushroomNum).x + MushroomSize.x/2  )&&
                     (CentipedeObject.getSegmentCoords(SegmentNum).x - CentipedeSize.x/2 >= MushroomFieldObject.getMushroomCoords(MushroomNum).x - MushroomSize.x/2))
                {
                    CentipedeMovementY(SegmentNum);
                }
            }
        }

        //MUSHROOM AND SHOOT COLLISION
        ShootMushroomCollisionCheck(MushroomNum);


    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//THE FOLLOWING COLLISION FUNCTIONS ARE FUNCTIONS CALLED WITHIN THE SHOOT MOVEMENT FUNCTION ABOVE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//SHOOT WITH DDT COLLISION
//////////////////////////////////////////////////////////////
void TestClass::ShootDDTCollisionCheck(int DDTNum)
{
    for (int ShootNum = 0; ShootNum < ShotsVector.size(); ShootNum++)
    {
        if (ShotsVector[ShootNum].getShootRect().getGlobalBounds().intersects(DDTFieldObject.getDDTBlock(DDTNum).getGlobalBounds()) &&
            !DDTFieldObject.getDDTIsExploded(DDTNum))//hit a DDT bomb that hasnt exploded yet
        {
            DDTFieldObject.setDDTExplosion(DDTExplosionRange, DDTNum, DDTExplosionClock.getElapsedTime());
            ShotsVector.erase(ShotsVector.begin() + ShootNum);
            break;
        }
    }
}

//////////////////////////////////////////////////////////////
//SHOOT WITH MUSHROOM COLLISION
//////////////////////////////////////////////////////////////

void TestClass::ShootMushroomCollisionCheck(int MushroomNum)
{
    for (int ShootNum = 0; ShootNum < ShotsVector.size(); ShootNum++)
    {
        if (ShotsVector[ShootNum].getShootRect().getGlobalBounds().intersects(MushroomFieldObject.getMushroomBlock(MushroomNum).getGlobalBounds()))
        {
            ShotsVector.erase(ShotsVector.begin() + ShootNum); //destructs shot object inside shoot vector and frees up memory
            MushroomFieldObject.setMushroomHealth(MushroomNum);
            if (MushroomFieldObject.getMushroomHealth(MushroomNum) == 0)
            {
                MushroomFieldObject.DestroyMushroom(MushroomNum);
                oldscore = score;
                score = score + MushroomPoints;
                NewLife();
            }
            break;
        }
    }
}

//////////////////////////////////////////////////////////////
//SHOOT WITH CENTIPEDE COLLISION
//////////////////////////////////////////////////////////////

bool TestClass::CentipedeShootCollisionCheck(int ShootNum)
{
    bool collisionDetected = false;
    for (int CentipedeSegment = 0; CentipedeSegment < CentipedeObject.getCentipede().size(); CentipedeSegment++)//check if it collides with any of the segments of the centipede
    {
        if  (ShotsVector[ShootNum].getShootRect().getGlobalBounds().intersects(CentipedeObject.getSegmentRect(CentipedeSegment).getGlobalBounds()))
        {
            //detsroys all centipede parts even if overlayed
            oldscore = score;
            if (CentipedeObject.getSegmentIsHead(CentipedeSegment))
            {
                score = score + headshot;//head collision
            }
            else
            {
                score = score + bodyshot;//body collision
            }
            NewLife();
            MushroomFieldObject.SpawnMushroom(CentipedeObject.getSegmentCoords(CentipedeSegment), CentipedeObject.getSegmentCurrentDirectionX(CentipedeSegment), MushroomSize); //spawn Mushroom
            //ShotsVector.erase(ShotsVector.begin() + ShootNum); //destructs shot object inside shoot vector and frees up memory
            CentipedeObject.CentipedeShotCollision(CentipedeSegment);//destroy segment
            collisionDetected = true;
        }

    }
    return collisionDetected;
}

//////////////////////////////////////////////////////////////
//SHOOT WITH FLEA COLLISION
//////////////////////////////////////////////////////////////

void TestClass::FleaShootCollisionCheck(int FleaNum)
{
    for (int ShootNum = 0; ShootNum < ShotsVector.size(); ShootNum++)
    {
        if (ShotsVector[ShootNum].getShootRect().getGlobalBounds().intersects(FleaVector[FleaNum].getFleaRect().getGlobalBounds()))
        {
            FleaVector.erase(FleaVector.begin() + FleaNum);
            ShotsVector.erase(ShotsVector.begin() + ShootNum);
            oldscore = score;
            score = score + FleaPoints;
            NewLife();
            break;
        }
    }
}

//////////////////////////////////////////////////////////////
//SHOOT WITH SPIDER COLLISION
//////////////////////////////////////////////////////////////

void TestClass::SpiderShootCollisionCheck(int SpiderNum)
{
    for (int ShootNum = 0; ShootNum < ShotsVector.size(); ShootNum++)
    {
        if (ShotsVector[ShootNum].getShootRect().getGlobalBounds().intersects(SpiderVector[SpiderNum].getSpiderRect().getGlobalBounds()))
        {
            SpiderVector.erase(SpiderVector.begin() + SpiderNum);
            ShotsVector.erase(ShotsVector.begin() + ShootNum);
            oldscore = score;
            score = score + SpiderPoints;
            NewLife();
            break;
        }
    }
}

//////////////////////////////////////////////////////////////
//SPIDER AND PLAYER COLLISION
//////////////////////////////////////////////////////////////

void TestClass::SpiderPlayerCollisionCheck(int SpiderNum)
{
    if  (SpiderVector[SpiderNum].getSpiderRect().getGlobalBounds().intersects(PlayerObject.getPlayerRect().getGlobalBounds()))
    {
        LoseLife();
    }
}

//////////////////////////////////////////////////////////////
//SPIDER AND MUSHROOM COLLISION
//////////////////////////////////////////////////////////////
void TestClass::SpiderMushroomCollisionCheck(int SpiderNum)
{
    for (int MushroomNum = 0; MushroomNum < MushroomFieldObject.getMushroomField().size(); MushroomNum++)
    {
        if (SpiderVector[SpiderNum].getSpiderRect().getGlobalBounds().intersects(MushroomFieldObject.getMushroomBlock(MushroomNum).getGlobalBounds()))//check collision
        {
            if (rand() % SpiderEatChance == 0)//Spider occassionally eats mushroom
            {
                MushroomFieldObject.DestroyMushroom(MushroomNum);//destroy that mushroom
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//GAME MANAGEMENT FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//WON GAME CHECK
//////////////////////////////////////////////////////////////

bool TestClass::WonCheck()
{
   if(CentipedeObject.getCentipede().empty())
    {
        highscore.push_back(score);
        ShotsVector.clear();
        FleaVector.clear();
        SpiderVector.clear();
        return false;
    }
    else
    {
        return true;
    }
}

//////////////////////////////////////////////////////////////
//LOST GAME CHECK
//////////////////////////////////////////////////////////////

bool TestClass::LostCheck()
{
    if(PlayerObject.getLives() == 0)
    {
        highscore.push_back(score);
        CentipedeObject.getCentipede().clear();
        ShotsVector.clear();
        FleaVector.clear();
        SpiderVector.clear();
        return false;
    }
    else
    {
        return true;
    }
}

//////////////////////////////////////////////////////////////
//GAIN LIFE FUNCTION
//////////////////////////////////////////////////////////////

void TestClass::NewLife()//new life granted for every 12000 points
{
    int multiple = oldscore / 12000;
    if (oldscore < 12000 +(12000 * multiple) && score >= 12000+(12000*multiple))
    {
        PlayerObject.setLives(PlayerObject.getLives() + 1);
    }
}

//////////////////////////////////////////////////////////////
//LOSE LIFE
//////////////////////////////////////////////////////////////

void TestClass::LoseLife()
{
    PlayerObject.setLives(PlayerObject.getLives() - 1);
    PlayerObject.resetPlayerPosition(gameWidth, gameHeight);
    CentipedeObject.setCentipede(gameWidth, gameHeight, CentipedeSize, CentipedeStartSegments, CentipedeSpeed);
    MushroomFieldObject.setMushroomField(gameWidth, gameHeight, CentipedeSize, MushroomSpawnChance);
    ShotsVector.clear();
    SpiderVector.clear();
    FleaVector.clear();
    SpiderSpawnClock.restart();
    FleaSpawnClock.restart();
    DDTSpawnClock.restart();
    DDTExplosionClock.restart();
    reloadClock.restart();
}


//////////////////////////////////////////////////////////////
//FLEA MUSHROOM SPAWN Y LOCATION
//////////////////////////////////////////////////////////////

sf::Vector2f TestClass::FleaMushroomSpawnY(int FleaNum)
{
    float intPart;
    float fracPart;
    fracPart = modf(FleaVector[FleaNum].getCoords().y/MushroomSize.y, &intPart);
    intPart = intPart * MushroomSize.y  + MushroomSize.y/2;

    if (fracPart*MushroomSize.y >= MushroomSize.y/2)
    {
        intPart = intPart + MushroomSize.y ; //rounds flea mushroom y position spawn to the nearest theoretical grid position
    }
    return sf::Vector2f(FleaVector[FleaNum].getCoords().x - MushroomSize.x, intPart);//mushroom spawns based of centipede movement direction
    //so to create the correct collision, therefore a shift of mushroom size in x direction is used to rectify this.
}
