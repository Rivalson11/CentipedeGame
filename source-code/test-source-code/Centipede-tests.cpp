#include "TestClass.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <tuple>
#include <iostream>
#include <unistd.h>

///////////////////////////////////////////////////////
//GAME SPAWNS
///////////////////////////////////////////////////////

TEST_CASE("Flea Spawn")
{
    TestClass TestObject;
    TestObject.SpiderSpawn();
    CHECK_FALSE(TestObject.spiderIsEmpty());
}

TEST_CASE("Spider Spawn")
{
    TestClass TestObject;
    TestObject.FleaSpawn(sf::Vector2f(gameWidth/2, 0));//spawns top of screen in the mid  of x plane
    CHECK_FALSE(TestObject.FleaIsEmpty());
}

TEST_CASE("Mushroom Spawn")
{
    TestClass TestObject;
    TestObject.MushroomSpawner(sf::Vector2f(0,0));//spawns top of screen in the mid  of x plane
    CHECK_FALSE(TestObject.MushroomIsEmpty());
}


TEST_CASE("testing DDT spawn")
{
    TestClass TestObject;
    TestObject.DDTSpawn();
    CHECK(TestObject.DDTIsSpawned());
}


///////////////////////////////////////////////////////
//GAME OBJECTS MOVEMENT TESTS
///////////////////////////////////////////////////////

//PLAYER MOVEMENTS
TEST_CASE("testing Player left move")
{
    TestClass TestObject;
    TestObject.PlayerControls("left");
    CHECK(TestObject.getPlayerPosition() == sf::Vector2f(gameWidth / 2 - PlayerSpeed, gameHeight - Standby.y/2));//Moves from starting position playerspeed amount to the left
}
TEST_CASE("testing Player right move")
{
    TestClass TestObject;
    TestObject.PlayerControls("right");
    CHECK(TestObject.getPlayerPosition() == sf::Vector2f(gameWidth / 2 + PlayerSpeed, gameHeight - Standby.y/2));//Moves from starting position playerspeed amount to the right
}
TEST_CASE("testing Player up move")
{
    TestClass TestObject;
    TestObject.PlayerControls("up");
    CHECK(TestObject.getPlayerPosition() == sf::Vector2f(gameWidth / 2, gameHeight - Standby.y/2 - PlayerSpeed));//Moves from starting position playerspeed amount up
}
TEST_CASE("testing Player down move")
{
    TestClass TestObject;
    TestObject.PlayerControls("up");
    TestObject.PlayerControls("down");
    CHECK(TestObject.getPlayerPosition() == sf::Vector2f(gameWidth / 2, gameHeight - Standby.y/2));//Moves from starting position moves up and down resulting in original position
}

//SHOOT MOVEMENT
TEST_CASE("testing shoot up movement")
{
    TestClass TestObject;
    TestObject.ShootSpawn(sf::Vector2f(gameWidth / 2, gameHeight - Standby.y/2));
    TestObject.ShootMovement();
    CHECK(TestObject.getShootPosition() == sf::Vector2f(gameWidth / 2, gameHeight - Standby.y/2 - ShootSpeed));//moves from starting position shoot speed distance up
}

//CENTIPEDE MOVEMENT
TEST_CASE("testing Centipede right movement")
{
    TestClass TestObject;
    sf::Vector2f originalPosition = TestObject.getCentipedePosition();
    TestObject.CentipedeMovementX();
    CHECK(TestObject.getCentipedePosition() == originalPosition + sf::Vector2f(CentipedeSpeed,0));
}
TEST_CASE("testing Centipede left movement")
{
    TestClass TestObject;
    TestObject.CentipedeMovementX(); //move it one block right to avoid left wall collision
    TestObject.CentipedeMovementY(0); //changes direction in x plane to move left
    sf::Vector2f originalPosition = TestObject.getCentipedePosition();
    TestObject.CentipedeMovementX();//moves left now as it moved one down
    CHECK(TestObject.getCentipedePosition() == originalPosition - sf::Vector2f(CentipedeSpeed,0));
}

