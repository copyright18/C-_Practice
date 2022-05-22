#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
using namespace std;
const int SNAKE_SIZE = 500;
enum
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
class Food
{
public:
	int x;
	int y;
	int r;
	bool flag;
	DWORD color;
}food;
class Snake
{
public:
	int size;
	int dir;
	int speed;
	POINT coor[SNAKE_SIZE];
}snake;

void Game_Init()
{
	initgraph(640,400);
	srand(GetTickCount());
	snake.size = 3;
	snake.speed = 10;
	snake.dir = RIGHT;
	for (int i = 0; i < snake.size; i++)
	{
		snake.coor[i].x = 40 - 10 * i;
		snake.coor[i].y = 10;
	}
	food.x = rand() % 640;
	food.y = rand() % 400;
	food.color = RGB(rand() % 256, rand() & 256, rand() % 256);
	food.r = rand() % 10 + 5;
	food.flag = true;

}
void Game_Draw()
{
	BeginBatchDraw();
	setbkcolor(RGB(	28,115,119));
	cleardevice();
	for (int i = 0; i < snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.r);
	}
	EndBatchDraw();
}
void Snake_Move()
{
	for (int i = snake.size-1; i>0; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}
	switch (snake.dir)
	{
	case UP:
		snake.coor[0].y-=snake.speed;
		if (snake.coor[0].y <= 0)snake.coor[0].y = 400;
		break;
	case DOWN:
		snake.coor[0].y += snake.speed;
		if (snake.coor[0].y >= 400)snake.coor[0].y = 0;
		break;
	case LEFT:
		snake.coor[0].x -= snake.speed;
		if (snake.coor[0].x <= 0)snake.coor[0].x = 640;
		break;
	case RIGHT:
		snake.coor[0].x += snake.speed;
		if (snake.coor[0].x >= 640)snake.coor[0].x = 0;
		break;

	}
}
void Eat_Food()
{
	if (food.flag && snake.coor[0].x >= food.x - food.r && snake.coor[0].x <= food.x + food.r &&
		snake.coor[0].y <= food.y + food.r && snake.coor[0].y >= food.y - food.r)
	{
		food.flag = false;
		snake.size++;
	}
	if (food.flag == false)
	{
		food.x = rand() % 640;
		food.y = rand() % 400;
		food.color = RGB(rand() % 256, rand() & 256, rand() % 256);
		food.r = rand() % 10 + 5;
		food.flag = true;
	}

}
	void Key_Concrol()
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case'w':
			case'W':
			case'72':
				if (snake.dir != DOWN)
					snake.dir = UP;
				break;
			case'a':
			case 'A':
			case 75:
				if(snake.dir!=RIGHT)
					snake.dir = LEFT;
				break;
			case's':
			case'S':
			case'80':
				if (snake.dir != UP)
					snake.dir =DOWN;
				break;
			case'd':
			case'D':
			case'77':
				if (snake.dir != LEFT)
					snake.dir = RIGHT;
				break;
			}
		}
	}
int main()
{
	Game_Init();

	while (true)
	{
		Game_Draw();
		Snake_Move();
		Key_Concrol();
		Eat_Food();		
		Sleep(50);
	}
	system("pause");
	return 0;
}