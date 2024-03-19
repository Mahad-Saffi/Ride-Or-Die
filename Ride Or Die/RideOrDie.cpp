#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib> // for rand and srand
#include <ctime>   // for time

using namespace std;

// Function Declarations
void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);
void cursorHide();
void cursorShow();
void setColor(int color);
void ready();
void printRoad();
void header();
void menu();
void printScore();
void printHealth();
void printTime(int Time, int level);
void printPlayer();
void erasePlayer();
void movePlayer();
void printEnemyZombie();
void printEnemyZombie2();
void printEnemyZombie3();
void printEnemyPlane();
void printEnemyChopper();
void printEnemyRocket();
void printEnemyBomb();
void dropEnemyBomb();
void printPlayerBullet();
void eraseEnemyZombie();
void eraseEnemyZombie2();
void eraseEnemyZombie3();
void eraseEnemyPlane();
void eraseEnemyChopper();
void eraseEnemyBomb();
void eraseEnemyRocket();
void erasePlayerBullet();
void moveEnemyZombie(int level);
void moveEnemyPlane();
void moveEnemyChopper();
void moveEnemyBomb();
void moveEnemyRocket();
void movePlayerBullet();
void shootBullet();
void moveBullet(int index);
void dropChopperBullet();
void dropEnemyRocket();
void moveChopperBullet();
void printChopperBullet();
void eraseChopperBullet();

// Global variables and constants
int blue = 1, green = 2, cyan = 3, red = 4, brown = 6, lightwhite = 7, lightblue = 9, lightgreen = 10, lightcyan = 11, lightred = 12, yellow = 14, white  = 15;
int pX, pY;
int roadL = 0, roadY = 0;
int planeX = 0, planeY = 2;
int chopperX = 2, chopperY = 5;
const int maxChopperBullets = 4;
int chopperBulletX[maxChopperBullets];
int chopperBulletY[maxChopperBullets];
bool chopperBulletActive[maxChopperBullets];
int bombX, bombY;
bool bombActive = false;
int rocketX, rocketY;
bool rocketActive = false;
char rocketDir;
int zX = 148, zY = 28;
char zDir = 'L';
int bulletX, bulletY;
bool bulletActive = false;
int score = 0;
const int maxBullets = 25;
int bulletsX[maxBullets];
int bulletsY[maxBullets];
bool bulletsActive[maxBullets];
int health = 100;

