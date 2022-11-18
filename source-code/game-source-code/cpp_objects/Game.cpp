#include "../header_files/Game.h"

//////////////////////////////////////////////////////////////
///CONSTRUCTOR AND DESTRUCTOR
//////////////////////////////////////////////////////////////

Game::Game()://game constructor including constructor calls of private objects in game.h
window(sf::VideoMode(gameWidth, gameHeight, 32), "Centipede: Dragon Ball Z Edition", sf::Style::Titlebar | sf::Style::Close), //window constructor
TexturePack1(),//Game Texture constructor
SoundPack1(),//Sound Buffer constructor
PlayerObject(gameWidth, gameHeight, Standby, PlayerSpeed),//Player constructor
CentipedeObject(gameWidth, gameHeight, CentipedeSize, CentipedeStartSegments, 1),//Centipede constructor with 12 segments, speed gets changed upon difficulty selection
MushroomFieldObject(gameWidth, gameHeight, MushroomSize, 1),//spawn chance gets changed upon difficulty selection
DDTFieldObject()
{
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    Iconimage.loadFromFile("resources/textures/sprites/dragonballsprites/fullball.png");
    window.setIcon(Iconimage.getSize().x, Iconimage.getSize().y, Iconimage.getPixelsPtr());
    //ctor
}

