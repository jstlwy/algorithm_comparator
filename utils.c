#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int *array, int arraySize)
{
	for(int i = 0; i < arraySize; i = i + 1)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}

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

int* copyIntArray(int* oldArray, int arraySize)
{
    int* newArray = malloc(arraySize * sizeof(int));
    for(int i = 0; i < arraySize; i = i + 1)
    {
        newArray[i] = oldArray[i];
    }
    return newArray;
}