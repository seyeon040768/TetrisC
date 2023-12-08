#include <stdio.h>
#include <time.h>
#include <conio.h>

#define SLEEP_TIME 2000
#define GAME_AREA_HEIGHT 20
#define GAME_AREA_WIDTH 10

void sleep(int millisecond)
{
	clock_t startTime = clock();

	while (clock() < startTime + millisecond);
}

void ClearGameArea(char* gameArea, int height, int width)
{
	int h = 0, w = 0;

	for (w = 0; w < width; ++w)
	{
		*(gameArea + w) = '+';
		*(gameArea + (height - 1) * width + w) = '+';
	}

	for (h = 1; h < height - 1; ++h)
	{
		*(gameArea + h * width) = '+';
		for (w = 1; w < width - 1; ++w)
		{
			*(gameArea + h * width + w) = ' ';
		}
		*(gameArea + h * width + w) = '+';
	}
}

void PrintGameArea(char* gameArea, int height, int width)
{
	for (int h = 0; h < height; ++h)
	{
		for (int w = 0; w < width; ++w)
		{
			printf("%c", *(gameArea + h * width + w));
		}
		printf("\n");
	}
}

int main(void)
{
	int i = 0; // for test

	char gameArea[GAME_AREA_HEIGHT + 2][GAME_AREA_WIDTH + 2];

	while (1)
	{
		ClearGameArea(&gameArea, GAME_AREA_HEIGHT + 2, GAME_AREA_WIDTH + 2);
		PrintGameArea(&gameArea, GAME_AREA_HEIGHT + 2, GAME_AREA_WIDTH + 2);

		sleep(SLEEP_TIME);
		system("cls || clear");
	}

	return 0;
}