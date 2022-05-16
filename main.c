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

/* 
To count in nanoseconds:
struct timespec start, stop;
clock_gettime(CLOCK_MONOTONIC, &start);
do_something();
clock_gettime(CLOCK_MONOTONIC, &stop);
printf("\nTime elapsed: %ld ns\n\n", stop.tv_nsec - start.tv_nsec);

Note: 
struct timespec
instead of
struct timeval
*/

void array_sort_test(void);
void linked_list_sort_test(void);
int get_num_array_elements(void);
bool get_yes_or_no(void);
void max_subarray_test(void);
void union_find_test(void);
void new_sort_test(void);
void priority_queue_test(void);


int main(int argc, char *argv[])
{
	initscr();
	keypad(stdscr, true);
	noecho();
	curs_set(0);
	srand(time(0));

	const int num_menu_options = 7;
	const char* menu_options[num_menu_options] = {
		"Array Sorting Algorithms",
		"Linked List Sorting Algorithms",
		"Maximum Subarray",
		"Union Find",
		"New Sort Test",
		"Priority Queue Test",
		"Quit"
	};

	int key_input = 0;
	int highlighted_option = 0;
	bool user_selected_quit = false;
	while(user_selected_quit == false)
	{
		erase();
		attron(A_BOLD);
		printw("DATA STRUCTURES AND ALGORITHMS TEST SUITE\n\n");
		attroff(A_BOLD);
		for(int i = 0; i < num_menu_options; i++)
		{
			if(i == highlighted_option)
			{
				attron(A_STANDOUT);
			}
			printw("%d. ", i + 1);
			printw(menu_options[i]);
			printw("\n");
			if(i == highlighted_option)
			{
				attroff(A_STANDOUT);
			}
		}
		refresh();

		key_input = getch();
		if(key_input == KEY_ENTER || key_input == 10)
		{
			switch(highlighted_option)
			{
			case 0:
				array_sort_test();
				break;
			case 1:
				linked_list_sort_test();
				break;
			case 2:
				max_subarray_test();
				break;
			case 3:
				union_find_test();
				break;
			case 4:
				new_sort_test();
				break;
			case 5:
				priority_queue_test();
				break;
			case 6:
				user_selected_quit = true;
				break;
			default:
				break;
			}
		}
		else if(key_input == KEY_UP && highlighted_option > 0)
		{
			highlighted_option--;
		}
		else if(key_input == KEY_DOWN && highlighted_option < num_menu_options - 1)
		{
			highlighted_option++;
		}
	}

	endwin();
	return 0;
}


void array_sort_test(void)
{
	erase();
	attron(A_BOLD);
	printw("Array Sorting Algorithms\n\n");
	attroff(A_BOLD);	
	printw("Select number of elements to sort:\n");
	refresh();
	
	const int array_length = get_num_array_elements();
	printw("\nArray will contain %d elements.\n\n", array_length);
	int array[array_length];
	for(int i = 0; i < array_length; i++)
	{
		array[i] = get_random_num(-1000, 1000);
	}

	const int num_sort_algorithms = 6;
	char* sort_algorithm_titles[num_sort_algorithms] = {
		"Selection Sort",
		"Insertion Sort",
		"Shell Sort",
		"Heap Sort",
		"Merge Sort",
		"Quick Sort"
	};
	
	struct timeval start, stop;		// start.tv_usec

	printw("Skip quadratic algorithms?\n");
	bool should_skip_quadratic = get_yes_or_no();
	printw("\n\n");
	const int menu_start_point = should_skip_quadratic ? 2 : 0;

	for(int i = menu_start_point; i < num_sort_algorithms; i++)
	{
		printw("%s: ", sort_algorithm_titles[i]);
		refresh();
		int* new_array = copy_int_array(array, array_length);
		//printf("\nUnsorted Array:\n");
		//printIntArray(new_array, array_length);

		switch(i)
		{
		case 0: // SELECTION SORT
			gettimeofday(&start, NULL);
			selectionSort(new_array, array_length);
			gettimeofday(&stop, NULL);
			break;
		case 1: // INSERTION SORT
			gettimeofday(&start, NULL);
			insertionSort(new_array, array_length);
			gettimeofday(&stop, NULL);
			break;
		case 2: // SHELLSORT
			gettimeofday(&start, NULL);
			shellSort(new_array, array_length);
			gettimeofday(&stop, NULL);
			break;
		case 3: // HEAP SORT
			gettimeofday(&start, NULL);
			heapsortArray(new_array, 0, array_length - 1);
			gettimeofday(&stop, NULL);
			break;
		case 4: // MERGE SORT
			gettimeofday(&start, NULL);
			mergeSortIntArr(new_array, array_length);
			gettimeofday(&stop, NULL);
			break;
		case 5: // QUICKSORT
			gettimeofday(&start, NULL);
			quickSort(new_array, 0, array_length - 1);
			gettimeofday(&stop, NULL);
			break;
		default:
			break;
		}

		//printf("\nSorted Array:\n");
		//printIntArray(new_array, array_length);
		int usecPassed = timeDiff(start, stop);
		printw("%d us\n", usecPassed);
		refresh();
		free(new_array);
	}

	printw("\n");
	wait_for_enter();
}


