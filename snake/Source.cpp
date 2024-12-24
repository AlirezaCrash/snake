#include<iostream>
#include<time.h>
#include <conio.h>
#include <windows.h>    
constexpr auto windHeight =  30;
constexpr auto windWidth = 80;
constexpr auto KEY_UP = 72;
constexpr auto KEY_DOWN = 80;
constexpr auto KEY_LEFT = 75;
constexpr auto KEY_RIGHT = 77;
enum directions{UP,DOWN,LEFT,RIGHT};
enum difficulty{EASY,NORMAL,HARD};
bool gameOver = false;
int snakeX,snakeY,fruitX,fruitY,tailX[100]={0}, tailY[100]={0}, nTail = 0;
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; 
	SetConsoleCursorInfo(out, &cursorInfo);
}
void gotoxy(int x, int y)
{
	COORD coordinate;
	coordinate.X = x;
	coordinate.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}
void spawnFruit()
{
	bool validPosition = false;
	while (!validPosition)
	{
		int X = (rand() % (windWidth - 2)) + 1;
		int Y = (rand() % (windHeight - 2)) + 1;

		if (X != snakeX || Y != snakeY)
		{
			validPosition = true;
			for (int i = 0; i < nTail; i++)
			{
				if (X == tailX[i] && Y == tailY[i])
				{
					validPosition = false;
					break;
				}
			}
		}
		if (validPosition)
		{
			fruitX = X;
			fruitY = Y;
			gotoxy(fruitX, fruitY);
			std::cout << "#";
		}
	}
}
void createGameWindow()
{
	for (int i = 0;i < windHeight;i++)
	{
		for (int j = 0;j < windWidth;j++)
		{
			if (i == 0 || i == windHeight - 1)
			{
				std::cout << "*";
			}
			else if (j == 0 || j == windWidth - 1)
			{
				std::cout << "*";
			}
			else
				std::cout << " ";
		}
		std::cout << "\n";
	}
	//snake initialisation
	int X = (rand() % (windWidth - 2)) + 1;
	srand(time(NULL));
	int Y = (rand() % (windHeight - 2)) + 1;
	snakeX = X;
	snakeY = Y;
	gotoxy(X, Y);
	std::cout << "O";
}
void snakeLogic()
{
    int prevX = snakeX;
    int prevY = snakeY;
    int prev2X, prev2Y;
    int currentDirection = -1;
    int newDirection = -1;

    while (!gameOver)
    {
        ShowConsoleCursor(false);

        if (_kbhit())
        {
            int newInput = _getch();

            switch (newInput)
            {
            case KEY_UP:
                if (currentDirection != KEY_DOWN)
                {
                    newDirection = KEY_UP;
                }
                break;
            case KEY_DOWN:
                if (currentDirection != KEY_UP)
                {
                    newDirection = KEY_DOWN;
                }
                break;
            case KEY_LEFT:
                if (currentDirection != KEY_RIGHT)
                {
                    newDirection = KEY_LEFT;
                }
                break;
            case KEY_RIGHT:
                if (currentDirection != KEY_LEFT)
                {
                    newDirection = KEY_RIGHT;
                }
                break;
            }
        }

        if (newDirection != -1)
        {
            currentDirection = newDirection;
            newDirection = -1;
        }

        prevX = snakeX;
        prevY = snakeY;

        switch (currentDirection)
        {
        case KEY_UP:
            if (snakeY - 1 > 0)
            {
                if (snakeY - 1 == fruitY && snakeX == fruitX)
                {
                    nTail++;
                    if (nTail == 1)
                    {
                        tailX[0] = snakeX;
                        tailY[0] = snakeY + 1;
                    }
                    gotoxy(snakeX, snakeY);
                    std::cout << "o";
                    prevX = snakeX;
                    prevY = snakeY;

                    snakeY--;
                    gotoxy(snakeX, snakeY);
                    std::cout << "O";
                    spawnFruit();
                }
                else
                {
                    gotoxy(snakeX, snakeY);
                    std::cout << " ";
                    prevX = snakeX;
                    prevY = snakeY;
                    snakeY--;
                    gotoxy(snakeX, snakeY);
                    std::cout << "O";
                }
            }
            else
                gameOver = true;
            break;
        case KEY_DOWN:
            if (snakeY + 1 < windHeight - 1)
            {
                if (snakeY + 1 == fruitY && snakeX == fruitX)
                {
                    nTail++;
                    if (nTail == 1)
                    {
                        tailX[0] = snakeX;
                        tailY[0] = snakeY - 1;
                    }
                    gotoxy(snakeX, snakeY);
                    std::cout << "o";
                    prevX = snakeX;
                    prevY = snakeY;
                    snakeY++;
                    gotoxy(snakeX, snakeY);
                    std::cout << "O";
                    spawnFruit();
                }
                else
                {
                    gotoxy(snakeX, snakeY);
                    std::cout << " ";
                    prevX = snakeX;
                    prevY = snakeY;
                    snakeY++;
                    gotoxy(snakeX, snakeY);
                    std::cout << "O";
                }
            }
            else
                gameOver = true;
            break;
        case KEY_LEFT:
            if (snakeX - 1 > 0)
            {
                if (snakeX - 1 == fruitX && snakeY == fruitY)
                {
                    nTail++;
                    if (nTail == 1)
                    {
                        tailX[0] = snakeX + 1;
                        tailY[0] = snakeY;
                    }
                    gotoxy(snakeX, snakeY);
                    std::cout << "o";
                    prevX = snakeX;
                    prevY = snakeY;
                    snakeX--;
                    gotoxy(snakeX, snakeY);
                    std::cout << "O";

                    spawnFruit();
                }
                else
                {
                    gotoxy(snakeX, snakeY);
                    std::cout << " ";
                    prevX = snakeX;
                    prevY = snakeY;
                    snakeX--;
                    gotoxy(snakeX, snakeY);
                    std::cout << "O";
                }
            }
            else
                gameOver = true;
            break;
        case KEY_RIGHT:
            if (snakeX + 1 < windWidth - 1)
            {
                if (snakeX + 1 == fruitX && snakeY == fruitY)
                {
                    nTail++;
                    if (nTail == 1)
                    {
                        tailX[0] = snakeX - 1;
                        tailY[0] = snakeY;
                    }
                    gotoxy(snakeX, snakeY);
                    std::cout << "o";
                    prevX = snakeX;
                    prevY = snakeY;
                    snakeX++;
                    gotoxy(snakeX, snakeY);
                    std::cout << "O";
                    spawnFruit();
                }
                else
                {
                    gotoxy(snakeX, snakeY);
                    std::cout << " ";
                    prevX = snakeX;
                    prevY = snakeY;
                    snakeX++;
                    gotoxy(snakeX, snakeY);
                    std::cout << "O";
                }
            }
            else
                gameOver = true;
            break;
        }

        for (int i = 0; i < nTail; i++)
        {
            if (snakeX == tailX[i] && snakeY == tailY[i])
            {
                gameOver = true;
            }
        }
        if (nTail > 0)
        {
            for (int i = 0; i < nTail; i++)
            {
                prev2X = tailX[i];
                prev2Y = tailY[i];
                tailX[i] = prevX;
                tailY[i] = prevY;
                prevX = prev2X;
                prevY = prev2Y;

                gotoxy(tailX[i], tailY[i]);
                std::cout << "o";
            }

            gotoxy(prev2X, prev2Y);
            std::cout << " ";
        }
        Sleep(100);
    }
}

void gameLogic()
{
	spawnFruit();
	snakeLogic();

}
void main()
{
	createGameWindow();
	ShowConsoleCursor(false);
	gameLogic();
	
}