#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <limits.h>
#include <pthread.h>
#include "input.h"
#include "utils.h"
#include "arrayutils.h"
#include "arraysort.h"
#include "dllist.h"
#include "listsort.h"
#include "maxsubarray.h"
#include "wqunion.h"

const unsigned long SI_h = 100;
const unsigned long SI_k = 1000;
const unsigned long SI_M = 1000000;
const unsigned long SI_G = 1000000000;
const unsigned long SI_hk = SI_h * SI_k;
const unsigned long SI_hM = SI_h * SI_M;
const unsigned long SI_hG = SI_h * SI_G;

// This way of measuring time deprecated in POSIX.1-2008:
/*
struct timeval start, stop;
gettimeofday(&start, NULL);
foo();
gettimeofday(&stop, NULL);
*/

struct array_sort_test_runner_vars {
	unsigned int sort_algo_num;
	int* original_array;
	int array_length;
	unsigned long time_elapsed_ns;
	bool was_successful;
};
void array_sort_test(void);
void *array_sort_test_runner(void* arg);

struct list_sort_test_runner_vars {
	unsigned int sort_algo_num;
	struct dllist* original_list;
	unsigned long time_elapsed_ns;
	bool was_successful;
};
void linked_list_sort_test(void);
void* list_sort_test_runner(void* arg);

void max_subarray_test(void);
void union_find_test(void);
void exercise_wqunion(struct wqunion* const wqu, const int option);

size_t get_num_elements(void);
bool get_yes_or_no(void);
void print_time_elapsed(unsigned long const time_elapsed);


