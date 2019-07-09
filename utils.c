#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

int randomNum(int a, int b)
{
	int low, high;
	if(a < b)
	{
		low = a;
		high = b;
	}
	else if(a > b)
	{
		low = b;
		high = a;
	}
	else
	{
		return a;
	}
	int difference = high - low;
	return (rand() % difference) + low;
}

void printIntArray(int *array, int arraySize)
{
	for(int i = 0; i < arraySize; i = i + 1)
	{
		printf("%d ", array[i]);
	}
}

void printIntArrayCurses(int *array, int arraySize)
{
	for(int i = 0; i < arraySize; i = i + 1)
	{
		printw("%d ", array[i]);
	}
}

int* copyIntArray(int* oldArray, int arraySize)
{
    int* newArray = malloc(arraySize * sizeof(int));
    for(int i = 0; i < arraySize; i = i + 1)
    {
        newArray[i] = oldArray[i];
    }
    return newArray;
}

int timeDiff(struct timeval start, struct timeval stop)
{
	int start_usec;
	int stop_usec;
	int diff;
	start_usec = start.tv_usec + start.tv_sec * 1000000;
	stop_usec = stop.tv_usec + stop.tv_sec * 1000000; 
	diff = stop_usec - start_usec;
	return diff;
}

void waitForEnter()
{
	printw("Press Enter to continue.");
	refresh();
	int keyInput = 0;
	while(keyInput != KEY_ENTER && keyInput != 10)
	{
		keyInput = getch();
	}
}