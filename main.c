#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "input.h"
#include "utils.h"
#include "arraysort.h"
#include "linklist.h"
#include "llsort.h"

#define ARRAY_LENGTH 100

void arraySortTest();
void linkedListTest();
void linkedListSortTest();
void maxSubarrayTest();

int main()
{
	srand(time(0));
	const int MENU_MIN = 0;
	const int MENU_MAX = 4;
	int choice;

	do
	{
		printf("\nDATA STRUCTURES AND ALGORITHMS TEST BENCH\n");
		printf("1. Array Sorting Algorithms\n");
		printf("2. Linked List Test\n");
		printf("3. Linked List Sorting Algorithms\n");
		printf("4. Maximum Subarray\n");
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
					linkedListTest();
					break;
				case 3:
					linkedListSortTest();
					break;
				case 4:
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
	struct timespec start, stop;

	for(int i = 0; i < NUM_SORT_TYPES; i = i + 1)
	{
		printf("\n%s\n", sortHeaders[i]);
		int* newArray = copyIntArray(array, ARRAY_LENGTH);
		printf("\nUnsorted Array:\n");
		printArray(newArray, ARRAY_LENGTH);

		switch(i)
		{
			case 0: // INSERTION SORT
				clock_gettime(CLOCK_MONOTONIC, &start);
				insertionSort(newArray, ARRAY_LENGTH);
				clock_gettime(CLOCK_MONOTONIC, &stop);
				break;
			case 1: // MERGE SORT
				clock_gettime(CLOCK_MONOTONIC, &start);
				mergeSort(newArray, 0, ARRAY_LENGTH - 1);
				clock_gettime(CLOCK_MONOTONIC, &stop);
				break;
			default:
				break;
		}

		printf("\nSorted Array:\n");
		printArray(newArray, ARRAY_LENGTH);
		printf("\nTime elapsed: %ld ns\n\n", stop.tv_nsec - start.tv_nsec);
		free(newArray);
	}
}

void linkedListTest()
{
	int listSize = 10;
	List* intList = initList();
	for(int i = 0; i < listSize; i = i + 1)
	{
		int* newInt = malloc(sizeof(int));
		*newInt = randomNum(-1000, 1000);
		insertAtTail(intList, newInt);
	}
	printf("Size of list: %d\n", intList->size);
	Node* headNode = intList->first;
	while(headNode != NULL)
	{
		int* listNumPtr = headNode->data;
		printf("%d\n", *listNumPtr);
		headNode = headNode->next;
	}
	deleteList(intList);
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

	const int NUM_SORT_TYPES = 2;
	char* sortHeaders[NUM_SORT_TYPES];
	sortHeaders[0] = "INSERTION SORT";
	sortHeaders[1] = "MERGE SORT";
	struct timespec start, stop;

	for(int i = 0; i < NUM_SORT_TYPES; i = i + 1)
	{
		printf("\n%s\n", sortHeaders[i]);
		List* newList = copyIntList(intList);
		printf("\nUnsorted List:\n");
		printIntList(newList);

		switch(i)
		{
			case 0: // INSERTION SORT
				clock_gettime(CLOCK_MONOTONIC, &start);
				insertionSortIntLL(newList);
				clock_gettime(CLOCK_MONOTONIC, &stop);
				break;
			case 1: // MERGE SORT
				clock_gettime(CLOCK_MONOTONIC, &start);
				mergeSortIntLL(newList->first, newList->last, newList->size);
				clock_gettime(CLOCK_MONOTONIC, &stop);
				break;
			default:
				break;
		}

		printf("\nSorted List:\n");
		printIntList(newList);
		printf("\nTime elapsed: %ld ns\n\n", stop.tv_nsec - start.tv_nsec);
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

	MaxSA msdata;
	struct timespec start, stop;
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
}