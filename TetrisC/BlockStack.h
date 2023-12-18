#pragma once

#include "Block.h"

char** InitBlockStack(int height, int width);
void FreeBlockStack(char** blockStack, int height);
int CheckBlockOverlap(char** blockStack, int height, int width, Block block, int y, int x);
void AddBlock2Stack(char** blockStack, int height, int width, Block block, int y, int x);
void RemoveLine(char** blockStack, int height, int line);
void RemoveFullLine(char** blockStack, int height, int width, int* score);
int CheckGameEnded(char** blockStack, int height, int width, int endedHeight);