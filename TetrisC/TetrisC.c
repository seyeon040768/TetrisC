#include <stdio.h>
#include <time.h>
#include <conio.h>

#define SLEEP_TIME 2000

void sleep(int millisecond)
{
	clock_t startTime = clock();

	while (clock() < startTime + millisecond);
}

int main(void)
{
	int i = 0; // for test

	while (1)
	{
		printf("%d", i);
		++i;

		sleep(SLEEP_TIME);
		system("cls || clear");
	}

	return 0;
}