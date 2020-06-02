#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

// Global variables
bool game_over;
const int width = 20;
const int height = 20;
int x, y, fruit_x, fruit_y, score;
int tail_x[100], tail_y[100];
int tail_length;

enum e_direction { stop = 0, LEFT, RIGHT, UP, DOWN };

e_direction direction;


void place_fruit()
{
	fruit_x = rand() % width;
	fruit_y = rand() % height;
}

void setup()
{
	game_over = false;
	direction = stop;
	x = width / 2;
	y = height / 2;
	place_fruit();
	score = 0;
}

void draw()
{
	system("cls");
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruit_y && j == fruit_x)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < tail_length; k++)
				{
					if (tail_x[k] == j && tail_y[k] == i)
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

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
}

void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			direction = LEFT;
			break;
		case 'd':
			direction = RIGHT;
			break;
		case 'w':
			direction = UP;
			break;
		case 's':
			direction = DOWN;
			break;
		case 'x':
			game_over = true;
			break;
		}
	}
}

void logic()
{
	int prev_x = tail_x[0];
	int prev_y = tail_y[0];
	tail_x[0] = x;
	tail_y[0] = y;
	for (int i = 1; i < tail_length; i++)
	{
		int prev_2_x = tail_x[i];
		int prev_2_y = tail_y[i];
		tail_x[i] = prev_x;
		tail_y[i] = prev_y;
		prev_x = prev_2_x;
		prev_y = prev_2_y;
	}
	switch (direction)
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

	if (x >= width)
	{
		x = 0;
	} else if (x < 0)
	{
		x = width - 1;
	}
	if (y >= height)
	{
		y = 0;
	}
	else if (y < 0)
	{
		y = height - 1;
	}
	for (int i = 0; i < tail_length; i++)
	{
		if (tail_x[i] == x && tail_y[i] == y)
		{
			game_over = true;
		}
	}
	if (x == fruit_x && y == fruit_y)
	{
		score += 10;
		place_fruit();
		tail_length++;
	}
}

int main()
{
	setup();
	while (!game_over)
	{
		draw();
		input();
		logic();
		Sleep(10);
	}
	return 0;
}