void linked_list_sort_test(void)
{
	erase();
	attron(A_BOLD);
	printw("Linked List Sorting Algorithms\n\n");
	attroff(A_BOLD);
	printw("Select number of elements to sort:\n");
	refresh();

	const int list_length = get_num_array_elements();
	printw("\nList will contain %d elements.\n\n", list_length);
	doubly_linked_list* int_list = init_list();
	for(int i = 0; i < list_length; i++)
	{
		doubly_linked_node* new_node = malloc(sizeof(doubly_linked_node));
        new_node->data = get_random_num(-1000, 1000);
		insert_at_tail(int_list, new_node);
	}

	const int num_sort_algorithms = 5;
	const char* sort_algorithm_titles[num_sort_algorithms] = {
		"Selection Sort",
		"Selection Sort (Sedgewick)",
		"Insertion Sort",
		"Insertion Sort (Sedgewick)",
		"Merge Sort (Sedgewick)"
	};
	struct timeval start, stop;		// start.tv_usec

	printw("Skip quadratic algorithms?\n");
	const bool should_skip_quadratic = get_yes_or_no();
	printw("\n\n");
	const int start_point = should_skip_quadratic ? 4 : 0;

	for(int i = start_point; i < num_sort_algorithms; i++)
	{
		doubly_linked_list* new_list = copy_int_list(int_list);
		printw("%s: ", sort_algorithm_titles[i]);
		//printf("\nUnsorted List:\n");
		//printIntList(new_list);
		refresh();

		switch(i)
		{
		case 0: // SELECTION SORT
			gettimeofday(&start, NULL);
			selection_sort_list(new_list);
			gettimeofday(&stop, NULL);
			break;
		case 1: // SELECTION SORT (SEDGEWICK & WAYNE)
			gettimeofday(&start, NULL);
			new_list = selection_sort_list_sw(new_list);
			gettimeofday(&stop, NULL);
			break;
		case 2: // INSERTION SORT
			gettimeofday(&start, NULL);
			insertion_sort_list(new_list);
			gettimeofday(&stop, NULL);
			break;
		case 3: // INSERTION SORT (SEDGEWICK & WAYNE)
			gettimeofday(&start, NULL);
			insertion_sort_list_sw(new_list);
			gettimeofday(&stop, NULL);
			break;
		case 4: // MERGE SORT (SEDGEWICK & WAYNE)
			gettimeofday(&start, NULL);
			new_list->first = merge_sort_list(new_list->first);
			gettimeofday(&stop, NULL);
			break;
		default:
			break;
		}

		//printf("\nSorted List:\n");
		//print_int_list(new_list);
		const int time_elapsed_us = time_diff(start, stop);
		printw("%d us\n", time_elapsed_us);
		refresh();
		delete_list(new_list);
	}

	delete_list(int_list);
	printw("\n");
	wait_for_enter();
}


