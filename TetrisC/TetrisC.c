#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#include "GameArea.h"
#include "BlockStack.h"
#include "Block.h"

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
	int score = 0;

	BlockInfo blockInfo = GenerateRandomBlock();

	int y = 0, x = GAME_AREA_WIDTH / 2;

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
				{
					Block block = Block2Char(blockInfo, BLOCK, NULL, NULL);

					if (!CheckBlockOverlap(blockStack, GAME_AREA_HEIGHT, GAME_AREA_WIDTH, block, y, x - 1))
					{
						--x;

						refreshScreen = 1;
					}

					free(block.block);
					break;
				}
				case RIGHT:
				{
					Block block = Block2Char(blockInfo, BLOCK, NULL, NULL);

					if (!CheckBlockOverlap(blockStack, GAME_AREA_HEIGHT, GAME_AREA_WIDTH, block, y, x + 1))
					{
						++x;

						refreshScreen = 1;
					}

					free(block.block);
					break;
				}
				case UP:
				{
					BlockInfo rotatedBlockInfo = blockInfo;
					rotatedBlockInfo.direction = (rotatedBlockInfo.direction + 1) % 4;

					int dy = 0, dx = 0;
					Block block = Block2Char(rotatedBlockInfo, BLOCK, &dy, &dx);

					if (!CheckBlockOverlap(blockStack, GAME_AREA_HEIGHT, GAME_AREA_WIDTH, block, y + dy, x + dx))
					{
						y += dy;
						x += dx;

						blockInfo = rotatedBlockInfo;

						refreshScreen = 1;
					}

					free(block.block);
					break;
				}
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

			Block block = Block2Char(blockInfo, BLOCK, NULL, NULL);

			if (CheckBlockOverlap(blockStack, GAME_AREA_HEIGHT, GAME_AREA_WIDTH, block, y + 1, x))
			{
				AddBlock2Stack(blockStack, GAME_AREA_HEIGHT, GAME_AREA_WIDTH, block, y, x);

				y = 0;
				x = GAME_AREA_WIDTH / 2;

				RemoveFullLine(blockStack, GAME_AREA_HEIGHT, GAME_AREA_WIDTH, &score);

				blockInfo = GenerateRandomBlock();
			}
			else
			{
				++y;
			}

			free(block.block);

			refreshScreen = 1;
		}

		if (refreshScreen)
		{
			refreshScreen = 0;

			Block block = Block2Char(blockInfo, BLOCK, NULL, NULL);
			DrawFallingBlock2GameArea(gameArea, GAME_AREA_HEIGHT, GAME_AREA_WIDTH, block, y, x);
			free(block.block);

			system("cls || clear");

			PrintGameArea(gameArea, blockStack, GAME_AREA_HEIGHT, GAME_AREA_WIDTH, GAME_AREA_EDGE);

			printf("Score: %d\n", score);
		}
	}

	FreeGameArea(gameArea, GAME_AREA_HEIGHT);
	FreeBlockStack(blockStack, GAME_AREA_HEIGHT);

	printf("Game Over!\n");

	return 0;
}