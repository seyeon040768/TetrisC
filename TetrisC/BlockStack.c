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