#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include "input.h"
#include "utils.h"
#include "arraysort.h"
#include "linklist.h"
#include "listsort.h"
#include "unionfind.h"

#define ARRAY_LENGTH 100000

void arraySortTest();
void linkedListTest();
void linkedListSortTest();
void maxSubarrayTest();
void unionFindTest();

int main(int argc, char *argv[])
{
	initscr();
	keypad(stdscr, true);
	noecho();
	curs_set(0);
	srand(time(0));

	char* menuOptions[] = {
		"Array Sorting Algorithms",
		"Linked List Sorting Algorithms",
		"Maximum Subarray",
		"Union Find",
		"Quit"
	};
	int numMenuOptions = 5;

	int keyInput = 0;
	int highlightedOption = 0;
	bool userSelectedQuit = false;
	while(userSelectedQuit == false)
	{
		erase();
		attron(A_BOLD);
		printw("DATA STRUCTURES AND ALGORITHMS TEST SUITE\n");
		attroff(A_BOLD);
		for(int i = 0; i < numMenuOptions; i = i + 1)
		{
			if(i == highlightedOption)
			{
				attron(A_STANDOUT);
			}
			printw("%d. ", i + 1);
			printw(menuOptions[i]);
			printw("\n");
			if(i == highlightedOption)
			{
				attroff(A_STANDOUT);
			}
		}
		refresh();

		keyInput = getch();
		if(keyInput == KEY_ENTER || keyInput == 10)
		{
			switch(highlightedOption)
			{
				case 0:
					arraySortTest();
					break;
				case 1:
					linkedListSortTest();
					break;
				case 2:
					maxSubarrayTest();
					break;
				case 3:
					unionFindTest();
				case 4:
					userSelectedQuit = true;
					break;
				default:
					break;
			}
		}
		else if(keyInput == KEY_UP && highlightedOption > 0)
		{
			highlightedOption = highlightedOption - 1;
		}
		else if(keyInput == KEY_DOWN && highlightedOption < numMenuOptions - 1)
		{
			highlightedOption = highlightedOption + 1;
		}
	}

	endwin();
	return 0;
}

void arraySortTest()
{
	erase();
	attron(A_BOLD);
	printw("Array Sorting Algorithms\n\n");
	attroff(A_BOLD);
	refresh();

	int array[ARRAY_LENGTH];
	for(int i = 0; i < ARRAY_LENGTH; i = i + 1)
	{
		array[i] = randomNum(-1000, 1000);
	}

	const int NUM_SORT_TYPES = 2;
	char* sortHeaders[NUM_SORT_TYPES];
	sortHeaders[0] = "Insertion Sort";
	sortHeaders[1] = "Merge Sort";
	//struct timespec start, stop; 	// start.tv_nsec
	struct timeval start, stop;		// start.tv_usec

	for(int i = 0; i < NUM_SORT_TYPES; i = i + 1)
	{
		printw("%s: ", sortHeaders[i]);
		refresh();
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
		printw("%d us\n", usecPassed);
		refresh();
		free(newArray);
	}

	printw("\n");
	waitForEnter();
}

void linkedListSortTest()
{
	erase();
	attron(A_BOLD);
	printw("Linked List Sorting Algorithms\n\n");
	attroff(A_BOLD);
	refresh();

	List* intList = initList();
	for(int i = 0; i < ARRAY_LENGTH; i = i + 1)
	{
		int* newInt = malloc(sizeof(int));
		*newInt = randomNum(-1000, 1000);
		insertAtTail(intList, newInt);
	}

	const int NUM_SORT_TYPES = 3;
	char* sortHeaders[NUM_SORT_TYPES];
	sortHeaders[0] = "Insertion Sort";
	sortHeaders[1] = "Merge Sort 1 (Sedgewick)";
	sortHeaders[2] = "Merge Sort 2 (Bijection)";
	//struct timespec start, stop; 	// start.tv_nsec
	struct timeval start, stop;		// start.tv_usec

	for(int i = 0; i < NUM_SORT_TYPES; i = i + 1)
	{
		List* newList = copyIntList(intList);
		printw("%s: ", sortHeaders[i]);
		//printf("\nUnsorted List:\n");
		//printIntList(newList);
		refresh();

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
				newList->first = mergeSortSedg(newList->first);
				//clock_gettime(CLOCK_MONOTONIC, &stop);
				gettimeofday(&stop, NULL);
				break;
			case 2: // MERGE SORT 2
				//clock_gettime(CLOCK_MONOTONIC, &start);
				gettimeofday(&start, NULL);
				newList->first = mergeSortList(newList->first);
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
		printw("%d us\n", usecPassed);
		refresh();
		deleteList(newList);
	}

	deleteList(intList);
	printw("\n");
	waitForEnter();
}

