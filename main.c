#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "input.h"
#include "sort.h"
#include "linklist.h"

void printArray(int*, int);

int main()
{
	srand(time(NULL));
	const int ARRAY_LENGTH = 1000;
	int array[ARRAY_LENGTH];
	int choice;
	struct timespec start, stop;

	do
	{
		printf("Choose your sorting method:\n");
		printf("1. Insertion Sort\n");
		printf("2. Merge Sort\n");
		printf("0. Quit\n");

		choice = getIntInput(0, 2);

		if(choice == 0)
		{
			printf("\nGoodbye.\n\n");
		}
		else
		{
			printf("\n");

			// Insert random numbers into array
			for(int i = 0; i < ARRAY_LENGTH; i = i + 1)
			{
				array[i] = rand() % 1000;
			}
			//printArray(array, ARRAY_LENGTH);

			switch(choice)
			{
				case 1:
					clock_gettime(CLOCK_MONOTONIC, &start);
					insertionSort(array, ARRAY_LENGTH);
					clock_gettime(CLOCK_MONOTONIC, &stop);
					break;
				case 2:
					clock_gettime(CLOCK_MONOTONIC, &start);
					mergeSort(array, 0, ARRAY_LENGTH - 1);
					clock_gettime(CLOCK_MONOTONIC, &stop);
					break;
			}
			//printArray(array, ARRAY_LENGTH);
			printf("\n");
			printf("Time elapsed: %ld (ns)\n", stop.tv_nsec - start.tv_nsec);
		}
	}
	while(choice != 0);

	return 0;
}

void printArray(int *array, int arraySize)
{
	for(int i = 0; i < arraySize; i = i + 1)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}