main()
{
    
    int option = 0;
    while (option != 3)
    {
        bool won = false, gameOver = false;
        pX = 4, pY = 28;
        health = 100;
        int frame = 0;
        int level = 1;
        int timer = 0; // to check the frames with time
        int Time = 0;  // to print actual time
        score = 0;

        system("cls");
        header();
        menu();
        setColor(green);
        gotoxy(77, 26);
        cout << "Option: ";
        cin >> option;
        setColor(white);

        if (option == 1)
        {
            ready();
            
            printPlayer();
            printEnemyPlane();
            printEnemyChopper();
            printEnemyZombie();

            // Initializing the random number generator
            srand(static_cast<unsigned>(time(0)));

            while (health > 0 && Time < 300)
            {
                Sleep(25);
                movePlayer();
                moveEnemyZombie(level);
                moveEnemyPlane();
                moveEnemyChopper();

                if (GetAsyncKeyState(VK_SPACE))
                {
                    shootBullet();
                }

                for (int i = 0; i < maxBullets; ++i)
                {
                    moveBullet(i);
                }

                if (getCharAtxy(zX - 1, zY) != ' ' || getCharAtxy(zX - 1, zY + 2) != ' '|| getCharAtxy(zX - 1, zY -2) != ' ')
                {
                    if (getCharAtxy(zX - 2, zY) == '>'||getCharAtxy(zX - 2, zY + 2) == '>'||getCharAtxy(zX - 2, zY - 2) == '>')
                    {
                        eraseEnemyZombie();
                        eraseEnemyZombie2();
                        eraseEnemyZombie3();
                        zX = 148;
                        score++;
                    }
                    if (getCharAtxy(zX - 1, zY) == char(219)|| getCharAtxy(zX - 1, zY + 2) == char(219)|| getCharAtxy(zX - 1, zY -2) == char(219))
                    {
                        eraseEnemyZombie();
                        eraseEnemyZombie2();
                        eraseEnemyZombie3();
                        zX = 148;
                        zY = 30;
                    }
                }

                if (getCharAtxy(planeX - 2, planeY) != ' ')
                {
                    eraseEnemyPlane();
                    planeX = roadL - 20;
                }

                if (getCharAtxy(chopperX + 14, chopperY) != ' ')
                {
                    eraseEnemyChopper();
                    chopperX = 2;
                }

                if (getCharAtxy(bulletX + 1, bulletY) != ' ')
                {
                    erasePlayerBullet();
                    bulletX = pX + 16;
                    bulletY = pY + 2;
                }

                // To move Bombs
                dropEnemyBomb();
                moveEnemyBomb();

                // Inside the game loop
                dropEnemyRocket();
                moveEnemyRocket();

                if (level == 2)
                {
                    dropChopperBullet();
                    moveChopperBullet();
                    
                }

                if (getCharAtxy(rocketX - 1, rocketY + 2) != ' ' && getCharAtxy(rocketX - 1, rocketY + 2) != '-' && getCharAtxy(rocketX - 1, rocketY + 2) != '/' && getCharAtxy(rocketX - 1, rocketY + 2) != char(219))
                {
                    eraseEnemyRocket();
                }

                setColor(12);

                frame++;
                if (frame % 3 == 0)
                {   setColor(15);
                    gotoxy(0, 24);
                    cout << char(219) << "/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/" << char(219) << endl;
                    gotoxy(0, 35);
                    cout << char(219) << "/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/" << char(219) << endl;
                    setColor(15);
                    setColor(white);

                }
                else
                {
                    setColor(15);
                    gotoxy(0, 24);
                    cout << char(219) << "~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~" << char(219) << endl;
                    gotoxy(0, 35);
                    cout << char(219) << "~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~/~" << char(219) << endl;
                    setColor(15);
                }
                timer++;
                if (timer % 5 == 0)
                {
                    Time++;
                }

                printScore();
                if (score > 15)
                {
                    level = 2;
                }

                printHealth();
                printTime(Time, level);

                if (health <= 0)
                {
                    gameOver = true;
                }

                if (score >= 60)
                {
                    won = true;
                }
            }

            if (gameOver || (health <= 0 && Time < 600))
            {   
                // Game over message
                system("cls");
                header();
                cout << "\n\nGame Over! Your score: " << score << endl;
                cout << "Press any key to exit." << endl;
                getch();
            }
            else if (won)
            {
                // Game Won message
                system("cls");
                header();
                cout << "\n\nYou Achieved your destination! Your score: " << score << endl;
                cout << "Press any key to exit." << endl;
                getch();
            }
        }
        else if (option == 2)
        {
            system("cls");
            header();
            gotoxy(50, 15);
            cout << "\t\tInstructions" << endl;
            gotoxy(50, 16);
            cout << "1. Player moves with arrow keys." << endl;
            gotoxy(50, 17);
            cout << "2. The game ends if time reaches 600." << endl;
            gotoxy(50, 18);
            cout << "3. The game ends if player's health becomes zero." << endl;
            gotoxy(50, 19);
            cout << "4. Score increases by hitting enemies." << endl;
            gotoxy(50, 20);
            cout << "5. Level 2 begins if score is more than 60." << endl;

            cout << "Press Any Key To Continue...";
            getch();
        }
        else if (option == 3)
        {
            return 0;
        }
        else
        {
            system("cls");
            header();
            cout << "\n\n\n\nInvalid Option!" << endl;
            Sleep(1000);
        }
    }
}

// Function Definitions
void ready()
{
    system("cls");

    roadL = 153;
    roadY = 37;

    printRoad();

    gotoxy(roadL / 3 + 15, 8);
    cout << "PRESS ANY KEY TO START";
    getch();

    system("cls");

    roadL = 155;
    printRoad();

    pX = 4, pY = 28;
    planeX = roadL / 2; // Set the initial position to the middle of the road
}

// Maze Functions
void printRoad()
{
    setColor(12);
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "                                                                                                                                                       " << char(219) << endl;
    cout << char(219) << "-------------------------------------------------------------------------------------------------------------------------------------------------------" << char(219) << endl;
    setColor(15);
}

