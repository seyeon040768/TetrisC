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

void sleep(int millisecond)
{
	clock_t startTime = clock();

	while (clock() < startTime + millisecond);
}

int main(void)
{
	char** gameArea = InitGameArea(GAME_AREA_HEIGHT, GAME_AREA_WIDTH);
	char** blockStack = InitBlockStack(GAME_AREA_HEIGHT, GAME_AREA_WIDTH);

	char block[4] = { BLOCK, BLOCK, BLOCK, BLOCK };

	int y = 0, x = 0;

	while (1)
	{
		ClearGameArea(gameArea, GAME_AREA_HEIGHT, GAME_AREA_WIDTH);

		if (!CheckBlockOverlap(blockStack, GAME_AREA_HEIGHT, GAME_AREA_WIDTH, block, 1, 4, y + 1, 0))
		{
			++y;
		}

		DrawFallingBlock2GameArea(gameArea, GAME_AREA_HEIGHT, GAME_AREA_WIDTH, block, 1, 4, y, 0);

		sleep(SLEEP_TIME);
		system("cls || clear");
		
		PrintGameArea(gameArea, blockStack, GAME_AREA_HEIGHT, GAME_AREA_WIDTH, GAME_AREA_EDGE);
	}

	return 0;
}