TEST_CASE("testing Centipede down movement")
{
    TestClass TestObject;
    sf::Vector2f originalPosition = TestObject.getCentipedePosition();
    TestObject.CentipedeMovementY(0); //changes direction in x plane to move left
    CHECK(TestObject.getCentipedePosition() == originalPosition + sf::Vector2f(0,CentipedeSize.y));//Centipede drops a full body length when its moves down
}

TEST_CASE("testing Centipede up movement")
{
    //in order for the centipede to move up it must reach the bottom of the game screen (this counts as a bottom boundary collision
    TestClass TestObject;
    for (int loop = 0; loop < gameHeight/CentipedeSize.y - 1; loop++)
    {
        TestObject.CentipedeMovementY(0);
    }
    sf::Vector2f originalPosition = TestObject.getCentipedePosition(); //should be on bottom boundary
    TestObject.CentipedeMovementY(0); //should move up now
    CHECK(TestObject.getCentipedePosition() == originalPosition - sf::Vector2f(0,CentipedeSize.y));//should move up one body size
}

//SPIDER MOVEMENT
TEST_CASE("testing Spider up movement")
{
    TestClass TestObject;
    TestObject.SpiderSpawn();
    sf::Vector2f originalPosition = TestObject.getSpiderPosition();
    TestObject.SpiderMovement(1);//1 is up
    CHECK(TestObject.getSpiderPosition() == originalPosition - sf::Vector2f(0, SpiderSpeed));
}

TEST_CASE("testing Spider down movement")
{
    TestClass TestObject;
    TestObject.SpiderSpawn();
    sf::Vector2f originalPosition = TestObject.getSpiderPosition();
    TestObject.SpiderMovement(2);//2 is down
    CHECK(TestObject.getSpiderPosition() == originalPosition + sf::Vector2f(0, SpiderSpeed));
}

TEST_CASE("testing Spider up_right movement")
{
    TestClass TestObject;
    TestObject.SpiderSpawn();
    sf::Vector2f originalPosition = TestObject.getSpiderPosition();
    TestObject.SpiderMovement(5);//Upper right diag Move
    CHECK(TestObject.getSpiderPosition() == originalPosition + sf::Vector2f(SpiderSpeed, -SpiderSpeed));
}

TEST_CASE("testing Spider up_left movement")
{
    TestClass TestObject;
    TestObject.SpiderSpawn();
    sf::Vector2f originalPosition = TestObject.getSpiderPosition();
    TestObject.SpiderMovement(6);//Upper Left diag Move
    CHECK(TestObject.getSpiderPosition() == originalPosition + sf::Vector2f(-SpiderSpeed, -SpiderSpeed));
}

TEST_CASE("testing Spider down_right movement")
{
    TestClass TestObject;
    TestObject.SpiderSpawn();
    sf::Vector2f originalPosition = TestObject.getSpiderPosition();
    TestObject.SpiderMovement(4);//bottom right diag Move
    CHECK(TestObject.getSpiderPosition() == originalPosition + sf::Vector2f(SpiderSpeed, SpiderSpeed));
}

TEST_CASE("testing Spider down_left movement")
{
    TestClass TestObject;
    TestObject.SpiderSpawn();
    sf::Vector2f originalPosition = TestObject.getSpiderPosition();
    TestObject.SpiderMovement(3);//bottom Left diag Move
    CHECK(TestObject.getSpiderPosition() == originalPosition + sf::Vector2f(-SpiderSpeed, SpiderSpeed));
}

//FLEA MOVEMENT

TEST_CASE("testing Centipede up movement")
{
    TestClass TestObject;
    TestObject.FleaSpawn(sf::Vector2f(gameWidth/2, 0));//spawns top of screen in the mid  of x plane
    sf::Vector2f originalPosition = TestObject.getFleaPosition();
    TestObject.FleaMovement();
    CHECK(TestObject.getFleaPosition() == originalPosition + sf::Vector2f(0, FleaSpeed));
}


///////////////////////////////////////////////////////
//RANDOM EVENT TESTS
///////////////////////////////////////////////////////