void header()
{   setColor(green);
    cout << "\t\t\t\t\t _______   __        __                   ______                   _______   __           " << endl;
    cout << "\t\t\t\t\t/       \\ /  |      /  |                 /      \\                 /       \\ /  |          " << endl;
    cout << "\t\t\t\t\t$$$$$$$  |$$ |  ____$$ |  ______        /$$$$$$  |  ______        $$$$$$$  |$$ |  ______  " << endl;
    cout << "\t\t\t\t\t$$ |__$$ |$$ | /    $$ | /      \\       $$$  $$$ | /      \\       $$ |  $$ |$$ | /      \\ " << endl;
    cout << "\t\t\t\t\t$$    $$< $$ |/$$$$$$$ |/$$$$$$  |      $$    $$ |/$$$$$$ |       $$ |  $$ |$$ |/$$$$$$  |" << endl;
    cout << "\t\t\t\t\t$$$$$$$  |$$/ $$ |  $$ |$$    $$ |      $$    $$ |$$ |  $$/       $$ |  $$ |$$/ $$    $$ |" << endl;
    cout << "\t\t\t\t\t$$ |  $$ | __ $$ \\__$$ |$$$$$$$$/       $$    $$ |$$ |            $$ |__$$ | __ $$$$$$$$/ " << endl;
    cout << "\t\t\t\t\t$$ |  $$ |/  |$$    $$ |$$       |      $$    $$/ $$ |            $$    $$/ /  |$$       |" << endl;
    cout << "\t\t\t\t\t$$/   $$/ $$/  $$$$$$$/  $$$$$$$/        $$$$$$/  $$/             $$$$$$$/  $$/  $$$$$$$/ " << endl;
    setColor(white);
}

void menu()
{   setColor(green);
    cout << "\n\n\n\n";
    cout << "\t\t\t\t\t\t\t _____                                         _____ " << endl;
    cout << "\t\t\t\t\t\t\t( ___ )                                       ( ___ )" << endl;
    cout << "\t\t\t\t\t\t\t |   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|   | " << endl;
    cout << "\t\t\t\t\t\t\t |   |                                         |   | " << endl;
    cout << "\t\t\t\t\t\t\t |   |              -------------              |   | " << endl;
    cout << "\t\t\t\t\t\t\t |   |             |  Game Menu   |            |   | " << endl;
    cout << "\t\t\t\t\t\t\t |   |              -------------              |   | " << endl;
    cout << "\t\t\t\t\t\t\t |   |         1.. |  Start Game  |            |   | " << endl;
    cout << "\t\t\t\t\t\t\t |   |              -------------              |   | " << endl;
    cout << "\t\t\t\t\t\t\t |   |         2.. | Instructions |            |   | " << endl;
    cout << "\t\t\t\t\t\t\t |   |              -------------              |   | " << endl;
    cout << "\t\t\t\t\t\t\t |   |         3.. |     Exit     |            |   | " << endl;
    cout << "\t\t\t\t\t\t\t |   |              -------------              |   | " << endl;
    cout << "\t\t\t\t\t\t\t |   |             |              |            |   | " << endl;
    cout << "\t\t\t\t\t\t\t |   |              -------------              |   | " << endl;
    cout << "\t\t\t\t\t\t\t |   |                                         |   | " << endl;
    cout << "\t\t\t\t\t\t\t |___|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|___| " << endl;
    cout << "\t\t\t\t\t\t\t(_____)                                       (_____)" << endl;
    setColor(white);    
}

void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}

// Players Functions
void printPlayer()
{
    setColor(1);
    gotoxy(pX, pY);
    cout << "  ______" << endl;
    gotoxy(pX, pY + 1);
    cout << " /|_||_\\`.__" << endl;
    gotoxy(pX, pY + 2);
    cout << "(   _    _ _\\" << endl;
    gotoxy(pX, pY + 3);
    cout << "=`-(_)--(_)-'" << endl;
    setColor(15);
}

void erasePlayer()
{
    gotoxy(pX, pY);
    cout << "             " << endl;
    gotoxy(pX, pY + 1);
    cout << "             " << endl;
    gotoxy(pX, pY + 2);
    cout << "             " << endl;
    gotoxy(pX, pY + 3);
    cout << "             " << endl;
}

void movePlayer()
{
    erasePlayer();

    if (GetAsyncKeyState(VK_LEFT) && getCharAtxy(pX - 2, pY) != char(219))
    {
        pX = pX - 2;
    }
    else if (GetAsyncKeyState(VK_RIGHT) && getCharAtxy(pX + 14, pY) != char(219))
    {
        pX = pX + 2;
    }
    else if (GetAsyncKeyState(VK_UP) && getCharAtxy(pX, pY - 1) != '~' && getCharAtxy(pX, pY - 1) != '/')
    {
        pY -= 1;
    }
    else if (GetAsyncKeyState(VK_DOWN) && getCharAtxy(pX, pY + 4) != '~' && getCharAtxy(pX, pY + 4) != '/')
    {
        pY += 1;
    }

    printPlayer();
}

