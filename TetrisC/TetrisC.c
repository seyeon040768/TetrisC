#include <stdio.h>
#include <time.h>
#include <conio.h>

#define SLEEP_TIME 2000

#define GAME_AREA_HEIGHT 20
#define GAME_AREA_WIDTH 10
#define GAME_AREA_EDGE '+'

#define BLOCK '#'

void sleep(int millisecond)
{
	clock_t startTime = clock();

	while (clock() < startTime + millisecond);
}

void ClearGameArea(char* gameArea, int height, int width)
{
	for (int h = 0; h < height; ++h)
	{
		for (int w = 0; w < width; ++w)
		{
			*(gameArea + h * width + w) = ' ';
		}
	}
}

void PrintGameArea(char* gameArea, int height, int width)
{
	for (int i = 0; i < width + 2; ++i)
	{
		printf("%c", GAME_AREA_EDGE);
	}
	printf("\n");

	for (int h = 0; h < height; ++h)
	{
		printf("%c", GAME_AREA_EDGE);
		for (int w = 0; w < width; ++w)
		{
			printf("%c", *(gameArea + h * width + w));
		}
		printf("%c\n", GAME_AREA_EDGE);
	}

	for (int i = 0; i < width + 2; ++i)
	{
		printf("%c", GAME_AREA_EDGE);
	}
	printf("\n");
}

void DrawBlock(char* gameArea, int height, int width, char* block, int blockHeight, int blockWidth, int y, int x)
{
	if (y < 0 || y + blockHeight > height || x < 0 || x + blockWidth > width)
	{
		//

		return;
	}

	for (int h = 0; h < blockHeight; ++h)
	{
		for (int w = 0; w < blockWidth; ++w)
		{
			*(gameArea + (y + h) * width + x + w) = *(block + h * blockWidth + w);
		}
	}
}

int main(void)
{
	char gameArea[GAME_AREA_HEIGHT][GAME_AREA_WIDTH];

	char block[4] = { BLOCK, BLOCK, BLOCK, BLOCK };

	int y = 0, x = 0;

	while (1)
	{
		ClearGameArea(gameArea, GAME_AREA_HEIGHT, GAME_AREA_WIDTH);

		DrawBlock(gameArea, GAME_AREA_HEIGHT, GAME_AREA_WIDTH, block, 1, 4, y++, 0);

		sleep(SLEEP_TIME);
		system("cls || clear");
		
		PrintGameArea(gameArea, GAME_AREA_HEIGHT, GAME_AREA_WIDTH);
	}

	return 0;
}