TEST_CASE("Spider random mushroom eating AND Mushroom spider collision check")
{
    TestClass TestObject;
    TestObject.SpiderSpawn();
    TestObject.MushroomSpawner(sf::Vector2f(TestObject.getSpiderPosition()));//spawn mushroom inside spider
    for (int loop; loop < 100; loop++)
    {
        TestObject.SpiderMovement(0);//spider doesnt move as 0 isnt movement option but does do mushroom collision check
                                    //also confirms mushroom destructor works
    }
    CHECK(TestObject.MushroomIsEmpty());
}

TEST_CASE("testing random flea mushroom spawns while flea moves")
{
    TestClass TestObject;
    TestObject.FleaSpawn(sf::Vector2f(gameWidth/2, 0));
    for (int loop; loop < gameHeight/FleaSpeed - 1; loop++)
    {
        TestObject.FleaMovement();//flea has probability to spawn mushrooms as it moves down
    }

    int TempnumSpawnedMushrooms = TestObject.getnumMushrooms();


    TestObject.FleaSpawn(sf::Vector2f(gameWidth/2, 0));
    for (int loop; loop < gameHeight/FleaSpeed - 1; loop++)
    {
        TestObject.FleaMovement();//flea has probability to spawn mushrooms as it moves down
    }

    TestObject.FleaSpawn(sf::Vector2f(gameWidth/2, 0));
    for (int loop; loop < gameHeight/FleaSpeed - 1; loop++)
    {
        TestObject.FleaMovement();//flea has probability to spawn mushrooms as it moves down
    }

    TestObject.FleaSpawn(sf::Vector2f(gameWidth/2, 0));
    for (int loop; loop < gameHeight/FleaSpeed - 1; loop++)
    {
        TestObject.FleaMovement();//flea has probability to spawn mushrooms as it moves down
    }

    CHECK_FALSE(TestObject.getnumMushrooms() == 4*TempnumSpawnedMushrooms);//each iteration should have spawned random different number of mushrrom and therefore should not be equal
}

///////////////////////////////////////////////////////
//COLLISION TESTS
///////////////////////////////////////////////////////
//SHOOT TESTS
TEST_CASE("Test Mushroom Shot")
{
    TestClass TestObject;
    TestObject.ShootSpawn(sf::Vector2f(gameWidth / 2, gameHeight - Standby.y/2));
    TestObject.MushroomSpawner(sf::Vector2f(TestObject.getShootPosition() - sf::Vector2f(0, ShootSpeed)));
    TestObject.ShootMovement();
    TestObject.MushroomCollisionChecks();
    CHECK(TestObject.getMushroomHealth() == 3);

}

TEST_CASE("centipede right wall collision")
{
    TestClass TestObject;
    sf::Vector2f originalPosition;
    for (int loop = 0; loop < gameWidth/CentipedeSpeed -3; loop++) //hits right wall (-3 due to starting pos of centipede)
    {
        originalPosition = TestObject.getCentipedePosition();
        TestObject.CentipedeMovementX();//   hit boundary and should drop 1 unit and move left
    }
    CHECK(TestObject.getCentipedePosition() == originalPosition + sf::Vector2f(-CentipedeSpeed, CentipedeSize.y));
}

TEST_CASE("testing left wall collision")
{
    TestClass TestObject;
    sf::Vector2f originalPosition;
    for (int loop = 0; loop < (2*gameWidth/CentipedeSpeed -7); loop++) //hits right wall then goes all the way to hit the left wall
    {
        originalPosition = TestObject.getCentipedePosition();
        TestObject.CentipedeMovementX();//   hit boundary and should drop 1 unit and move left
    }
    CHECK(TestObject.getCentipedePosition() == originalPosition + sf::Vector2f(CentipedeSpeed, CentipedeSize.y));
}

TEST_CASE("testing Centipede and shoot collision")
{
    TestClass TestObject;
    TestObject.ShootSpawn(TestObject.getCentipedePosition() + sf::Vector2f(0,ShootSpeed));
    TestObject.ShootMovement();
    CHECK(TestObject.CentipedeIsEmpty());//the only segment is shot so should be no centipede left
}

