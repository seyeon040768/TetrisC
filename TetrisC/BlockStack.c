#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Block.h"

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

		memset(*(blockStack + h), 0, width * sizeof(char));
	}

	return blockStack;
}

void FreeBlockStack(char** blockStack, int height)
{
	for (int h = 0; h < height; ++h)
	{
		free(*(blockStack + h));
	}

	free(blockStack);
}

int CheckBlockOverlap(char** blockStack, int height, int width, Block block, int y, int x)
{
	if (y < 0 || y + block.height > height || x < 0 || x + block.width > width)
	{
		return 1;
	}

	for (int h = 0; h < block.height; ++h)
	{
		for (int w = 0; w < block.width; ++w)
		{
			if (*(block.block + h * block.width + w) && *(*(blockStack + y + h) + x + w))
			{
				return 1;
			}
		}
	}

	return 0;
}

void AddBlock2Stack(char** blockStack, int height, int width, Block block, int y, int x)
{
	for (int h = 0; h < block.height; ++h)
	{
		for (int w = 0; w < block.width; ++w)
		{
			if (*(block.block + h * block.width + w))
			{
				*(*(blockStack + y + h) + x + w) = *(block.block + h * block.width + w);
			}
		}
	}
}

void RemoveLine(char** blockStack, int height, int line)
{
	if (line < 0 || line > height - 1)
	{
		return;
	}

	free(*(blockStack + line));

	*(blockStack + line) = NULL;
}

void RemoveFullLine(char** blockStack, int height, int width, int* score)
{
	int isLineFull = 1;
	for (int h = height - 1; h >= 0; --h)
	{
		isLineFull = 1;
		for (int w = 0; w < width; ++w)
		{
			if (!*(*(blockStack + h) + w))
			{
				isLineFull = 0;
				break;
			}
		}

		if (isLineFull)
		{
			RemoveLine(blockStack, height, h);

			for (int i = h; i > 0; --i)
			{
				*(blockStack + i) = *(blockStack + i - 1);
			}

			*blockStack = (char*)malloc(width * sizeof(char));
			if (*blockStack == NULL)
			{
				exit(EXIT_FAILURE);
			}

			memset(*blockStack, 0, width * sizeof(char));

			++(*score);

			++h;
		}
	}
}

int CheckGameEnded(char** blockStack, int height, int width, int endedHeight)
{
	if (endedHeight < 0)
	{
		endedHeight = 0;
	}
	else if (endedHeight > height - 1)
	{
		endedHeight = height - 1;
	}

	for (int w = 0; w < width; ++w)
	{
		if (*(*(blockStack + endedHeight) + w))
		{
			return 1;
		}
	}

	return 0;
}