int main()
{
	initscr();
	keypad(stdscr, true);
	noecho();
	curs_set(0);
	srand(time(0));

	size_t const num_options = 5;
	char const* const menu_options[] = {
		"Array Sorting Algorithms",
		"Linked List Sorting Algorithms",
		"Maximum Subarray",
		"Union Find",
		"Quit"
	};

	int key_input = 0;
	size_t highlighted_option = 0;
	bool exit_program = false;
	while (!exit_program)
	{
		erase();
		attron(A_BOLD);
		printw("DATA STRUCTURES AND ALGORITHMS TEST SUITE\n\n");
		attroff(A_BOLD);
		for (size_t i = 0; i < num_options; i++)
		{
			if (i == highlighted_option)
				attron(A_STANDOUT);
			printw("%zu. %s\n", i + 1, menu_options[i]);
			if (i == highlighted_option)
				attroff(A_STANDOUT);
		}
		refresh();

		key_input = getch();
		if (key_input == KEY_ENTER || key_input == 10)
		{
			switch (highlighted_option) {
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
				exit_program = true;
				break;
			default:
				break;
			}
		}
		else if (key_input == KEY_UP && highlighted_option > 0)
		{
			highlighted_option--;
		}
		else if (key_input == KEY_DOWN && highlighted_option < num_options - 1)
		{
			highlighted_option++;
		}
		else if (key_input >= '1' && key_input <= '5')
		{
			highlighted_option = ((int) key_input) - 49;
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

	size_t const array_length = get_num_elements();
	printw("\nArray will contain %zu elements.\n\n", array_length);
	int* const array = malloc(array_length * sizeof(int));
	for (size_t i = 0; i < array_length; i++)
	{
		array[i] = get_random_num(-1000, 1000);
	}

	size_t const num_options = 6;
	char const* const sort_algorithms[] = {
		"Selection Sort",
		"Insertion Sort",
		"Shellsort",
		"Heapsort",
		"Merge Sort",
		"Quicksort"
	};
	
	printw("Skip quadratic algorithms?\n");
	bool const skip_quadratic = get_yes_or_no();
	printw("\n\n");
	size_t const start_point = skip_quadratic ? 2 : 0;
	printw("Please wait...");
	refresh();

	size_t const num_threads = num_options - start_point;
	pthread_t threads[num_threads];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	struct array_sort_test_runner_vars vars[num_threads];

	for (size_t i = 0; i < num_threads; i++)
	{
		vars[i].sort_algo_num = i + start_point;
		vars[i].original_array = array;
		vars[i].array_length = array_length;
		pthread_create(&threads[i], &attr, array_sort_test_runner, &vars[i]);
	}

	for (size_t i = 0; i < num_threads; i++)
	{
		pthread_join(threads[i], NULL);
	}
	
	clear();
	printw("When sorting %zu elements:\n\n", array_length);
	for (size_t i = 0; i < num_threads; i++)
	{
		printw("%-14s: ", sort_algorithms[i + start_point]);
		print_time_elapsed(vars[i].time_elapsed_ns);
		if (!vars[i].was_successful)
			printw(" (failed)");
		printw("\n");
	}
	refresh();

	printw("\n");
	wait_for_enter();
}


void *array_sort_test_runner(void* arg)
{	
	struct array_sort_test_runner_vars* vars = arg;

	int* new_array = copy_int_array(vars->array_length, vars->original_array);

	struct timespec start;
	struct timespec stop;
	clock_gettime(CLOCK_MONOTONIC, &start);
	switch (vars->sort_algo_num)
	{
	case 0:
		selection_sort(vars->array_length, new_array);
		break;
	case 1:
		insertion_sort(vars->array_length, new_array);
		break;
	case 2:
		shellsort(vars->array_length, new_array);
		break;
	case 3:
		heapsort_array(new_array, 0, vars->array_length - 1);
		break;
	case 4:
		merge_sort_array(vars->array_length, new_array);
		break;
	case 5:
		quicksort(new_array, 0, vars->array_length - 1);
		break;
	default:
		break;
	}
	clock_gettime(CLOCK_MONOTONIC, &stop);

	vars->time_elapsed_ns = get_time_diff(start, stop);
	vars->was_successful = array_is_sorted(vars->array_length, new_array);
	
	free(new_array);

	return 0;
}


void linked_list_sort_test(void)
{
	erase();
	attron(A_BOLD);
	printw("Linked List Sorting Algorithms\n\n");
	attroff(A_BOLD);
	refresh();

	size_t const list_length = get_num_elements();
	printw("\nList will contain %zu elements.\n\n", list_length);
	struct dllist* const int_list = init_list();
	for (size_t i = 0; i < list_length; i++)
	{
		struct dlnode* const new_node = malloc(sizeof(struct dlnode));
        new_node->data = get_random_num(-1000, 1000);
		insert_at_tail(int_list, new_node);
	}

	size_t const num_options = 5;
	char const* const sort_algorithms[] = {
		"Selection Sort",
		"Selection Sort (Sedgewick)",
		"Insertion Sort",
		"Insertion Sort (Sedgewick)",
		"Merge Sort (Sedgewick)"
	};

	printw("Skip quadratic algorithms?\n");
	bool const skip_quadratic = get_yes_or_no();
	printw("\n\nPlease wait...");
	refresh();

	if (skip_quadratic)
	{
		struct dllist* new_list = copy_int_list(int_list);
		struct timespec start;
		struct timespec stop;
		clock_gettime(CLOCK_MONOTONIC, &start);
		new_list->first = merge_sort_list(new_list->first);
		clock_gettime(CLOCK_MONOTONIC, &stop);

		// Time returned in ns
		long const time_elapsed = get_time_diff(start, stop);
		printw("Merge sort: ");
		print_time_elapsed(time_elapsed);
		if (!list_is_sorted(new_list))
			printw(" (failed)");
		printw("\n");
		refresh();
		delete_list(new_list);
	}
	else
	{
		pthread_t threads[num_options];
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		struct list_sort_test_runner_vars vars[num_options];

		for (size_t i = 0; i < num_options; i++)
		{
			vars[i].sort_algo_num = i;
			vars[i].original_list = int_list;
			pthread_create(&threads[i], &attr, list_sort_test_runner, &vars[i]);
		}

		for (size_t i = 0; i < num_options; i++)
		{
			pthread_join(threads[i], NULL);
		}
		
		clear();
		printw("When sorting %zu elements:\n\n", list_length);
		for (size_t i = 0; i < num_options; i++)
		{
			printw("%-26s: ", sort_algorithms[i]);
			print_time_elapsed(vars[i].time_elapsed_ns);
			if (!vars[i].was_successful)
				printw(" (failed)");
			printw("\n");
		}
		refresh();
	}

	delete_list(int_list);
	printw("\n");
	wait_for_enter();
}


void *list_sort_test_runner(void* arg)
{	
	struct list_sort_test_runner_vars* vars = arg;

	struct dllist* new_list = copy_int_list(vars->original_list);

	struct timespec start;
	struct timespec stop;
	clock_gettime(CLOCK_MONOTONIC, &start);
	switch (vars->sort_algo_num)
	{
	case 0:
		selection_sort_list(new_list);
		break;
	case 1:
		new_list = selection_sort_list_sw(new_list);
		break;
	case 2:
		insertion_sort_list(new_list);
		break;
	case 3:
		insertion_sort_list_sw(new_list);
		break;
	case 4:
		new_list->first = merge_sort_list(new_list->first);
		break;
	default:
		break;
	}
	clock_gettime(CLOCK_MONOTONIC, &stop);

	vars->time_elapsed_ns = get_time_diff(start, stop);
	vars->was_successful = list_is_sorted(new_list);
	
	delete_list(new_list);

	return 0;
}


void max_subarray_test(void)
{
	erase();
	attron(A_BOLD);
	printw("Max Subarray Test\n\n");
	attroff(A_BOLD);
	refresh();

	size_t const array_len = get_num_elements();
	int* const array = malloc(array_len * sizeof(int));
	for (size_t i = 0; i < array_len; i++)
	{
		array[i] = get_random_num(-100, 100);
	}
	printw("Original Array:\n");
	print_int_array_curses(array_len, array);
	refresh();

	struct max_subarray ms;
	struct timespec start;
	struct timespec stop;
	clock_gettime(CLOCK_MONOTONIC, &start);
	ms = find_max_subarray(array, 0, array_len - 1);
	clock_gettime(CLOCK_MONOTONIC, &stop);

	printw("\n\nMax Subarray:\n");
	for (size_t i = ms.low_index; i <= ms.high_index; i++)
	{
		printw("%d ", array[i]);
	}
	printw("\n\nMax Subarray Sum: %d\n", ms.max_sum);

	printw("Time elapsed: ");
	long const time_elapsed = get_time_diff(start, stop);
	print_time_elapsed(time_elapsed);
	printw("\n\n");
	refresh();
	wait_for_enter();
}


void union_find_test(void)
{
	erase();
	
	size_t const num_options = 4;	
	char const* const menu_options[] = {
		"Find the root of a node",
		"Check whether two nodes are connected",
		"Connect two nodes",
		"Return to the main menu"
	};

	attron(A_BOLD);
	printw("UNION FIND TEST\n\n");
	attroff(A_BOLD);
	refresh();

	size_t const size = get_num_elements();
	printw("\n%zu-element weighted quick UF\n\n", size);
	refresh();
	struct wqunion* const wqu = init_wqunion_of_size(size);

	int y;
	int x;
	getyx(stdscr, y, x);
	x = 0;
	size_t highlighted_option = 0;
	bool should_return_to_main = false;
	while (!should_return_to_main)
	{
		move(y, x);
		clrtobot();
		for (size_t i = 0; i < num_options; i++)
		{
			if (i == highlighted_option)
				attron(A_STANDOUT);
			printw("%zu. %s\n", i + 1, menu_options[i]);
			if (i == highlighted_option)
				attroff(A_STANDOUT);
		}
		refresh();

		int key_input = getch();
		switch (key_input)
		{
		case KEY_ENTER:
		case 10:
			if (highlighted_option == num_options - 1)
				should_return_to_main = true;
			else
				exercise_wqunion(wqu, highlighted_option);
			break;
		case KEY_UP:
			if (highlighted_option > 0)
				highlighted_option--;
			break;
		case KEY_DOWN:
			if (highlighted_option < num_options - 1)
				highlighted_option++;
			break;
		case '1':
		case '2':
		case '3':
		case '4':
			highlighted_option = ((int) key_input) - 49;
			break;
		default:
			break;
		}
	}

	delete_wqunion(wqu);
}


void exercise_wqunion(struct wqunion* const wqu, int const option)
{
	switch (option)
	{
	case 0: // Find root of a node
		printw("\nEnter node number: ");
		refresh();
		size_t const node = get_size_t();
		if (node > wqu->count - 1)
		{
			printw("\nInvalid input.\n\n");
		}
		else
		{
			int const root = get_node_root(wqu, node);
			printw("\nRoot of %d: %d\n\n", node, root);
		}
		wait_for_enter();
		break;
	case 1: // Check if two nodes are connected
	case 2: // Connect two nodes
		printw("\nEnter number of first node:  ");
		size_t const node1 = get_size_t();
		printw("Enter number of second node: ");
		size_t const node2 = get_size_t();
		// Validate input
		size_t const last_node = wqu->count - 1;
		if (node1 > last_node || node2 > last_node)
		{
			printw("\nInvalid input.\n\n");
		}
		else if (option == 1)
		{
			printw("\nNodes %d and %d: ", node1, node2);
			bool const connected = pair_is_connected(wqu, node1, node2);
			printw("%s\n\n", connected ? "connected" : "not connected");
		}
		else
		{
			unify_nodes(wqu, node1, node2);
			printw("\nConnected nodes %d and %d.\n\n", node1, node2);
		}
		wait_for_enter();
		break;
	default:
		break;
	}
}


size_t get_num_elements(void)
{
	// Remember the coordinates so the cursor can be moved
	// back repeatedly in case of invalid user input
	int y;
	int x;
	getyx(stdscr, y, x);
	x = 0;
	
	size_t array_length = 0;
	while (array_length <= 0)
	{
		move(y,x);
		clrtobot();
		printw("Enter desired number of elements: ");
		refresh();
		array_length = get_size_t();
	}

	return array_length;
}


bool get_yes_or_no(void)
{
	int y;
	int x;
	getyx(stdscr, y, x);
	x = 0;
	size_t highlighted_option = 0;
	bool user_pressed_enter = false;
	bool did_choose_yes;
	while (!user_pressed_enter)
	{
		move(y, x);
		clrtobot();

		if (highlighted_option == 0)
			attron(A_STANDOUT);
		printw("Yes\n");
		if (highlighted_option == 0)
			attroff(A_STANDOUT);

		if (highlighted_option == 1)
			attron(A_STANDOUT);
		printw("No\n");
		if (highlighted_option == 1)
			attroff(A_STANDOUT);

		refresh();

		int const key_input = getch();
		switch (key_input)
		{
		case KEY_ENTER:
		case 10:
			user_pressed_enter = true;
			did_choose_yes = highlighted_option == 0;
			break;
		case KEY_UP:
			if (highlighted_option > 0)
				highlighted_option--;
			break;
		case KEY_DOWN:
			if (highlighted_option < 1)
				highlighted_option++;
			break;
		case 'Y':
		case 'y':
			highlighted_option = 0;
			break;
		case 'N':
		case 'n':
			highlighted_option = 1;
			break;
		default:
			break;
		}
	}
	
	return did_choose_yes;
}


void print_time_elapsed(unsigned long const time_elapsed)
{
	if (time_elapsed < SI_hk)
	{
		printw("%10lu ns", time_elapsed);
	}
	else if (time_elapsed < SI_hM)
	{
		printw("%10lu us", time_elapsed / SI_k);
	}
	else if (time_elapsed < SI_hG)
	{
		printw("%10lu ms", time_elapsed / SI_M);
	}
	else
	{
		printw("%10lu  s", time_elapsed / SI_G);
	}
}