// Bullet Functions
void printPlayerBullet()
{
    setColor(10);
    gotoxy(bulletX, bulletY);
    cout << "\u001b[1m-";
    setColor(15);
}

void erasePlayerBullet()
{
    gotoxy(bulletX, bulletY);
    cout << " ";
}

// Function to handle player shooting
void movePlayerBullet()
{
    if (bulletActive)
    {
        erasePlayerBullet();

        // Move the bullet forward
        bulletX += 5;

        // Check if bullet collides with wall
        if (getCharAtxy(bulletX + 1, bulletY) == char(219))
        {
            bulletActive = false;
        }

        // Check for collision with enemy
        else if ((bulletX + 1 == zX && bulletY == zY) || (bulletX + 2 == zX && bulletY == zY) || (bulletX + 1 == zX && bulletY == zY-2) || (bulletX + 2 == zX && bulletY == zY-2)||(bulletX + 1 == zX && bulletY == zY+2) || (bulletX + 2 == zX && bulletY == zY +2))
        {
            eraseEnemyZombie(); // To print a new Zombie
            eraseEnemyZombie2(); // To print a new Zombie
            eraseEnemyZombie3(); // To print a new Zombie

            bulletActive = false;
            zX = 148;
            score++;
        }
        // Else print the bullet again for next iteration
        else
        {
            printPlayerBullet();
        }
    }
}


// Enemy Zombie
void printEnemyZombie()
{
    setColor(4);
    gotoxy(zX, zY);
    cout << "\u001b[1m*-*";
    setColor(15);
  
}
void printEnemyZombie2()
{
    setColor(4);
    gotoxy(zX, zY + 2);
    cout << "\u001b[1m*-*";
    setColor(15);
  
}
void printEnemyZombie3()
{
    setColor(4);
    gotoxy(zX, zY - 2);
    cout << "\u001b[1m*-*";
    setColor(15);
  
}

// Enemy Plane
void printEnemyPlane()
{
    setColor(3);
    gotoxy(planeX, planeY);
    cout << " |__\\_\\_o,___/ " << endl;
    gotoxy(planeX, planeY + 1);
    cout << "([___\\_\\_____-'" << endl;
    gotoxy(planeX, planeY + 2);
    cout << " | o'            " << endl;
    setColor(15);
}

// Enemy Chopper
void printEnemyChopper()
{
    setColor(14);
    gotoxy(chopperX, chopperY);
    cout << "   -----|-----" << endl;
    gotoxy(chopperX, chopperY + 1);
    cout << "*>=====[_]L)  " << endl;
    gotoxy(chopperX, chopperY + 2);
    cout << "      -'-`-   " << endl;
    setColor(15);
}

// Enemy Bomb
void printEnemyBomb()
{
    setColor(4);
    gotoxy(bombX, bombY);
    cout << "\u001b[1m|``|" << endl;
    gotoxy(bombX, bombY + 1);
    cout << "\u001b[1m\\  /" << endl;
    gotoxy(bombX, bombY + 2);
    cout << "\u001b[1m '' " << endl;
    setColor(15);
}

void dropEnemyBomb()
{
    // Randomly drop a bomb with a certain probability
    if (rand() % 100 < 5 && !bombActive)
    {
        bombActive = true;
        bombX = planeX + 5;
        bombY = planeY + 3;
    }
}

// Erase Functions
void eraseEnemyZombie()
{
    gotoxy(zX, zY);
    cout << "   ";
}
void eraseEnemyZombie2()
{
    gotoxy(zX, zY + 2);
    cout << "   ";
}
void eraseEnemyZombie3()
{
    gotoxy(zX, zY - 2);
    cout << "   ";
}

void eraseEnemyPlane()
{
    gotoxy(planeX, planeY);
    cout << "                 " << endl;
    gotoxy(planeX, planeY + 1);
    cout << "                 " << endl;
    gotoxy(planeX, planeY + 2);
    cout << "                 " << endl;
}

void eraseEnemyBomb()
{
    gotoxy(bombX, bombY);
    cout << "    " << endl;
    gotoxy(bombX, bombY + 1);
    cout << "    " << endl;
    gotoxy(bombX, bombY + 2);
    cout << "     " << endl;
}

void eraseEnemyChopper()
{
    gotoxy(chopperX, chopperY);
    cout << "              " << endl;
    gotoxy(chopperX, chopperY + 1);
    cout << "              " << endl;
    gotoxy(chopperX, chopperY + 2);
    cout << "              " << endl;
}

