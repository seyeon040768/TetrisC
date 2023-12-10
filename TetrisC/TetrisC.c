#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#include "GameArea.h"
#include "BlockStack.h"

#define SLEEP_TIME 1000

#define GAME_AREA_HEIGHT 20
#define GAME_AREA_WIDTH 10
#define GAME_AREA_EDGE '+'

#define BLOCK '#'

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

// top is 0
#define GAME_END_HEIGHT 1

int main(void)
{
	int refreshScreen = 0;

	clock_t startTime = clock();

	char** gameArea = InitGameArea(GAME_AREA_HEIGHT, GAME_AREA_WIDTH);
	char** blockStack = InitBlockStack(GAME_AREA_HEIGHT, GAME_AREA_WIDTH);
	char input;

	int speed = 1;

	char block[2][2] = { {BLOCK, BLOCK}, {BLOCK, BLOCK} };

	int y = 0, x = 0;

	while (!CheckGameEnded(blockStack, GAME_AREA_HEIGHT, GAME_AREA_WIDTH, GAME_END_HEIGHT))
	{
		ClearGameArea(gameArea, GAME_AREA_HEIGHT, GAME_AREA_WIDTH);

		if (_kbhit())
		{
			input = _getch();
			if (input == -32)
			{
				input = _getch();
				switch (input)
				{
				case LEFT:
					if (!CheckBlockOverlap(blockStack, GAME_AREA_HEIGHT, GAME_AREA_WIDTH, block, 2, 2, y, x - 1))
					{
						--x;

						refreshScreen = 1;
					}
					break;
				case RIGHT:
					if (!CheckBlockOverlap(blockStack, GAME_AREA_HEIGHT, GAME_AREA_WIDTH, block, 2, 2, y, x + 1))
					{
						++x;

						refreshScreen = 1;
					}
					break;
				case UP:

					break;
				case DOWN:
					speed = 20;
					break;
				}
			}
		}
		else
		{
			speed = 1;
		}

		if (clock() - startTime > SLEEP_TIME / speed)
		{
			startTime = clock();

			if (CheckBlockOverlap(blockStack, GAME_AREA_HEIGHT, GAME_AREA_WIDTH, block, 2, 2, y + 1, x))
			{
				AddBlock2Stack(blockStack, GAME_AREA_HEIGHT, GAME_AREA_WIDTH, block, 2, 2, y, x);

				y = 0;

				RemoveFullLine(blockStack, GAME_AREA_HEIGHT, GAME_AREA_WIDTH);
			}
			else
			{
				++y;
			}

			refreshScreen = 1;
		}

		if (refreshScreen)
		{
			refreshScreen = 0;

			DrawFallingBlock2GameArea(gameArea, GAME_AREA_HEIGHT, GAME_AREA_WIDTH, block, 2, 2, y, x);

			system("cls || clear");

			PrintGameArea(gameArea, blockStack, GAME_AREA_HEIGHT, GAME_AREA_WIDTH, GAME_AREA_EDGE);
		}
	}

	FreeGameArea(gameArea, GAME_AREA_HEIGHT);
	FreeBlockStack(blockStack, GAME_AREA_HEIGHT);

	printf("Game Over!\n");

	return 0;
}