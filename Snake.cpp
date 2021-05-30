#include <iostream>
#include <cstdlib>
#include <Windows.h>
using namespace std;

// main variables

bool endGame;
enum position
{
    MENU,
    GAME
};
int menu = 0;
position Check;
const int height = 20; //height of the playing area
const int width = 40;  //width of playing area

// snake variables

int x, y, initialPosition = 1;
int tx[100], ty[100], tL;
int fx, fy, sx, sy, tarx, tary, points;

//  game and movement variables

enum movement
{
    STOP = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT
};
movement mov;

void snake_Over()
{
    tL = 0;
    points = 0;
    Check = MENU;
}
void start()
{
    endGame = true;
    Check = MENU;
}
void main_Menu()
{

    // displaying main menu

    system("cls");
    cout << "Main Menu" << endl
         << "Select either option from below!" << endl;
    if (menu == 0)
    {
        cout << "-> Play the Game." << endl;
        cout << "End Game" << endl;
    }
    else if (menu == 1)
    {
        cout << "Play the Game." << endl;
        cout << "-> End Game" << endl;
    }

    // getting user input in main menu

    if (GetAsyncKeyState(VK_RETURN))
    {
        switch (menu)
        {
        case 0:
            Check = GAME;
            break;
        case 1:
            exit(0);
            break;
        }
    }
    else if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
    {
        mov = STOP;
    }
    else if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
    {
        mov = STOP;
    }
    else if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
    {
        mov = STOP;
        menu++;
        Sleep(10);
    }
    else if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
    {
        mov = STOP;
        menu--;
        Sleep(10);
    }

    if (menu <= -1)
    {
        menu = 1;
    }
    else if (menu >= 2)
    {
        menu = 0;
    }
}
void Setup()
{

    // randomizing the position of the point

    mov = STOP;
    x = rand() % width;
    y = rand() % height;
    tarx = rand() % width;
    tary = rand() % height;
    while (x == tarx && y == tary)
    {
        x = rand() % width;
        y = rand() % height;
        tarx = rand() % width;
        tary = rand() % height;
    }
    points = 0;
}
void key_Input()
{
    if (Check == GAME)
    {
        if ((GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) && mov != RIGHT)
        {
            mov = LEFT;
        }
        else if ((GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) && mov != LEFT)
        {
            mov = RIGHT;
        }
        else if ((GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) && mov != UP)
        {
            mov = DOWN;
        }
        else if ((GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) && mov != DOWN)
        {
            mov = UP;
        }
        else if (GetAsyncKeyState(VK_RETURN))
        {
            return;
        }
    }
}
void main_Window()
{

    // creating the main play area

    system("cls");
    for (int i = 0; i < width; i++)
    {
        cout << "_";
    }
    cout << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0 || j == width - 1)
            {
                cout << "|";
            }
            else if (i == y && j == x)
            {
                cout << "O";
            }
            else if (i == tary && j == tarx)
            {
                cout << "*";
            }
            else
            {
                bool print = false;
                for (int k = 0; k < tL; k++)
                {
                    if (tx[k] == j && ty[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
    for (int i = 0; i < width; i++)
    {
        cout << "_";
    }
    cout << endl;
    cout << "Your current score: " << points << " Points";
}
void main_Logic()
{

    // setting tail location

    fx = tx[0];
    fy = ty[0];
    tx[0] = x;
    ty[0] = y;
    for (int i = 1; i < tL; i++)
    {
        sx = tx[i];
        sy = ty[i];
        tx[i] = fx;
        ty[i] = fy;
        fy = sy;
        fx = sx;
        while (tx[i] == tarx && ty[i] == tary)
        {
            tarx = rand() % width;
            tary = rand() % height;
        }
    }

    // snake movement

    switch (mov)
    {
    case LEFT:
        x -= initialPosition;
        break;
    case UP:
        y -= initialPosition;
        break;
    case RIGHT:
        x += initialPosition;
        break;
    case DOWN:
        y += initialPosition;
        break;
    }

    // border collision detection

    if (x <= 0 || x >= width - 1 || y < 0 || y > height - 1)
    {
        snake_Over();
    }

    // tail collision detection

    for (int i = 0; i < tL; i++)
    {
        if (tx[i] == x && ty[i] == y)
        {
            snake_Over();
        }
    }

    // increasing points

    if (x == tarx && y == tary)
    {
        tarx = rand() % width;
        tary = rand() % height;
        points += 10;
        tL++;
    }
}
int main()
{
    start();
    while (endGame == true)
    {
        if (Check == MENU)
        {
            main_Menu();
        }
        else if (Check == GAME)
        {
            Setup();
            while (Check == GAME)
            {
                main_Window();
                key_Input();
                main_Logic();
                Sleep(10);
            }
        }
    }
}
