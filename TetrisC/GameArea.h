#pragma once

char** InitGameArea(int height, int width);
void ClearGameArea(char** gameArea, int height, int width);
void DrawFallingBlock2GameArea(char** gameArea, int height, int width, char* block, int blockHeight, int blockWidth, int y, int x);
void PrintGameArea(char** gameArea, char** blockStack, int height, int width, char edge);