int get_num_array_elements(void)
{
	int array_length = 0;
	
	const int num_array_size_options = 6;
	const char* array_size_options[num_array_size_options] = {
		"10",
		"100",
		"1000",
		"10000",
		"100000",
		"1000000"
	};
	const int array_size_values[num_array_size_options] = {
		10,
		100,
		1000,
		10000,
		100000,
		1000000
	};
	
	int y;
	int x;
	getyx(stdscr, y, x);
	x = 0;
	int highlighted_option = 0;
	int key_input;
	bool user_pressed_enter = false;
	while(user_pressed_enter == false)
	{
		move(y, x);
		clrtobot();

		for(int i = 0; i < numArraySizeChoices; i++)
		{
			if(i == highlighted_option)
			{
				attron(A_STANDOUT);
			}
			printw(arraySizeChoices[i]);
			printw("\n");
			if(i == highlighted_option)
			{
				attroff(A_STANDOUT);
			}
		}
		refresh();

		key_input = getch();
		if(key_input == KEY_ENTER || key_input == 10)
		{
			array_length = array_size_values[highlighted_option];
			user_pressed_enter = true;
		}
		else if(key_input == KEY_UP && highlighted_option > 0)
		{
			highlighted_option--;
		}
		else if(key_input == KEY_DOWN && highlighted_option < numArraySizeChoices - 1)
		{
			highlighted_option++;
		}
	}
	
	return array_length;
}


bool get_yes_or_no(void)
{
	const num_menu_options = 2;
	const char* menu_options[num_menu_options] = {"Yes", "No"};
	
	int y;
	int x;
	getyx(stdscr, y, x);
	x = 0;
	int highlighted_option = 0;
	bool user_pressed_enter = false;
	bool user_choice;
	while(user_pressed_enter == false)
	{
		move(y, x);
		clrtobot();

		for(int i = 0; i < num_menu_options; i++)
		{
			if(i == highlighted_option)
			{
				attron(A_STANDOUT);
			}
			printw(menu_options[i]);
			printw("\n");
			if(i == highlighted_option)
			{
				attroff(A_STANDOUT);
			}
		}
		refresh();

		const int key_input = getch();
		if(key_input == KEY_ENTER || key_input == 10)
		{
			switch(highlighted_option)
			{
			case 0:
				user_choice = true;
				break;
			case 1:
				user_choice = false;
				break;
			default:
				break;
			}
			user_pressed_enter = true;
		}
		else if(key_input == KEY_UP && highlighted_option > 0)
		{
			highlighted_option--;
		}
		else if(key_input == KEY_DOWN && highlighted_option < numArraySizeChoices - 1)
		{
			highlighted_option++;
		}
	}
	
	return user_choice;
}


void max_subarray_test(void)
{
	erase();
	attron(A_BOLD);
	printw("Max Subarray Test\n\n");
	attroff(A_BOLD);
	refresh();

	int mstArrLen = 50;
	int array[mstArrLen];
	for(int i = 0; i < mstArrLen; i++)
	{
		array[i] = get_random_num(-100, 100);
	}
	printw("Original Array:\n");
	print_int_array_curses(array, mstArrLen);
	refresh();

	MaxSA msdata;
	struct timeval start, stop;		// start.tv_usec
	gettimeofday(&start, NULL);
	msdata = findMaxSubarray(array, 0, mstArrLen - 1);
	gettimeofday(&stop, NULL);

	printw("\n\nMax Subarray:\n");
	for(int i = msdata.lowIndex; i <= msdata.highIndex; i++)
	{
		printw("%d ", array[i]);
	}
	printw("\n\nMax Subarray Sum: %d\n", msdata.maxSum);

	int usecPassed = timeDiff(start, stop);
	printw("Time elapsed: %d us\n\n", usecPassed);
	refresh();

	wait_for_enter();
}