void maxSubarrayTest()
{
	erase();
	attron(A_BOLD);
	printw("Max Subarray Test\n\n");
	attroff(A_BOLD);
	refresh();

	int mstArrLen = 50;
	int array[mstArrLen];
	for(int i = 0; i < mstArrLen; i = i + 1)
	{
		array[i] = randomNum(-100, 100);
	}
	printw("Original Array:\n");
	printIntArrayCurses(array, mstArrLen);
	refresh();

	MaxSA msdata;
	//struct timespec start, stop; 	// start.tv_nsec
	struct timeval start, stop;		// start.tv_usec
	//clock_gettime(CLOCK_MONOTONIC, &start);
	gettimeofday(&start, NULL);
	msdata = findMaxSubarray(array, 0, mstArrLen - 1);
	//clock_gettime(CLOCK_MONOTONIC, &stop);
	gettimeofday(&stop, NULL);

	printw("\n\nMax Subarray:\n");
	for(int i = msdata.lowIndex; i <= msdata.highIndex; i++)
	{
		printw("%d ", array[i]);
	}
	printw("\n\nMax Subarray Sum: %d\n", msdata.maxSum);

	//printf("\nTime elapsed: %ld ns\n", stop.tv_nsec - start.tv_nsec);
	int usecPassed = timeDiff(start, stop);
	printw("Time elapsed: %d us\n\n", usecPassed);
	refresh();

	waitForEnter();
}

void unionFindTest()
{
	const int numDigits = 4;
	printf("\nUNION FIND TEST\n");
	printf("How many elements?\n");
	int numElements = getIntInput(numDigits);
	printf("Creating Union Find with %d elements.\n", numElements);
	WQuickUnion* newWQU = initWQuickUnionOfSize(numElements);

	const int MENU_MIN = 0;
	const int MENU_MAX = 4;
	int choice;

	do
	{
		printf("\n1. Find root of node\n");
		printf("2. Check whether nodes connected\n");
		printf("3. Connect nodes\n");
		printf("0. Return to main menu\n");

		choice = getIntInput(2);

		if(choice < MENU_MIN || choice > MENU_MAX)
		{
			printf("\nInvalid input.  Please try again.\n\n");
		}
		else if(choice == 1)
		{
			printf("\nEnter node number:\n");
			int nodeNum = getIntInput(numDigits);
			if(nodeNum < 0 || nodeNum > newWQU->count - 1)
			{
				printf("Invalid input.\n");
			}
			else
			{
				int nodeRoot = findRootOfNode(newWQU, nodeNum);
				printf("Root of Node %d is %d.\n", nodeNum, nodeRoot);
			}
		}
		else if(choice != 0)
		{
			printf("\nEnter number of Node 1:\n");
			int nodeNum1 = getIntInput(numDigits);
			printf("\nEnter number of Node 2:\n");
			int nodeNum2 = getIntInput(numDigits);

			if(nodeNum1 < 0 || nodeNum2 < 0 || nodeNum1 > (newWQU->count - 1) || nodeNum2 > (newWQU->count - 1))
			{
				printf("Invalid input.\n");
			}
			else if(choice == 2)
			{
				bool isConnected = pairIsConnected(newWQU, nodeNum1, nodeNum2);
				printf("Nodes %d and %d are ", nodeNum1, nodeNum2);
				if(isConnected == true)
				{
					printf("connected.\n");
				}
				else
				{
					printf("not connected.\n");
				}
			}
			else
			{
				unionNodes(newWQU, nodeNum1, nodeNum2);
			}
		}
	}
	while(choice != 0);

	deleteWQuickUnion(newWQU);
}
