#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "input.h"
#include "utils.h"
#include "sort.h"
#include "linklist.h"

void sortTest(int* array, int arraySize, int sortType, char* sortHeader);

int main()
{
	srand(time(0));
	struct timespec start, stop;
	
	const int ARRAY_LENGTH = 100;
	const int MENU_MIN = 0;
	const int MENU_MAX = 3;
	int array[ARRAY_LENGTH];
	int choice;

	const int NUM_SORT_TYPES = 2;
	char* sortHeaders[NUM_SORT_TYPES];
	sortHeaders[0] = "INSERTION SORT";
	sortHeaders[1] = "MERGE SORT";
	
	MaxSA msdata;

	LLNode* head = malloc(sizeof(LLNode));
	head->rank = 0;
	head->previous = NULL;
	head->next = NULL;

	do
	{
		printf("\nDATA STRUCTURES AND ALGORITHMS TEST BENCH\n");
		printf("1. Array Sorting Algorithm Comparison\n");
		printf("2. Maximum Subarray\n");
		printf("0. Quit\n");

		choice = getIntInput(3);

		if(choice == 0)
		{
			printf("\nGoodbye.\n\n");
		}
		else if(choice < MENU_MIN || choice > MENU_MAX)
		{
			printf("\nInvalid input.  Please try again.\n\n");
		}
		else
		{
			// Insert random numbers into array
			for(int i = 0; i < ARRAY_LENGTH; i = i + 1)
			{
				array[i] = randomNum(-1000, 1000);
			}

			switch(choice)
			{
				case 1:
					for(int i = 0; i < NUM_SORT_TYPES; i = i + 1)
					{
						sortTest(array, ARRAY_LENGTH, 0, sortHeaders[i]);
					}
					break;
				case 2:
					printf("\nOriginal Array:\n");
					printArray(array, ARRAY_LENGTH);
					clock_gettime(CLOCK_MONOTONIC, &start);
					msdata = findMaxSubarray(array, 0, ARRAY_LENGTH - 1);
					clock_gettime(CLOCK_MONOTONIC, &stop);
					printf("\nMax Subarray:\n");
					for(int i = msdata.lowIndex; i <= msdata.highIndex; i++)
					{
						printf("%d ", array[i]);
					}
					printf("\n\nMax Subarray Sum: %d\n", msdata.maxSum);
					printf("\nTime elapsed: %ld ns\n", stop.tv_nsec - start.tv_nsec);
					break;
			}
		}
	}
	while(choice != 0);

	return 0;
}

void sortTest(int* array, int arraySize, int sortType, char* sortHeader)
{
	struct timespec start, stop;
	printf("\n%s\n", sortHeader);
	int* newArray = copyIntArray(array, arraySize);
	printf("\nUnsorted Array:\n");
	printArray(newArray, arraySize);
	if(sortType == 0)
	{
		clock_gettime(CLOCK_MONOTONIC, &start);
		insertionSort(newArray, arraySize);
		clock_gettime(CLOCK_MONOTONIC, &stop);
	}
	else if(sortType == 1)
	{
		clock_gettime(CLOCK_MONOTONIC, &start);
		mergeSort(newArray, 0, arraySize - 1);
		clock_gettime(CLOCK_MONOTONIC, &stop);
	}
	printf("\nSorted Array:\n");
	printArray(newArray, arraySize);
	printf("\nTime elapsed: %ld ns\n\n", stop.tv_nsec - start.tv_nsec);
	free(newArray);
}