// Move Functions
void moveEnemyZombie(int level)
{
    
    if(level == 1){
        eraseEnemyZombie();
    if (getCharAtxy(zX - 1, zY) == ' ' && zDir == 'L')
    {
        zX--;
    }
    if (getCharAtxy(zX - 2, zY) != char(219) && getCharAtxy(zX - 2, zY) != '>' && getCharAtxy(zX - 2, zY) != ' ')
    {
        eraseEnemyZombie();
        zX = 148;
        health-=10;
    }

    printEnemyZombie();
    }
    else if(level == 2){
        eraseEnemyZombie();
        eraseEnemyZombie2();
        eraseEnemyZombie3();
    if (getCharAtxy(zX - 1, zY) == ' ' && zDir == 'L')
    {
        zX--;
    }
    if (getCharAtxy(zX - 2, zY) != char(219) && getCharAtxy(zX - 2, zY) != '>' && getCharAtxy(zX - 2, zY ) != ' ')
    {
        eraseEnemyZombie();
        zX = 148;
        health-=10;
    }
    if (getCharAtxy(zX - 1, zY + 2) == ' ' && zDir == 'L')
    {
        zX--;
    }
    if (getCharAtxy(zX - 2, zY + 2) != char(219) && getCharAtxy(zX - 2, zY+2)  != '>' && getCharAtxy(zX - 2, zY + 2) != ' ')
    {
        eraseEnemyZombie2();
        zX = 148;
        health-=10;
    }
    if (getCharAtxy(zX - 1, zY - 2) == ' ' && zDir == 'L')
    {
        zX--;
    }
    if (getCharAtxy(zX - 2, zY - 2) != char(219) && getCharAtxy(zX - 2, zY-2)  != '>' && getCharAtxy(zX - 2, zY - 2) != ' ')
    {
        eraseEnemyZombie3();
        zX = 148;
        health-=10;
    }

    printEnemyZombie();
    printEnemyZombie2();
    printEnemyZombie3();
    }
}

void moveEnemyPlane()
{
    eraseEnemyPlane();

    if (getCharAtxy(planeX - 1, planeY) == ' ')
    {
        planeX--;
    }

    printEnemyPlane();
}

void moveEnemyChopper()
{
    eraseEnemyChopper();

    if (getCharAtxy(chopperX + 1, chopperY) == ' ')
    {
        chopperX++;
    }

    printEnemyChopper();
}

void moveEnemyBomb()
{
    if (bombActive)
    {
        eraseEnemyBomb();

        // Move the bomb downward
        bombY++;

        // Check if the bomb hit the car
        if (getCharAtxy(bombX, bombY + 3) == '_' || getCharAtxy(bombX, bombY + 3) == '\\' || getCharAtxy(bombX, bombY + 3) == '(' || getCharAtxy(bombX, bombY + 3) == '`' || getCharAtxy(bombX, bombY + 3) == '.')
        {
            bombY = bombY + 3;
            bombActive = false;
            score = score - 5;
            health-=10;
        }

        // Check if bomb hit the road
        else if (getCharAtxy(bombX, bombY + 3) == '-')
        {
            bombY = bombY + 3;
            bombActive = false;
        }

        else
        {
            printEnemyBomb();
        }
    }
}

// Function for Score
void printScore()
{
    gotoxy(2, roadY + 2);
    cout << "Score: " << score;
}

void printHealth()
{
    gotoxy(2, roadY + 3);
    cout << "Health: " << health;
}

void printTime(int Time, int level)
{
    gotoxy(2, roadY + 4);
    cout << "Time.... " << Time;
    gotoxy(2, roadY + 5);
    cout << "Level: " << level;
}

// Set the color
void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void dropEnemyRocket()
{

    if (rand() % 100 < 5 && !rocketActive)
    {
        rocketActive = true;
        rocketX = rand() % (roadL - 4);
        rocketY = 1;
        rocketDir = 'D';
    }
}

