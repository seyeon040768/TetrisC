#pragma once

char** InitGameArea(int height, int width);
void ClearGameArea(char** gameArea, int height, int width);
void PrintGameArea(char** gameArea, char** blockStack, int height, int width, char edge);