#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[width*height], tailY[width * height];
int Tail_len;
enum Directon { STOP, LEFT, RIGHT, UP, DOWN };
Directon directon;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

void Setup()
{
    gameOver = false;
    directon = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;//10-gr,
    score = 0;
}
void Print()
{
    
    system("cls");
    SetConsoleTextAttribute(h, 8);
    for (int i = 0; i < width + 2; i++)
    {
        cout << "+";
    };
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
            {
                SetConsoleTextAttribute(h, 8);
                cout << "+";
            };
            if (i == y && j == x)
            {   
                SetConsoleTextAttribute(h, 10);
                cout << "@";
            }
            else if (i == fruitY && j == fruitX)
            { 
                SetConsoleTextAttribute(h, 5);
                cout << "$";
            }
            else
            {
                bool prd = false;
                for (int k = 0; k < Tail_len; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        SetConsoleTextAttribute(h, 10);
                        cout << "*";
                        prd = true;
                    }
                }
                if (!prd)
                    cout << " ";
            }


            if (j == width - 1)
            {
                SetConsoleTextAttribute(h, 8);
                cout << "+";
            }
        }
        cout << endl;
    }
    SetConsoleTextAttribute(h, 8);
    for (int i = 0; i < width + 2; i++)
        cout << "+";
    cout << endl;
    SetConsoleTextAttribute(h, 4);
    cout << "Score:" << score << endl;
}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            directon = LEFT;
            break;
        case 'd':
            directon = RIGHT;
            break;
        case 'w':
            directon = UP;
            break;
        case 's':
            directon = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}
void Other()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < Tail_len; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (directon)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if (x > width || x < 0 || y > height || y < 0)
    gameOver = true;

    for (int i = 0; i < Tail_len; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        Tail_len++;
    }
}
int main()
{
    Setup();
    while (!gameOver)
    {
        Print();
        Input();
        Other();
        Sleep(20);
    }
    return 0;
}