void union_find_test(void)
{
	erase();
	
	const int num_menu_options = 4;	
	const char* menu_options[num_menu_options] = {
		"Find the root of a node",
		"Check whether two nodes are connected",
		"Connect two nodes",
		"Return to the main menu"
	};

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
	int highlighted_option = 0;
	bool userSelectedReturn = false;
	while(userSelectedReturn == false)
	{
		move(y, x);
		clrtobot();
		for(int i = 0; i < num_menu_options; i++)
		{
			if(i == highlighted_option)
			{
				attron(A_STANDOUT);
			}
			printw("%d. ", i + 1);
			printw(menu_options[i]);
			printw("\n");
			if(i == highlighted_option)
			{
				attroff(A_STANDOUT);
			}
		}
		refresh();

		int key_input = getch();
		if(key_input == KEY_ENTER || key_input == 10)
		{
			switch(highlighted_option)
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
		else if(key_input == KEY_UP && highlighted_option > 0)
		{
			highlighted_option--;
		}
		else if(key_input == KEY_DOWN && highlighted_option < num_menu_options - 1)
		{
			highlighted_option++;
		}
	}

	deleteWQuickUnion(newWQU);
}


void new_sort_test(void)
{
	erase();
	attron(A_BOLD);
	printw("List Selection Sort (Sedgewick) Test\n\n");
	attroff(A_BOLD);	
	printw("Select number of elements to sort:\n");
	refresh();
	
	/*
	const int array_length = get_num_array_elements();
	printw("\nArray will contain %d elements.\n\n", array_length);
	int array[array_length];
	for(int i = 0; i < array_length; i++)
	{
		array[i] = get_random_num(-1000, 1000);
	}
	print_int_array_curses(array, array_length);
	*/

	int list_length = get_num_array_elements();
	printw("\nList will contain %d elements.\n\n", list_length);
	List* int_list = init_list();
	for(int i = 0; i < list_length; i++)
	{
		int newInt = get_random_num(-1000, 1000);
		Node* new_node = malloc(sizeof(Node));
        newNode->data = newInt;
		insertAtTail(int_list, new_node);
	}
	printIntListCurses(int_list);
	printw("\n\n");
	refresh();

	struct timeval start, stop;		// start.tv_usec
	gettimeofday(&start, NULL);
	// PUT SORT METHOD HERE
	insertionSortIntLLSedge(int_list);
	gettimeofday(&stop, NULL);
	int usecPassed = timeDiff(start, stop);
	printw("Time elapsed: %d us\n\n", usecPassed);

	//print_int_array_curses(array, array_length);
	printIntListCurses(int_list);
	printw("\n\n");
	wait_for_enter();
}


void priority_queue_test(void)
{
	erase();
	attron(A_BOLD);
	printw("Heapsort Test\n\n");
	attroff(A_BOLD);	
	printw("Select number of elements to sort:\n");
	refresh();
	
	int array_length = get_num_array_elements();
	printw("\nArray will contain %d elements.\n\n", array_length);
	int array[array_length];
	for(int i = 0; i < array_length; i++)
	{
		array[i] = get_random_num(-1000, 1000);
	}
	if(array_length < 1000)
	{
		printw("\nUnsorted Array:\n");
		print_int_array_curses(array, array_length);
	}
	printw("\n\n");
	refresh();

	struct timeval start, stop;		// start.tv_usec
	gettimeofday(&start, NULL);
	heapsortArray(array, 0, array_length-1);
	gettimeofday(&stop, NULL);
	int usecPassed = timeDiff(start, stop);
	printw("Time elapsed: %d us\n\n", usecPassed);

	if(array_length < 1000)
	{
		printw("\nSorted Array:\n");
		print_int_array_curses(array, array_length);
	}
	printw("\n\n");
	wait_for_enter();
}