void moveEnemyRocket()
{
    if (rocketActive)
    {
        eraseEnemyRocket();

        // Move the rocket diagonally
        if (rocketDir == 'D')
        {
            rocketX--;
            rocketY++;
        }
        if (getCharAtxy(rocketX - 3, rocketY + 1) == char(219))
        {
            rocketActive = false;
        }

        else if (getCharAtxy(rocketX - 1, rocketY + 1) != '-' && getCharAtxy(rocketX - 1, rocketY + 1) != '*' && rocketY > roadY - 4)
        {
            rocketActive = false;
        }
        else
        {
            printEnemyRocket();
        }

        if (getCharAtxy(pX, pY + 1) == char(251) || getCharAtxy(pX + 1, pY + 1) == char(251) || getCharAtxy(pX + 2, pY + 1) == char(251) || getCharAtxy(pX + 3, pY + 1) == char(251) || getCharAtxy(pX + 4, pY + 1) == char(251) || getCharAtxy(pX + 5, pY + 1) == char(251) || getCharAtxy(pX + 6, pY + 1) == char(251) || getCharAtxy(pX + 7, pY + 1) == char(251) || getCharAtxy(pX + 8, pY + 1) == char(251) || getCharAtxy(pX + 9, pY + 1) == char(251) || getCharAtxy(pX + 10, pY + 1) == char(251) || getCharAtxy(pX + 11, pY + 1) == char(251))
        {
            rocketActive = false;
            health -=10;
        }
    }
}

void printEnemyRocket()
{
    setColor(12);
    gotoxy(rocketX, rocketY);
    cout << "\u001b[1m" << char(251);
    setColor(15);
}

void eraseEnemyRocket()
{
    gotoxy(rocketX, rocketY);
    cout << " ";
}

void shootBullet()
{
    for (int i = 0; i < maxBullets; ++i)
    {
        if (!bulletsActive[i])
        {
            bulletsX[i] = pX + 16; // Set initial X position just to the right of the player
            bulletsY[i] = pY + 2;
            bulletsActive[i] = true;
            // Draw the bullet on the screen directly
            gotoxy(bulletsX[i], bulletsY[i]);
            cout << ">";
            break;
        }
    }
}

void moveBullet(int index)
{
    if (bulletsActive[index])
    {
        // Clear previous position
        gotoxy(bulletsX[index], bulletsY[index]);
        cout << " ";

        bulletsX[index] += 2;

        // Check for collision with enemy
        if (bulletsX[index] == zX && (bulletsY[index] == zY || bulletsY[index] == zY+2|| bulletsY[index] == zY-2))
        {
            bulletsActive[index] = false;
            eraseEnemyZombie(); // Erase the zombie
            eraseEnemyZombie2(); // Erase the zombie
            eraseEnemyZombie3(); // Erase the zombie
            zX = 148;           // Reset zombie position
            score++;            // Increase the score
        }
        else if (bulletsX[index] >= roadL - 4)
        {
            bulletsActive[index] = false; // Deactivate bullet if it goes beyond the road
        }
        else
        {
            // Draw bullet at the new position
            gotoxy(bulletsX[index], bulletsY[index]);
            cout << ">";
        }
    }
}

// Chopper Bullet Functions
void dropChopperBullet()
{
    // Randomly drop chopper bullets with a certain probability
    for (int i = 0; i < maxChopperBullets; ++i)
    {
        if (rand() % 100 < 20 && !chopperBulletActive[i] && chopperX < 110)
        {
            chopperBulletActive[i] = true;
            chopperBulletX[i] = chopperX + 7; // Adjust the starting position of the bullet
            chopperBulletY[i] = chopperY + 3; // Adjust the starting position of the bullet
        }
    }
}

void moveChopperBullet()
{
    for (int i = 0; i < maxChopperBullets; ++i)
    {
        if (chopperBulletActive[i])
        {
            eraseChopperBullet();

            // Move the chopper bullets downward diagonally
            chopperBulletX[i]++;
            chopperBulletY[i]++;

            if (getCharAtxy(chopperBulletX[i] + 1, chopperBulletY[i] + 1) == '_')
            {
                chopperBulletActive[i] = false;
                health -= 10;
                continue;
            }

            // Check if the chopper bullet hit the road or went out of bounds
            if (getCharAtxy(chopperBulletX[i], chopperBulletY[i] + 1) == '-')
            {
                chopperBulletActive[i] = false;
                continue;
            }
            else
            {
                printChopperBullet();
            }
        }
    }
}

void printChopperBullet()
{
    for (int i = 0; i < maxChopperBullets; ++i)
    {
        if (chopperBulletActive[i])
        {
            gotoxy(chopperBulletX[i], chopperBulletY[i]);
            cout << char(4);
        }
    }
}

void eraseChopperBullet()
{
    for (int i = 0; i < maxChopperBullets; ++i)
    {
        if (chopperBulletActive[i])
        {
            gotoxy(chopperBulletX[i], chopperBulletY[i]);
            cout << " ";
        }
    }
}