TEST_CASE("testing Centipede and Mushroom Collision")
{
    TestClass TestObject;

    TestObject.MushroomSpawner(TestObject.getCentipedePosition() + sf::Vector2f(CentipedeSize.x,0));
    TestObject.CentipedeMovementX();
    TestObject.CentipedeMovementX();
    TestObject.CentipedeMovementX();
    TestObject.CentipedeMovementX();//moves to collision point
    sf::Vector2f originalPosition = TestObject.getCentipedePosition();
    TestObject.MushroomCollisionChecks();//check for collision and moves centipede down
    TestObject.CentipedeMovementX();
    CHECK(TestObject.getCentipedePosition() == originalPosition + sf::Vector2f(-CentipedeSpeed, CentipedeSize.y));

}


TEST_CASE("testing Flea shot")
{
    TestClass TestObject;
    TestObject.FleaSpawn(sf::Vector2f(400, 10));
    TestObject.ShootSpawn(TestObject.getFleaPosition() + sf::Vector2f(0,FleaSpeed));
    TestObject.FleaMovement();
    CHECK(TestObject.FleaIsEmpty());
}

TEST_CASE("testing Spider shoot collision")
{
    TestClass TestObject;
    TestObject.SpiderSpawn();
    TestObject.ShootSpawn(TestObject.getSpiderPosition() + sf::Vector2f(0,SpiderSpeed));
    TestObject.SpiderMovement(2);
    CHECK(TestObject.spiderIsEmpty());
}

TEST_CASE("testing Spider Player collision")
{
    TestClass TestObject;
    TestObject.SpiderSpawn();
    for (int loop = 0; loop < 100 ; loop++)//moving player to spider
    {
        TestObject.PlayerControls("left");
    }

    for (int loop = 0; loop < floor(PlayerCeiling/PlayerSpeed) ; loop++)
    {
        TestObject.PlayerControls("up");
    }

    TestObject.SpiderMovement(2);
    CHECK(TestObject.getPlayerHealth() == 2);
}


TEST_CASE("testing Centipede player collision")
{
    TestClass TestObject;

    for (int loop = 0; loop < 79; loop++)
    {
        TestObject.CentipedeMovementX();//centipede to just past middle of screen
    }

    for (int loop = 0; loop < (gameHeight/CentipedeSize.y) - 1; loop++)
    {
        TestObject.CentipedeMovementY(0);//centipede to bottom of screen
    }
    TestObject.CentipedeMovementX();//collision happens here when moving left again
    CHECK(TestObject.getPlayerHealth() == 2);
}


TEST_CASE("Testing ddt collosion and explosion")
{
    TestClass TestObject;
    TestObject.DDTSpawn();
    TestObject.MushroomSpawner(TestObject.getDDTPosition());
    TestObject.ShootSpawn(TestObject.getDDTPosition());
    TestObject.DDTCollisionChecks();
    CHECK(TestObject.MushroomIsEmpty());
}


//Player boundry collisions
TEST_CASE("testing player right boundary")
{
    TestClass TestObject;
    for (int loop = 0; loop < 100 ; loop++)
    {
         TestObject.PlayerControls("right");
    }

    CHECK(TestObject.getPlayerPosition().x < gameWidth);//can move slighlty passed boundary point by a certain amount but will never cross end boundary
}

TEST_CASE("testing player left boundary")
{
    TestClass TestObject;
    for (int loop = 0; loop < 100 ; loop++)
    {
         TestObject.PlayerControls("left");
    }

    CHECK(TestObject.getPlayerPosition().x > 0);//can move slighlty passed boundary point by a certain amount but will never cross end boundary
}

TEST_CASE("testing player up boundary")
{
    TestClass TestObject;
    for (int loop = 0; loop < 100 ; loop++)
    {
         TestObject.PlayerControls("up");
    }

    CHECK(TestObject.getPlayerPosition().y > PlayerCeiling - Up.y/2);//can move slighlty passed boundary point by a certain amount but will never cross end boundary
}

TEST_CASE("testing player down boundary")
{
    TestClass TestObject;
    for (int loop = 0; loop < 100 ; loop++)
    {
         TestObject.PlayerControls("down");
    }

    CHECK(TestObject.getPlayerPosition().y < gameHeight);//can move slighlty passed boundary point by a certain amount but will never cross end boundary
}


