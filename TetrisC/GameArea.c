#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** InitGameArea(int height, int width)
{
	char** gameArea = NULL;
	gameArea = (char**)malloc(height * sizeof(char*));
	if (gameArea == NULL)
	{
		exit(EXIT_FAILURE);
	}

	for (int h = 0; h < height; ++h)
	{
		*(gameArea + h) = (char*)malloc(width * sizeof(char));
		if (*(gameArea + h) == NULL)
		{
			exit(EXIT_FAILURE);
		}

		memset(*(gameArea + h), ' ', width * sizeof(char));
	}

	return gameArea;
}

void ClearGameArea(char** gameArea, int height, int width)
{
	for (int h = 0; h < height; ++h)
	{
		memset(*(gameArea + h), ' ', width * sizeof(char));
	}
}

void DrawFallingBlock2GameArea(char** gameArea, int height, int width, char* block, int blockHeight, int blockWidth, int y, int x)
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
			*(*(gameArea + y + h) + x + w) = *(block + h * blockWidth + w);
		}
	}
}

void PrintGameArea(char** gameArea, char** blockStack, int height, int width, char edge)
{
	for (int i = 0; i < width + 2; ++i)
	{
		printf("%c", edge);
	}
	printf("\n");

	for (int h = 0; h < height; ++h)
	{
		printf("%c", edge);
		for (int w = 0; w < width; ++w)
		{
			if (*(*(blockStack + h) + w) != ' ')
			{
				*(*(gameArea + h) + w) = *(*(blockStack + h) + w);
			}

			printf("%c", *(*(gameArea + h) + w));
		}
		printf("%c\n", edge);
	}

	for (int i = 0; i < width + 2; ++i)
	{
		printf("%c", edge);
	}
	printf("\n");
}