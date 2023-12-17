#pragma once

#include "Block.h"

char** InitGameArea(int height, int width);
void FreeGameArea(char** gameArea, int height);
void ClearGameArea(char** gameArea, int height, int width);
void DrawFallingBlock2GameArea(char** gameArea, int height, int width, Block block, int y, int x);
void PrintGameArea(char** gameArea, char** blockStack, int height, int width, char edge);