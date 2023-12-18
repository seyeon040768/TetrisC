#pragma once

#define BlockCount 7

enum BlockCode
{
	BCStraight,
	BCSquare,
	BCZ,
	BCS,
	BCJ,
	BCL,
	BCT,
};

typedef struct BlockInfo
{
	int size;
	int blockCode;
	int direction;
} BlockInfo;

typedef struct Block
{
	char* block;
	int height;
	int width;
} Block;

BlockInfo GenerateRandomBlock();
Block Block2Char(BlockInfo blockInfo, char blockChar, int* dy, int* dx);
void RotateBlock(char* block, int size);
void CropBlock(const Block* block, BlockInfo blockInfo, int* top, int* bottom, int* left, int* right);
void MakeTightBlock(Block* block, BlockInfo blockInfo);