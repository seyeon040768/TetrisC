#include <stdio.h>
#include <time.h>
#include <conio.h>

#define SLEEP_TIME 2000

#define GAME_AREA_HEIGHT 20
#define GAME_AREA_WIDTH 10
#define GAME_AREA_EDGE '+'

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

int main(void)
{
	char gameArea[GAME_AREA_HEIGHT][GAME_AREA_WIDTH];

	while (1)
	{
		ClearGameArea(gameArea, GAME_AREA_HEIGHT, GAME_AREA_WIDTH);

		sleep(SLEEP_TIME);
		system("cls || clear");
		
		PrintGameArea(gameArea, GAME_AREA_HEIGHT, GAME_AREA_WIDTH);
	}

	return 0;
}