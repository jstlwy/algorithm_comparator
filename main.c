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
//#include "pqueue.h"

#define ARRAY_LENGTH 100000

void arraySortTest(void);
void linkedListSortTest(void);
int getNumArrayElements(void);
bool getYesOrNo(void);
void maxSubarrayTest(void);
void unionFindTest(void);
void newSortTest(void);

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
		"New Sort Test",
		"Quit"
	};
	int numMenuOptions = 6;

	int keyInput = 0;
	int highlightedOption = 0;
	bool userSelectedQuit = false;
	while(userSelectedQuit == false)
	{
		erase();
		attron(A_BOLD);
		printw("DATA STRUCTURES AND ALGORITHMS TEST SUITE\n\n");
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
					break;
				case 4:
					newSortTest();
					break;
				case 5:
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

void arraySortTest(void)
{
	erase();
	attron(A_BOLD);
	printw("Array Sorting Algorithms\n\n");
	attroff(A_BOLD);	
	printw("Select number of elements to sort:\n");
	refresh();
	
	int arrayLength = getNumArrayElements();
	printw("\nArray will contain %d elements.\n\n", arrayLength);
	int array[arrayLength];
	for(int i = 0; i < arrayLength; i = i + 1)
	{
		array[i] = randomNum(-1000, 1000);
	}

	char* sortHeaders[] = {
		"Selection Sort",
		"Insertion Sort",
		"Shell Sort",
		"Merge Sort",
		"Quick Sort"
	};
	int numSortTypes = 5;
	//struct timespec start, stop; 	// start.tv_nsec
	struct timeval start, stop;		// start.tv_usec

	printw("Skip quadratic algorithms?\n");
	bool userDecidedToSkip = getYesOrNo();
	printw("\n\n");
	int skipPoint;
	if(userDecidedToSkip == true)
	{
		skipPoint = 2;
	}
	else
	{
		skipPoint = 0;
	}

	for(int i = skipPoint; i < numSortTypes; i = i + 1)
	{
		printw("%s: ", sortHeaders[i]);
		refresh();
		int* newArray = copyIntArray(array, arrayLength);
		//printf("\nUnsorted Array:\n");
		//printIntArray(newArray, arrayLength);

		switch(i)
		{
			case 0: // SELECTION SORT
				//clock_gettime(CLOCK_MONOTONIC, &start);
				gettimeofday(&start, NULL);
				selectionSort(newArray, arrayLength);
				//clock_gettime(CLOCK_MONOTONIC, &stop);
				gettimeofday(&stop, NULL);
				break;
			case 1: // INSERTION SORT
				//clock_gettime(CLOCK_MONOTONIC, &start);
				gettimeofday(&start, NULL);
				insertionSort(newArray, arrayLength);
				//clock_gettime(CLOCK_MONOTONIC, &stop);
				gettimeofday(&stop, NULL);
				break;
			case 2: // SHELL SORT
				//clock_gettime(CLOCK_MONOTONIC, &start);
				gettimeofday(&start, NULL);
				shellSort(newArray, arrayLength);
				//clock_gettime(CLOCK_MONOTONIC, &stop);
				gettimeofday(&stop, NULL);
				break;
			case 3: // MERGE SORT
				//clock_gettime(CLOCK_MONOTONIC, &start);
				gettimeofday(&start, NULL);
				mergeSortIntArr(newArray, arrayLength);
				//clock_gettime(CLOCK_MONOTONIC, &stop);
				gettimeofday(&stop, NULL);
				break;
			case 4: // QUICK SORT
				//clock_gettime(CLOCK_MONOTONIC, &start);
				gettimeofday(&start, NULL);
				quickSort(newArray, 0, arrayLength - 1);
				//clock_gettime(CLOCK_MONOTONIC, &stop);
				gettimeofday(&stop, NULL);
				break;
			default:
				break;
		}

		//printf("\nSorted Array:\n");
		//printIntArray(newArray, arrayLength);
		//printf("\nTime elapsed: %ld ns\n\n", stop.tv_nsec - start.tv_nsec);
		int usecPassed = timeDiff(start, stop);
		printw("%d us\n", usecPassed);
		refresh();
		free(newArray);
	}

	printw("\n");
	waitForEnter();
}

void linkedListSortTest(void)
{
	erase();
	attron(A_BOLD);
	printw("Linked List Sorting Algorithms\n\n");
	attroff(A_BOLD);
	printw("Select number of elements to sort:\n");
	refresh();

	int listLength = getNumArrayElements();
	printw("\nList will contain %d elements.\n\n", listLength);
	List* intList = initList();
	for(int i = 0; i < listLength; i = i + 1)
	{
		int newInt = randomNum(-1000, 1000);
		Node* newNode = malloc(sizeof(Node));
        newNode->data = newInt;
		insertAtTail(intList, newNode);
	}

	char* sortHeaders[] = {
		"Selection Sort",
		"Selection Sort (Sedgewick)",
		"Insertion Sort",
		"Insertion Sort (Sedgewick)",
		"Merge Sort (Sedgewick)"
	};
	int numSortTypes = 5;
	//struct timespec start, stop; 	// start.tv_nsec
	struct timeval start, stop;		// start.tv_usec

	printw("Skip quadratic algorithms?\n");
	bool userDecidedToSkip = getYesOrNo();
	printw("\n\n");
	int startPoint;
	if(userDecidedToSkip == true)
	{
		startPoint = 4;
	}
	else
	{
		startPoint = 0;
	}

	for(int i = startPoint; i < numSortTypes; i = i + 1)
	{
		List* newList = copyIntList(intList);
		printw("%s: ", sortHeaders[i]);
		//printf("\nUnsorted List:\n");
		//printIntList(newList);
		refresh();

		switch(i)
		{
			case 0: // SELECTION SORT
				//clock_gettime(CLOCK_MONOTONIC, &start);
				gettimeofday(&start, NULL);
				selectionSortIntLL(newList);
				//clock_gettime(CLOCK_MONOTONIC, &stop);
				gettimeofday(&stop, NULL);
				break;
			case 1: // SELECTION SORT (SEDGEWICK)
				//clock_gettime(CLOCK_MONOTONIC, &start);
				gettimeofday(&start, NULL);
				newList = selectionSortIntLLSedge(newList);
				//clock_gettime(CLOCK_MONOTONIC, &stop);
				gettimeofday(&stop, NULL);
				break;
			case 2: // INSERTION SORT
				//clock_gettime(CLOCK_MONOTONIC, &start);
				gettimeofday(&start, NULL);
				insertionSortIntLL(newList);
				//clock_gettime(CLOCK_MONOTONIC, &stop);
				gettimeofday(&stop, NULL);
				break;
			case 3: // INSERTION SORT (SEDGEWICK)
				//clock_gettime(CLOCK_MONOTONIC, &start);
				gettimeofday(&start, NULL);
				insertionSortIntLLSedge(newList);
				//clock_gettime(CLOCK_MONOTONIC, &stop);
				gettimeofday(&stop, NULL);
				break;
			case 4: // MERGE SORT (SEDGEWICK)
				//clock_gettime(CLOCK_MONOTONIC, &start);
				gettimeofday(&start, NULL);
				newList->first = mergeSortIntLL(newList->first);
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

int getNumArrayElements(void)
{
	int arrayLength = 0;
	
	char* arraySizeChoices[] = {
		"10",
		"100",
		"1000",
		"10000",
		"100000",
		"1000000"
	};
	int numArraySizeChoices = 6;
	
	int y;
	int x;
	getyx(stdscr, y, x);
	x = 0;
	int highlightedOption = 0;
	int keyInput;
	bool userPressedEnter = false;
	while(userPressedEnter == false)
	{
		move(y, x);
		clrtobot();

		for(int i = 0; i < numArraySizeChoices; i = i + 1)
		{
			if(i == highlightedOption)
			{
				attron(A_STANDOUT);
			}
			printw(arraySizeChoices[i]);
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
					arrayLength = 10;
					break;
				case 1:
					arrayLength = 100;
					break;
				case 2:
					arrayLength = 1000;
					break;
				case 3:
					arrayLength = 10000;
					break;
				case 4:
					arrayLength = 100000;
					break;
				case 5:
					arrayLength = 1000000;
					break;
				default:
					break;
			}
			userPressedEnter = true;
		}
		else if(keyInput == KEY_UP && highlightedOption > 0)
		{
			highlightedOption = highlightedOption - 1;
		}
		else if(keyInput == KEY_DOWN && highlightedOption < numArraySizeChoices - 1)
		{
			highlightedOption = highlightedOption + 1;
		}
	}
	
	return arrayLength;
}

bool getYesOrNo(void)
{
	bool userChoice;

	char* arraySizeChoices[] = {
		"Yes",
		"No"
	};
	int numArraySizeChoices = 2;
	
	int y;
	int x;
	getyx(stdscr, y, x);
	x = 0;
	int highlightedOption = 0;
	int keyInput;
	bool userPressedEnter = false;
	while(userPressedEnter == false)
	{
		move(y, x);
		clrtobot();

		for(int i = 0; i < numArraySizeChoices; i = i + 1)
		{
			if(i == highlightedOption)
			{
				attron(A_STANDOUT);
			}
			printw(arraySizeChoices[i]);
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
					userChoice = true;
					break;
				case 1:
					userChoice = false;
					break;
				default:
					break;
			}
			userPressedEnter = true;
		}
		else if(keyInput == KEY_UP && highlightedOption > 0)
		{
			highlightedOption = highlightedOption - 1;
		}
		else if(keyInput == KEY_DOWN && highlightedOption < numArraySizeChoices - 1)
		{
			highlightedOption = highlightedOption + 1;
		}
	}
	
	return userChoice;
}

void maxSubarrayTest(void)
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

void unionFindTest(void)
{
	erase();
	
	char* menuOptions[] = {
		"Find the root of a node",
		"Check whether two nodes are connected",
		"Connect two nodes",
		"Return to the main menu"
	};
	int numMenuOptions = 4;	

	attron(A_BOLD);
	printw("UNION FIND TEST\n\n");
	attroff(A_BOLD);
	printw("How many elements?\n");
	printw("Input: ");
	refresh();

	// Do something to get input
	int numElements = 100;

	printw("\n%d-element weighted quick UF\n\n", numElements);
	refresh();
	WQuickUnion* newWQU = initWQuickUnionOfSize(numElements);

	int y;
	int x;
	getyx(stdscr, y, x);
	x = 0;
	int highlightedOption = 0;
	bool userSelectedReturn = false;
	while(userSelectedReturn == false)
	{
		move(y, x);
		clrtobot();
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

		int keyInput = getch();
		if(keyInput == KEY_ENTER || keyInput == 10)
		{
			switch(highlightedOption)
			{
				case 0:
				{
					printf("\nEnter node number:\n");
					int nodeNum = getIntInput(3);
					if(nodeNum < 0 || nodeNum > newWQU->count - 1)
					{
						printf("Invalid input.\n");
					}
					else
					{
						int nodeRoot = findRootOfNode(newWQU, nodeNum);
						printf("Root of Node %d is %d.\n", nodeNum, nodeRoot);
					}
					break;
				}
				case 1:
				{
					printf("\nEnter number of Node 1:\n");
					int nodeNum1 = getIntInput(3);
					printf("\nEnter number of Node 2:\n");
					int nodeNum2 = getIntInput(3);

					if(nodeNum1 < 0 || nodeNum2 < 0 || nodeNum1 > (newWQU->count - 1) || nodeNum2 > (newWQU->count - 1))
					{
						printf("Invalid input.\n");
					}
					else
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
					break;
				}
				case 2:
				{
					printf("\nEnter number of Node 1:\n");
					int nodeNum1 = getIntInput(3);
					printf("\nEnter number of Node 2:\n");
					int nodeNum2 = getIntInput(3);
					if(nodeNum1 < 0 || nodeNum2 < 0 || nodeNum1 > (newWQU->count - 1) || nodeNum2 > (newWQU->count - 1))
					{
						printf("Invalid input.\n");
					}
					else
					{
						unionNodes(newWQU, nodeNum1, nodeNum2);
					}
					break;
				}
				case 3:
					userSelectedReturn = true;
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

	deleteWQuickUnion(newWQU);
}

void newSortTest(void)
{
	erase();
	attron(A_BOLD);
	printw("List Selection Sort (Sedgewick) Test\n\n");
	attroff(A_BOLD);	
	printw("Select number of elements to sort:\n");
	refresh();
	
	/*
	int arrayLength = getNumArrayElements();
	printw("\nArray will contain %d elements.\n\n", arrayLength);
	int array[arrayLength];
	for(int i = 0; i < arrayLength; i = i + 1)
	{
		array[i] = randomNum(-1000, 1000);
	}
	printIntArrayCurses(array, arrayLength);
	*/

	int listLength = getNumArrayElements();
	printw("\nList will contain %d elements.\n\n", listLength);
	List* intList = initList();
	for(int i = 0; i < listLength; i = i + 1)
	{
		int newInt = randomNum(-1000, 1000);
		Node* newNode = malloc(sizeof(Node));
        newNode->data = newInt;
		insertAtTail(intList, newNode);
	}
	printIntListCurses(intList);

	printw("\n\n");
	refresh();

	struct timeval start, stop;		// start.tv_usec
	gettimeofday(&start, NULL);
	// PUT SORT METHOD HERE
	intList = selectionSortIntLLSedge(intList);
	gettimeofday(&stop, NULL);
	int usecPassed = timeDiff(start, stop);
	printw("Time elapsed: %d us\n\n", usecPassed);
	refresh();

	//printIntArrayCurses(array, arrayLength);
	printIntListCurses(intList);
	printw("\n\n");
	refresh();

	waitForEnter();
}
