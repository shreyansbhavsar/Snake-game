#include<iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool GameOver; //true when game finish
// dimensions of the board/display
const int width = 20;
const int height = 20;

int x, y; //x & y coordinate of snake
int fruitX, fruitY; // x & y coordinate of fruit
int score; // score of the game
int i, j;
int tailX[100], tailY[100], nTail; // length of tail

// to choose the direction for snake movement
enum eDirection
{
	STOP = 0,
	LEFT, RIGHT, UP, DOWN

};
eDirection dir;

void Setup();
//1)set the snake at the centre of the map.
//2)set the food position

void Draw();
/*
draw the map:
#########
#  	    #
#########
*/

void Input();
//get the input of W, A, S, D from the keyboard.
//make switch case.

void Logic();
//1)direction of the snake using W,A,S,D.
//2)Random food position
//3)Eat the food and generate another position.
//4)Hit the wall = GameOver.
//5)Tail of the snake grow when eat the food.

int main()
{
	Setup(); //setup your game
	while (!GameOver)
	{
		Draw(); // draw the map of our board
		if (dir == LEFT || dir == RIGHT) Sleep(30);
		if (dir == UP || dir == DOWN)  Sleep(70);
		Input(); // taking the input from console for the movement of snake
		Logic();
		//Sleep(10);
	}
	return 0;
}

void Setup()
{
	GameOver = false;
	dir = STOP;
	// let's place snake in the middle of the board/display
	x = width / 2;
	y = height / 2;
	// let's place fruit in the random possition
	fruitX = rand() % width;
	fruitY = rand() % height;
	// initialize score to 0
	score = 0;
}

void Draw()
{
	system("cls"); // clear the screen
	// display top border of our board;
	for (i = 0; i <= width + 1 ; i++)
		cout << "#";
	cout << endl;

	// display the remaining part
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";

			if (i == y && j == x) // snake head
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "F"; // print fruit
			else
			{	// printing the tail of snake
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}

			if (j == width - 1)
				cout << "#";

		}
		cout << endl;
	}
	// display the lower border of our board
	for (i = 0; i <= width + 1 ; i++)
		cout << "#";
	cout << endl;

	cout << "Score: " << score << endl; // printing the score
}

void Input()
{
	if (_kbhit()) // check whether keyboard key pressed or not
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT; // when 'a' pressed go to the left continuously
			break;
		case 'd':
			dir = RIGHT; // when 'd' pressed go to the right continuously
			break;
		case 'w':
			dir = UP; // when 'w' pressed go to the up continuously
			break;
		case 's':
			dir = DOWN; // when 's' pressed go to the doen continuously
			break;
		case 'x':
			GameOver = true; // when 'x' pressed game-over
			break;
		}
	}
}

void Logic()
{
	// previous coordinates of a tail
	int preX = tailX[0];
	int preY = tailY[0];
	int pre2X, pre2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (i = 1; i < nTail; i++)
	{
		pre2X = tailX[i];
		pre2Y = tailY[i];
		tailX[i] = preX;
		tailY[i] = preY;
		preX = pre2X;
		preY = pre2Y;
	}
	switch (dir)
	{
	case STOP:
		break;
	case LEFT:
		x--; // decreasing x coordinate
		break;
	case RIGHT:
		x++; // increasing x coordinate
		break;
	case UP:
		y--; // decreasing y coordinate
		break;
	case DOWN:
		y++; // increasing y coordinate
		break;
	default:
		break;
	}
	// if (x >= width || x < 0 || y >= height || y < 0) // check if snake hits the wall then terminate the game
	// 	GameOver = true;

	// pass the snake through the wall
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for ( i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			GameOver = true;

	// when snake eats the fruit
	if (x == fruitX && y == fruitY)
	{
		score++; // increase the score
		// place the next fruit random
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++; // increase the tail length
	}
}