Game::~Game()
{
    //dtor
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//GAME MENU, DIFFICULTY, OPTIONS AND RUNNING GAME SCREENS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//MENU SCREEN
//////////////////////////////////////////////////////////////

void Game::Menu()
{
    bool isMenuScreen = true;
    bool goToDifficultyScreen = false;
    window.clear();

    PlayGameMusic = true;
    PlayedFromOptions = false;

    if (PlayMenuMusic)
    {
        MenuSound = SoundPack1.getMenuSound();
        MenuSound.play();
        MenuSound.setLoop(true);
    }

    window.draw(TexturePack1.getCurrentBackgroundSprite());//Display current screen when called
    window.display();

    while(isMenuScreen)
    {
        // Handle events
        while(window.pollEvent(event))
        {
            // Window closed or escape key pressed: exit
            if ((event.type == sf::Event::Closed) ||((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
            {
                isMenuScreen = false;
                break;
            }
            // Enter key pressed: play
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                isMenuScreen = false;
                goToDifficultyScreen = true;
                break;
            }
        }
    }
    if (goToDifficultyScreen)
    {
        Difficulty();
    }
}

//////////////////////////////////////////////////////////////
//DIFFICULTY SCREEN
//////////////////////////////////////////////////////////////

void Game::Difficulty()
{
    bool isDifficultyScreen = true;
    bool goToMenuScreen = false;
    bool goToGameScreen = false;
    window.clear();

    TexturePack1.setCurrentBackgroundSprite(4);//set background sprite to difficulty sprite
    window.draw(TexturePack1.getCurrentBackgroundSprite());
    window.display();

    while(isDifficultyScreen)
    {
        // Handle events
        while(window.pollEvent(event))
        {
            // Window closed or escape key pressed: exit
            if ((event.type == sf::Event::Closed) ||((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
            {
                isDifficultyScreen = false;
                TexturePack1.setCurrentBackgroundSprite(1);
                PlayMenuMusic = false;
                goToMenuScreen = true;
                break;
            }
            // Enter key pressed:go to difficulty
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
            {
                setDifficulty(1);
                isDifficultyScreen = false;
                goToGameScreen = true;
                break;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
            {
                setDifficulty(2);
                isDifficultyScreen = false;
                goToGameScreen = true;
                break;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
            {
                setDifficulty(3);
                isDifficultyScreen = false;
                goToGameScreen = true;
                break;
            }
        }
    }

    if(goToMenuScreen)
    {
        Menu();
    }
    else if(goToGameScreen)
    {
        MenuSound.stop();
        StartGame();
    }
}

//////////////////////////////////////////////////////////////
//SET GAME DIFFICULTY
//////////////////////////////////////////////////////////////

void Game::setDifficulty(int inp)
{

    switch (inp)
    {
    case 1:
            CentipedeSpeed = 2;//movement speed must be factor of both mad width and centipede size
            FleaSpawnTimeConst = 15;//time interval between fleas spawning
            MushroomSpawnChance = 100;//Spawn Randomness (1/(value+1)) *100 = percentage)
            SpiderSpawnTimeConst = 12;
            break;

    case 2:
            CentipedeSpeed = 5;
            FleaSpawnTimeConst = 10;
            MushroomSpawnChance = 40;
            SpiderSpawnTimeConst = 10;
            break;

    case 3:
            CentipedeSpeed = 10;
            FleaSpawnTimeConst = 6;
            MushroomSpawnChance = 20;
            SpiderSpawnTimeConst = 8;
            break;
    }
}

//////////////////////////////////////////////////////////////
//OPTIONS SCREEN
//////////////////////////////////////////////////////////////

bool Game::Options()
{
    bool isOptionsScreen = true;
    bool goToMenu = false;
    window.clear();

    TexturePack1.setCurrentBackgroundSprite(5);//set background sprite to options sprite
    window.draw(TexturePack1.getCurrentBackgroundSprite());
    window.display();

    while(isOptionsScreen)

    {
        // Handle events
        while(window.pollEvent(event))
        {
            // Window closed or escape key pressed: exit
            if((event.type == sf::Event::Closed) ||((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
            {
                window.clear();
                ShotsVector.clear();
                FleaVector.clear();
                SpiderVector.clear();
                isOptionsScreen = false;
                PlayMenuMusic = true;
                GameSound.stop();
                TexturePack1.setCurrentBackgroundSprite(1);//set screen texture for splash screen background
                goToMenu = true;
                break;
            }
            // Enter key pressed: play
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                isOptionsScreen = false;
                TexturePack1.setCurrentBackgroundSprite(0);//game screen
                break;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
            {
                GameSound.stop();
                PlayGameMusic = false;//stops music
                break;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
            {
                GameSound.play();
                PlayedFromOptions = true;//allows for instant music start from options screen and will not restart song when back in game
                break;
            }
        }
    }

    if (goToMenu)
    {
        return false;//will terminate isgamescreen loop and go to menu
    }
    else
    {
        return true;
    }
}

//////////////////////////////////////////////////////////////
//START GAME SCREEN
//////////////////////////////////////////////////////////////

void Game::StartGame()
{
    bool isGameScreen = true;

    //reset Game objects per new game
    PlayerObject.resetPlayerPosition(gameWidth, gameHeight);
    CentipedeObject.setCentipede(gameWidth, gameHeight, CentipedeSize, CentipedeStartSegments, CentipedeSpeed);
    MushroomFieldObject.setMushroomField(gameWidth, gameHeight, MushroomSize, MushroomSpawnChance);
    DDTFieldObject.ResetDDTField();
    ShotsVector.clear();
    FleaVector.clear();
    SpiderVector.clear();

    //set Start game textures
    TexturePack1.setCurrentBackgroundSprite(0);
    TexturePack1.setCurrentPlayerSprite(0);
    TexturePack1.setCurrentShootSprite(0);
    TexturePack1.setCurrentMushroomSprite(0);
    TexturePack1.setCurrentDDTSprite(0);
    TexturePack1.setCurrentFleaSprite(0);
    TexturePack1.setCurrentSpiderSprite(0);

    //Clock resets
    reloadClock.restart();
    FleaSpawnClock.restart();
    SpiderSpawnClock.restart();
    DDTSpawnClock.restart();
    DDTExplosionClock.restart();

    //score
    score = 0;
    PlayerObject.setLives(3);
    highscore.push_back(score);

    //set and load texts and positions
    SetTexts();

    //load game music
    GameSound = SoundPack1.getGameSound();

    //Game Mechanics
    while(isGameScreen)
    {
        //////////////////////////////////////////////////////////////
        //SCREEN REFRESH
        //////////////////////////////////////////////////////////////

        window.clear();
        window.draw(TexturePack1.getCurrentBackgroundSprite());

        //////////////////////////////////////////////////////////////
        //OPEN OPTIONS EVENT
        //////////////////////////////////////////////////////////////

        while(window.pollEvent(event))
        {
            // Window closed or escape key pressed: exit
            if((event.type == sf::Event::Closed) ||((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
            {
                isGameScreen = Options();
                break;
            }
        }

        //////////////////////////////////////////////////////////////
        //GAME TIMERS
        //////////////////////////////////////////////////////////////

        sf::Time FleaSpawnTime = FleaSpawnClock.getElapsedTime();
        sf::Time SpiderSpawnTime = SpiderSpawnClock.getElapsedTime();
        sf::Time DDTSpawnTime = DDTSpawnClock.getElapsedTime();
        sf::Time reloadTime = reloadClock.getElapsedTime();

        //////////////////////////////////////////////////////////////
        //START GAME MUSIC
        //////////////////////////////////////////////////////////////

        if (PlayGameMusic && !PlayedFromOptions)//set along with options function to only play in a loop from start, off and on ability further on is only handled in options
        {
            GameSound.play();
            GameSound.setLoop(true);
            GameSound.setVolume(5.f);
            PlayGameMusic = false;
        }

        //////////////////////////////////////////////////////////////
        //DISPLAY SCORE, LIVES AND HIGHSCORE COUNT
        //////////////////////////////////////////////////////////////

        DisplayBoard(textLives, textScore, textHighscore);

        //////////////////////////////////////////////////////////////
        //OBJECT SPAWNING
        //////////////////////////////////////////////////////////////

        FleaSpawn(FleaSpawnTime);//FLEA SPAWN
        SpiderSpawn(SpiderSpawnTime);//SPIDER SPAWN
        DDTSpawn(DDTSpawnTime);//DDT SPAWN


        //////////////////////////////////////////////////////////////
        //OBJECT MOVEMENT AND DRAWING
        //////////////////////////////////////////////////////////////
        //respective collision checks called within these objects
        PlayerControls(reloadTime);//PLAYER MOVEMENT
        CentipedeMovementX();//CENTIPEDE MOVEMENT
        FleaMovement();//FLEA MOVEMENT
        SpiderMovement();//SPIDER MOVEMENT
        ShootMovement();//SHOT MOVEMENT

        //////////////////////////////////////////////////////////////
        //ENVIRONMENTAL COLLISION CHECKS
        //////////////////////////////////////////////////////////////

        DDTCollisionChecks();//DDT EXPLOSION COLLISION CHECK
        MushroomCollisionChecks();//MUSHROOM COLLOSION DETECTION

        //////////////////////////////////////////////////////////////
        //WON/LOST GAME CHECK
        //////////////////////////////////////////////////////////////

        if (isGameScreen)
        {
            isGameScreen = WonCheck();
        }
        if (isGameScreen)
        {
            isGameScreen = LostCheck();//in the case you win you must check if you lost
        }

        //////////////////////////////////////////////////////////////
        //DISPLAY OBJECTS IN WINDOW
        //////////////////////////////////////////////////////////////

        window.display();
    }
    Menu();//End game process then go to menu
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//THE FOLLOWING FUNCTIONS ARE PRIVATE FUNCTIONS CALLED WITHIN THE START GAME FUNCTION AND DEAL WITH THE RUNNING OF THE GAME
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//SET TEXTS
//////////////////////////////////////////////////////////////

void Game::SetTexts()
{
    font.loadFromFile("resources/fonts/Score.ttf");
    tempText.setFont(font);
    tempText.setCharacterSize(38);
    tempText.setFillColor(sf::Color::White);
    tempText.setPosition(gameWidth - 200.f,gameHeight - 60.f);
    textLives = tempText;
    tempText.setPosition(20.f,gameHeight - 100.f);
    textScore = tempText;
    tempText.setPosition(20.f,gameHeight - 60.f);
    textHighscore = tempText;
}

//////////////////////////////////////////////////////////////
//DISPLAY BOARD
//////////////////////////////////////////////////////////////

void Game::DisplayBoard(sf::Text textLives, sf::Text textScore, sf::Text textHighscore)
{
    textLives.setString("Lives: " + std::to_string(PlayerObject.getLives()));
    window.draw(textLives);
    textScore.setString("Score: " + std::to_string(score));
    window.draw(textScore);
    std::sort(highscore.begin(),highscore.end(), std::greater<int>());
    textHighscore.setString("Highscore: "+std::to_string(highscore[0]));
    window.draw(textHighscore);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//GAME SPAWNERS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//FLEA SPAWN
//////////////////////////////////////////////////////////////

void Game::FleaSpawn(sf::Time FleaSpawnTime)
{
    if (FleaSpawnTime.asSeconds() >= FleaSpawnTimeConst)//delay in between flea spawns
    {
        int Xpos = (((rand() % (int)(gameWidth/FleaSize.x -1)) + 1) * FleaSize.x) +FleaSize.x/2;//cant spawn on X boundaries
        if (Xpos == ((gameWidth/FleaSize.x - 1) * FleaSize.x) + FleaSize.x/2)
        {
            Xpos = Xpos - FleaSize.x;
        }
        Flea FleaObject(Xpos, FleaSize, FleaSpeed);//construct flea object at random x position
        FleaVector.push_back(FleaObject);//make copy in vector, made as a vector in the case you want to have multiple flea objects active at the same time i.e very low flea spawn time
        FleaSpawnClock.restart();
    }
}

//////////////////////////////////////////////////////////////
//SPIDER SPAWN
//////////////////////////////////////////////////////////////

void Game::SpiderSpawn(sf::Time SpiderSpawnTime)
{
    if (SpiderSpawnTime.asSeconds() >= SpiderSpawnTimeConst)//delay in between spider spawns
    {
        Spider SpiderObject(PlayerCeiling, SpiderSize, SpiderSpeed);//construct Spider object at top of player ceiling area
        SpiderVector.push_back(SpiderObject);//make copy in vector, made as a vector in the case you want to have multiple flea objects active at the same time i.e very low flea spawn time
        SpiderSpawnClock.restart();
    }
}

//////////////////////////////////////////////////////////////
//DDT SPAWN
//////////////////////////////////////////////////////////////

void Game::DDTSpawn(sf::Time DDTSpawnTime)
{
    if (DDTSpawnTime.asSeconds() >= DDTSpawnTimeConst && DDTFieldObject.getDDTField().size() < 4)//delay in between DDT spawns must be less than 4 ddt bombs at a time
    {
        if (rand() % DDTSpawnChance == 0)//33% random chance it spawns
        {
            DDTFieldObject.SpawnDDT(gameWidth, PlayerCeiling, DDTSize);
        }
        DDTSpawnClock.restart();
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//GAME OBJECT MOVEMENT
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//PLAYER MOVEMENT CONTROLS
//////////////////////////////////////////////////////////////

void Game::PlayerControls(sf::Time reloadTime)
{
    sf::Sprite PlayerSprite;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            PlayerObject.setPlayerSize(Up);
            TexturePack1.setCurrentPlayerSprite(1);
            TexturePack1.setPlayerSpriteOrigin(Up);
            if (PlayerObject.getCoords().y > PlayerCeiling )//Player area ristricted vertically
            {
                PlayerObject.MoveUp();
            }
        }
        else //STANDBY
        {
            PlayerObject.setPlayerSize(Standby);
            TexturePack1.setCurrentPlayerSprite(0);
            TexturePack1.setPlayerSpriteOrigin(Standby);
        }

        //DOWN MOVEMENT
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            PlayerObject.setPlayerSize(Down);
            TexturePack1.setCurrentPlayerSprite(2);
            TexturePack1.setPlayerSpriteOrigin(Down);
            if (PlayerObject.getCoords().y < gameHeight - Down.y / 2)
            {
                PlayerObject.MoveDown();
            }
        }

        //LEFT MOVEMENT
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            PlayerObject.setPlayerSize(Left);
            TexturePack1.setCurrentPlayerSprite(3);
            TexturePack1.setPlayerSpriteOrigin(Left);
            if (PlayerObject.getCoords().x > Left.x / 2)
            {
                PlayerObject.MoveLeft();
            }
        }

        //RIGHT MOVEMENT
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            PlayerObject.setPlayerSize(Right - sf::Vector2f(30, 0));//additional hitbox size change to accommodate irregular sprite shape by decreasing sprite size values
            TexturePack1.setCurrentPlayerSprite(4);
            TexturePack1.setPlayerSpriteOrigin(Right);
            if (PlayerObject.getCoords().x  < gameWidth - Right.x / 2)
            {
                PlayerObject.MoveRight();
            }
        }

        //SHOOTING: CREATION OF SHOOT OBJECTS AND POPULATION OF SHOOT VECTOR
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            PlayerObject.setPlayerSize(Shooting);
            TexturePack1.setCurrentPlayerSprite(6);
            TexturePack1.setPlayerSpriteOrigin(Shooting);
            TexturePack1.setCurrentShootSprite(0);

            if (reloadTime.asSeconds() >= reloadTimeConst)//delay in between shots
            {
                Shoot ShootObject(PlayerObject.getCoords(), ShootSize, ShootSpeed);//construct shoot object
                ShotsVector.push_back(ShootObject);//make copy in vector
                reloadClock.restart();
            }
        }

        //DRAWING OF PLAYER SPRITE
        PlayerSprite = TexturePack1.getCurrentPlayerSprite();
        PlayerSprite.setPosition(PlayerObject.getCoords());
        //window.draw(PlayerObject.getPlayerRect());
        window.draw(PlayerSprite);
}

//////////////////////////////////////////////////////////////
//SHOOT MOVEMENT
//////////////////////////////////////////////////////////////

void Game::ShootMovement()
{
    sf::Sprite ShootSprite;

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

            //DRAWING OF SHOOT SPRITE
            ShootSprite = TexturePack1.getCurrentShootSprite();
            ShootSprite.setPosition(ShotsVector[ShootNum].getCoords());

            //window.draw(ShotsVector[ShootNum].getShootRect());
            window.draw(ShootSprite);
        }
    }
}

//////////////////////////////////////////////////////////////
//CENTIPEDE MOVEMENT X DIRECTION
//////////////////////////////////////////////////////////////

void Game::CentipedeMovementX()
{
    sf::Sprite CentipedeSprite;

    for (int SegmentNum = 0; SegmentNum < CentipedeObject.getCentipede().size(); SegmentNum++)//Move head first
    {
        if ((CentipedeObject.getSegmentCoords(SegmentNum).x  >= gameWidth - CentipedeSize.x / 2) || (CentipedeObject.getSegmentCoords(SegmentNum).x <= CentipedeSize.x / 2) && (CentipedeObject.getSegmentCoords(SegmentNum).y != CentipedeSize.y / 2))//right and left boundary collision check
        {
            CentipedeMovementY(SegmentNum);//Move in the Y Direction in the case Boundary is hit.
        }

        CentipedeObject.MoveX(SegmentNum);

        //DRAWING OF CENTIPEDE SPRITE
        if (CentipedeObject.getSegmentIsHead(SegmentNum))//true if head, false if body
        {
            if (CentipedeObject.getSegmentCurrentDirectionX(SegmentNum))//true if going right, false if going left
            {
                TexturePack1.setCurrentCentipedeSprite(1);//head facing right
            }
            else
            {
                TexturePack1.setCurrentCentipedeSprite(2);//head facing left
            }
        }
        else
        {
            TexturePack1.setCurrentCentipedeSprite(0);//body
        }
        CentipedeSprite = TexturePack1.getCurrentCentipedeSprite();
        CentipedeSprite.setPosition(CentipedeObject.getSegmentCoords(SegmentNum));
        window.draw(CentipedeObject.getSegmentRect(SegmentNum));
        window.draw(CentipedeSprite);

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

void Game::CentipedeMovementY(int SegmentNum)
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

void Game::FleaMovement()
{
    sf::Sprite FleaSprite;
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
        FleaSprite = TexturePack1.getCurrentFleaSprite();
        FleaSprite.setPosition(FleaVector[FleaNum].getCoords());
        //window.draw(FleaVector[FleaNum].getFleaRect());
        window.draw(FleaSprite);
    }
}

//////////////////////////////////////////////////////////////
//SPIDER MOVEMENT
//////////////////////////////////////////////////////////////

void Game::SpiderMovement()
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

        //DRAWING SPIDER SPRITES
        if (SpiderVector[SpiderNum].getCurrentDirection() == 2 || SpiderVector[SpiderNum].getCurrentDirection() == 4)
        {
            TexturePack1.setCurrentSpiderSprite(0);
        }
        if (SpiderVector[SpiderNum].getCurrentDirection() == 3 || SpiderVector[SpiderNum].getCurrentDirection() == 5)
        {
            TexturePack1.setCurrentSpiderSprite(1);
        }
        SpiderSprite = TexturePack1.getCurrentSpiderSprite();
        SpiderSprite.setPosition(SpiderVector[SpiderNum].getCoords());
        //window.draw(SpiderVector[SpiderNum].getSpiderRect());
        window.draw(SpiderSprite);
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//GAME COLLISIONS CALLS TO COLLISIONS ARE DONE WITHIN THEIR RESPECTIVE MOVEMENT FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//DDT BOMB COLLISIONS AS WELL AS DDT BOMB DISPLAY
//////////////////////////////////////////////////////////////

void Game::DDTCollisionChecks()
{
    int numDDTExploded = 0; //used to reset clock timer
    for (int DDTNum = 0; DDTNum < DDTFieldObject.getDDTField().size(); DDTNum++)
    {
        sf::Sprite DDTSprite;

        //!DDT AND SHOOT COLLISION
        ShootDDTCollisionCheck(DDTNum);

        if (DDTFieldObject.getDDTIsExploded(DDTNum))
        {
            numDDTExploded++;
            TexturePack1.setCurrentDDTSprite(1);//Exploded sprite

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
            TexturePack1.setCurrentDDTSprite(0);//normal small bomb
        }
        DDTSprite = TexturePack1.getCurrentDDTSprite();
        DDTSprite.setPosition(DDTFieldObject.getRectCoords(DDTNum));
        //window.draw(DDTFieldObject.getDDTBlock(DDTNum));
        window.draw(DDTSprite);//display sprite

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

void Game::MushroomCollisionChecks()
{
    sf::Sprite MushroomSprite;

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
                     (CentipedeObject.getSegmentCoords(SegmentNum).x + CentipedeSize.x/2 < MushroomFieldObject.getMushroomCoords(MushroomNum).x + MushroomSize.x/2))
                {
                    CentipedeMovementY(SegmentNum);
                }
            }
            else
            {
                if  ((CentipedeObject.getSegmentCoords(SegmentNum).y == (MushroomFieldObject.getMushroomCoords(MushroomNum).y)) &&
                     (CentipedeObject.getSegmentCoords(SegmentNum).x - CentipedeSize.x/2 <= MushroomFieldObject.getMushroomCoords(MushroomNum).x + MushroomSize.x/2  )&&
                     (CentipedeObject.getSegmentCoords(SegmentNum).x - CentipedeSize.x/2 > MushroomFieldObject.getMushroomCoords(MushroomNum).x - MushroomSize.x/2))
                {
                    CentipedeMovementY(SegmentNum);
                }
            }
        }

        //MUSHROOM AND SHOOT COLLISION
        ShootMushroomCollisionCheck(MushroomNum);

        //DRAWING OF MUSHROOM SPRITE
        if (MushroomFieldObject.getMushroomHealth(MushroomNum) <= 2)
        {
            TexturePack1.setCurrentMushroomSprite(1);//broken mushroom
        }
        else
        {
            TexturePack1.setCurrentMushroomSprite(0);//full mushroom
        }
        MushroomSprite = TexturePack1.getCurrentMushroomSprite();
        MushroomSprite.setPosition(MushroomFieldObject.getBlockCoords(MushroomNum));
        //window.draw(MushroomFieldObject.getMushroomBlock(MushroomNum));
        window.draw(MushroomSprite);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//THE FOLLOWING COLLISION FUNCTIONS ARE FUNCTIONS CALLED WITHIN THE SHOOT MOVEMENT FUNCTION ABOVE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//SHOOT WITH DDT COLLISION
//////////////////////////////////////////////////////////////
void Game::ShootDDTCollisionCheck(int DDTNum)
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

void Game::ShootMushroomCollisionCheck(int MushroomNum)
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

bool Game::CentipedeShootCollisionCheck(int ShootNum)
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

void Game::FleaShootCollisionCheck(int FleaNum)
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

void Game::SpiderShootCollisionCheck(int SpiderNum)
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

void Game::SpiderPlayerCollisionCheck(int SpiderNum)
{
    if  (SpiderVector[SpiderNum].getSpiderRect().getGlobalBounds().intersects(PlayerObject.getPlayerRect().getGlobalBounds()))
    {
        LoseLife();
    }
}

//////////////////////////////////////////////////////////////
//SPIDER AND MUSHROOM COLLISION
//////////////////////////////////////////////////////////////
void Game::SpiderMushroomCollisionCheck(int SpiderNum)
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

bool Game::WonCheck()
{
   if(CentipedeObject.getCentipede().empty())
    {
        highscore.push_back(score);
        ShotsVector.clear();
        FleaVector.clear();
        SpiderVector.clear();
        TexturePack1.setCurrentBackgroundSprite(3);//set screen texture for won game background
        GameSound.stop();

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

bool Game::LostCheck()
{
    if(PlayerObject.getLives() == 0)
    {
        highscore.push_back(score);
        CentipedeObject.getCentipede().clear();
        ShotsVector.clear();
        FleaVector.clear();
        SpiderVector.clear();
        TexturePack1.setCurrentBackgroundSprite(2);//set screen texture for lost game background
        GameSound.stop();

        return false;
    }
    else
    {
        return true;
    }
}

//////////////////////////////////////////////////////////////
//LOSE LIFE
//////////////////////////////////////////////////////////////

void Game::LoseLife()
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
//GAIN LIFE FUNCTION
//////////////////////////////////////////////////////////////

void Game::NewLife()//new life granted for every 12000 points
{
    int multiple = oldscore / 12000;
    if (oldscore < 12000 +(12000 * multiple) && score >= 12000+(12000*multiple))
    {
        PlayerObject.setLives(PlayerObject.getLives() + 1);
    }
}

//////////////////////////////////////////////////////////////
//FLEA MUSHROOM SPAWN Y LOCATION
//////////////////////////////////////////////////////////////

sf::Vector2f Game::FleaMushroomSpawnY(int FleaNum)
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//END OF CENTIPEDE GAME PRIVATE FUNCTION IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
