#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** InitBlockStack(int height, int width)
{
	char** blockStack = NULL;
	blockStack = (char**)malloc(height * sizeof(char*));
	if (blockStack == NULL)
	{
		exit(EXIT_FAILURE);
	}

	for (int h = 0; h < height; ++h)
	{
		*(blockStack + h) = (char*)malloc(width * sizeof(char));
		if (*(blockStack + h) == NULL)
		{
			exit(EXIT_FAILURE);
		}

		memset(*(blockStack + h), ' ', width * sizeof(char));
	}

	return blockStack;
}

int CheckBlockOverlap(char** blockStack, int height, int width, char* block, int blockHeight, int blockWidth, int y, int x)
{
	if (y < 0 || y + blockHeight > height || x < 0 || x + blockWidth > width)
	{
		return 1;
	}

	for (int h = 0; h < blockHeight; ++h)
	{
		for (int w = 0; w < blockWidth; ++w)
		{
			if (*(block + h * blockWidth + w) != ' ' && *(*(blockStack + y + h) + x + w) != ' ')
			{
				return 1;
			}
		}
	}

	return 0;
}

void AddBlock2Stack(char** blockStack, int height, int width, char* block, int blockHeight, int blockWidth, int y, int x)
{
	for (int h = 0; h < blockHeight; ++h)
	{
		for (int w = 0; w < blockWidth; ++w)
		{
			if (*(block + h * blockWidth + w) != ' ')
			{
				*(*(blockStack + y + h) + x + w) = *(block + h * blockWidth + w);
			}
		}
	}
}