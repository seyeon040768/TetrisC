#pragma once

char** InitBlockStack(int height, int width);
int CheckBlockOverlap(char** blockStack, int height, int width, char* block, int blockHeight, int blockWidth, int y, int x);
void AddBlock2Stack(char** blockStack, int height, int width, char* block, int blockHeight, int blockWidth, int y, int x);
int CheckGameEnded(char** blockStack, int height, int width, int endedHeight);