#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "input.h"
#include "utils.h"
#include "arraysort.h"
#include "linklist.h"
#include "listsort.h"

#define ARRAY_LENGTH 100000

void arraySortTest();
void linkedListTest();
void linkedListSortTest();
void maxSubarrayTest();

int main()
{
	srand(time(0));
	const int MENU_MIN = 0;
	const int MENU_MAX = 3;
	int choice;

	do
	{
		printf("\nDATA STRUCTURES AND ALGORITHMS TEST SUITE\n");
		printf("1. Array Sorting Algorithms\n");
		printf("2. Linked List Sorting Algorithms\n");
		printf("3. Maximum Subarray\n");
		printf("0. Quit\n");

		choice = getIntInput(2);

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
			switch(choice)
			{
				case 1:
					arraySortTest();
					break;
				case 2:
					linkedListSortTest();
					break;
				case 3:
					maxSubarrayTest();
					break;
			}
		}
	}
	while(choice != 0);

	return 0;
}

void arraySortTest()
{
	int array[ARRAY_LENGTH];
	for(int i = 0; i < ARRAY_LENGTH; i = i + 1)
	{
		array[i] = randomNum(-1000, 1000);
	}

	const int NUM_SORT_TYPES = 2;
	char* sortHeaders[NUM_SORT_TYPES];
	sortHeaders[0] = "INSERTION SORT";
	sortHeaders[1] = "MERGE SORT";
	//struct timespec start, stop; 	// start.tv_nsec
	struct timeval start, stop;		// start.tv_usec

	for(int i = 0; i < NUM_SORT_TYPES; i = i + 1)
	{
		printf("\n%s\n", sortHeaders[i]);
		int* newArray = copyIntArray(array, ARRAY_LENGTH);
		//printf("\nUnsorted Array:\n");
		//printIntArray(newArray, ARRAY_LENGTH);

		switch(i)
		{
			case 0: // INSERTION SORT
				//clock_gettime(CLOCK_MONOTONIC, &start);
				gettimeofday(&start, NULL);
				insertionSort(newArray, ARRAY_LENGTH);
				//clock_gettime(CLOCK_MONOTONIC, &stop);
				gettimeofday(&stop, NULL);
				break;
			case 1: // MERGE SORT
				//clock_gettime(CLOCK_MONOTONIC, &start);
				gettimeofday(&start, NULL);
				mergeSort(newArray, 0, ARRAY_LENGTH - 1);
				//clock_gettime(CLOCK_MONOTONIC, &stop);
				gettimeofday(&stop, NULL);
				break;
			default:
				break;
		}

		//printf("\nSorted Array:\n");
		//printIntArray(newArray, ARRAY_LENGTH);
		//printf("\nTime elapsed: %ld ns\n\n", stop.tv_nsec - start.tv_nsec);
		int usecPassed = timeDiff(start, stop);
		printf("\nTime elapsed: %d us\n\n", usecPassed);
		free(newArray);
	}
}

void linkedListSortTest()
{
	List* intList = initList();
	for(int i = 0; i < ARRAY_LENGTH; i = i + 1)
	{
		int* newInt = malloc(sizeof(int));
		*newInt = randomNum(-1000, 1000);
		insertAtTail(intList, newInt);
	}

	const int NUM_SORT_TYPES = 3;
	char* sortHeaders[NUM_SORT_TYPES];
	sortHeaders[0] = "INSERTION SORT";
	sortHeaders[1] = "MERGE SORT 1";
	sortHeaders[2] = "MERGE SORT 2";
	//struct timespec start, stop; 	// start.tv_nsec
	struct timeval start, stop;		// start.tv_usec

	for(int i = 0; i < NUM_SORT_TYPES; i = i + 1)
	{
		printf("\n%s\n", sortHeaders[i]);
		List* newList = copyIntList(intList);
		//printf("\nUnsorted List:\n");
		//printIntList(newList);

		switch(i)
		{
			case 0: // INSERTION SORT
				//clock_gettime(CLOCK_MONOTONIC, &start);
				gettimeofday(&start, NULL);
				insertionSortIntLL(newList);
				//clock_gettime(CLOCK_MONOTONIC, &stop);
				gettimeofday(&stop, NULL);
				break;
			case 1: // MERGE SORT 1
				//clock_gettime(CLOCK_MONOTONIC, &start);
				gettimeofday(&start, NULL);
				newList->first = mergeSortList(newList->first);
				//clock_gettime(CLOCK_MONOTONIC, &stop);
				gettimeofday(&stop, NULL);
				break;
			case 2: // MERGE SORT 2
				//clock_gettime(CLOCK_MONOTONIC, &start);
				gettimeofday(&start, NULL);
				newList->first = mergeSortSedg(newList->first);
				//clock_gettime(CLOCK_MONOTONIC, &stop);
				gettimeofday(&stop, NULL);
				break;
			default:
				break;
		}

		//printf("\nSorted List:\n");
		//printIntList(newList);
		//printf("\nTime elapsed: %ld ns\n\n", stop.tv_nsec - start.tv_nsec);
		int usecPassed = timeDiff(start, stop);
		printf("\nTime elapsed: %d us\n\n", usecPassed);
		deleteList(newList);
	}

	deleteList(intList);
}

void maxSubarrayTest()
{
	int array[ARRAY_LENGTH];
	for(int i = 0; i < ARRAY_LENGTH; i = i + 1)
	{
		array[i] = randomNum(-1000, 1000);
	}
	printf("\nOriginal Array:\n");
	printIntArray(array, ARRAY_LENGTH);

	MaxSA msdata;
	//struct timespec start, stop; 	// start.tv_nsec
	struct timeval start, stop;		// start.tv_usec
	//clock_gettime(CLOCK_MONOTONIC, &start);
	gettimeofday(&start, NULL);
	msdata = findMaxSubarray(array, 0, ARRAY_LENGTH - 1);
	//clock_gettime(CLOCK_MONOTONIC, &stop);
	gettimeofday(&stop, NULL);

	printf("\nMax Subarray:\n");
	for(int i = msdata.lowIndex; i <= msdata.highIndex; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n\nMax Subarray Sum: %d\n", msdata.maxSum);

	//printf("\nTime elapsed: %ld ns\n", stop.tv_nsec - start.tv_nsec);
	int usecPassed = timeDiff(start, stop);
	printf("\nTime elapsed: %d us\n\n", usecPassed);
}