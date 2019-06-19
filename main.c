#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "input.h"
#include "sort.h"
#include "linklist.h"

void printArray(int*, int);
int randomNum(int a, int b);

int main()
{
	srand(time(0));
	const int ARRAY_LENGTH = 100;
	const int MENU_MIN = 0;
	const int MENU_MAX = 3;
	int array[ARRAY_LENGTH];
	int choice;
	struct timespec start, stop;
	MaxSA msdata;

	do
	{
		printf("\nChoose your sorting method:\n");
		printf("1. Insertion Sort\n");
		printf("2. Merge Sort\n");
		printf("3. Maximum Subarray\n");
		printf("0. Quit\n");

		choice = getIntInput(3);

		if(choice == 0)
		{
			printf("\nGoodbye.\n\n");
		}
		else if(choice < MENU_MIN || choice > MENU_MAX)
		{
			printf("\nInvalid input.  Please try again.\n");
		}
		else
		{
			printf("\n");

			// Insert random numbers into array
			for(int i = 0; i < ARRAY_LENGTH; i = i + 1)
			{
				array[i] = randomNum(-1000, 1000);
			}
			printArray(array, ARRAY_LENGTH);

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
				case 3:
					clock_gettime(CLOCK_MONOTONIC, &start);
					msdata = findMaxSubarray(array, 0, ARRAY_LENGTH - 1);
					clock_gettime(CLOCK_MONOTONIC, &stop);
					printf("\nMax Subarray:\n");
					for(int i = msdata.lowIndex; i <= msdata.highIndex; i++)
					{
						printf("%d ", array[i]);
					}
					printf("\n\nMax Subarray Sum: %d\n", msdata.maxSum);
					break;
			}
			//printArray(array, ARRAY_LENGTH);
			printf("\nTime elapsed: %ld ns\n", stop.tv_nsec - start.tv_nsec);
		}
	}
	while(choice != 0);

	return 0;
}

void printArray(int *array, int arraySize)
{
	printf("Original array:\n");
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