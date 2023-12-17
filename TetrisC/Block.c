#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Block.h"

BlockInfo GenerateRandomBlock()
{
	srand(time(NULL));

	BlockInfo blockInfo = { .size = 0, .blockCode = 0, .direction = 0 };
	blockInfo.blockCode = rand() % BlockCount;

	if (blockInfo.blockCode == BCStraight)
	{
		blockInfo.size = 4;
	}
	else if (blockInfo.blockCode == BCSquare)
	{
		blockInfo.size = 2;
	}
	else
	{
		blockInfo.size = 3;
	}

	blockInfo.direction = rand() % 4;

	return blockInfo;
}

Block Block2Char(BlockInfo blockInfo, char blockChar)
{
	char straightBlock[] = {
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0
	};
	char squareBlock[] = {
		1, 1,
		1, 1
	};
	char zBlock[] = {
		1, 1, 0,
		0, 1, 1,
		0, 0, 0
	};
	char sBlock[] = {
		0, 1, 1,
		1, 1, 0,
		0, 0, 0
	};
	char jBlock[] = {
		0, 0, 1,
		0, 0, 1,
		0, 1, 1
	};
	char lBlock[] = {
		1, 0, 0,
		1, 0, 0,
		1, 1, 0
	};
	char tBlock[] = {
		0, 0, 0,
		0, 1, 0,
		1, 1, 1
	};

	char* blocks[] = { straightBlock, squareBlock, zBlock, sBlock, jBlock, lBlock, tBlock };


	Block block = { .block = NULL, .height = 0, .width = 0 };
	block.block = (char*)malloc(blockInfo.size * blockInfo.size * sizeof(char));
	memcpy(block.block, blocks[blockInfo.blockCode], blockInfo.size * blockInfo.size * sizeof(char));

	for (int i = 0; i < blockInfo.direction; ++i)
	{
		RotateBlock(block.block, blockInfo.size);
	}

	MakeTightBlock(&block, blockInfo);

	for (int i = 0; i < block.height; ++i)
	{
		for (int j = 0; j < block.width; ++j)
		{
			*(block.block + i * block.width + j) = (*(block.block + i * block.width + j) == 1) ? blockChar : 0;
		}
	}

	return block;
}

/// <summary>
/// Rotate block 90 degrees clockwise
/// </summary>
/// <param name="block">Block pointer</param>
/// <param name="size">the length of the longest side</param>
void RotateBlock(char* block, int size)
{
	char* temp = (char*)malloc(size * size * sizeof(char));
	if (temp == NULL)
	{
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			*(temp + j * size + (size - 1 - i)) = *(block + i * size + j);
		}
	}

	memcpy(block, temp, size * size * sizeof(char));

	free(temp);
}

void MakeTightBlock(Block* block, BlockInfo blockInfo)
{
	char* temp = NULL;

	int top = blockInfo.size - 1;
	int bottom = 0;
	int left = blockInfo.size - 1;
	int right = 0;

	for (int i = 0; i < blockInfo.size; ++i)
	{
		for (int j = 0; j < blockInfo.size; ++j)
		{
			if (*(block->block + i * blockInfo.size + j))
			{
				top = (i < top) ? i : top;
				bottom = (i > bottom) ? i : bottom;
				left = (j < left) ? j : left;
				right = (j > right) ? j : right;
			}
		}
	}

	block->height = bottom - top + 1;
	block->width = right - left + 1;

	
	temp = (char*)malloc(block->height * block->width * sizeof(char));
	if (temp == NULL)
	{
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < block->height; ++i)
	{
		for (int j = 0; j < block->width; ++j)
		{
			*(temp + i * block->width + j) = *(block->block + (top + i) * blockInfo.size + (left + j));
		}
	}

	free(block->block);
	block->block = temp;
}