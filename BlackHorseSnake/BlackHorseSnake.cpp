// BlackHorseSnake.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include "Wall.h"
#include "Snake.h"
#include "Food.h"


using namespace std;

int main()
{
	srand((unsigned int) time(NULL));

	Wall wall;
	Food food(wall);
	Snake snake(wall, food);
	bool isDead = false;
	char preKey = NULL;
	wall.init();	
	snake.init();
	food.setFood();
	
	wall.drawWall();

	while (!isDead) {
		char key = _getch();
		if (preKey == NULL && key == snake.LEFT) {
			continue;
		}
		do {
			if (key == snake.UP || key == snake.DOWN || key == snake.LEFT || key == snake.RIGHT) {
				// 判断当前按键是否有上次冲突
				if (
					(key == snake.LEFT && preKey == snake.RIGHT)
					|| (key == snake.RIGHT && preKey == snake.LEFT)
					|| (key == snake.UP && preKey == snake.DOWN)
					|| (key == snake.DOWN && preKey == snake.UP)
				) {
					key = preKey;
				}
				else
				{
					preKey = key;
				}
				
				if (snake.move(key) == true) {
					wall.drawWall();
					Sleep(50);
				}
				else {
					isDead = true;
					break;
				}
			}
			else {
				key = preKey;
				continue;
			}
		} while (!_kbhit());// when no user keyboard input, _kbhit() returns 0;
	}

	system("pause");
    return 0;
}

