#include "arrayutils.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

bool array_is_sorted(int *array, const int array_size)
{
	if (array_size <= 1)
		return true;

	for (int i = 1; i < array_size; i++) {
		if (array[i] < array[i-1])
			return false;
	}

	return true;
}


// Returns index of sought-after number
int binary_search(int array[], int first, int last, int target)
{
	// Return -1 if the index isn't found
	int soln_index = -1;

	while (first <= last) {
		int middle = (first + last) / 2;
		if (array[middle] == target) {
			soln_index = middle;
			break;
		} else if (target < array[middle]) {
			last = middle - 1;
		} else {
			first = middle + 1;
		}
	}

	return soln_index;
}


void print_int_array(int *array, const int array_size)
{
	for (int i = 0; i < array_size; i++) {
		printf("%d ", array[i]);
	}
}


void print_int_array_curses(int *array, const int array_size)
{
	for (int i = 0; i < array_size; i++) {
		printw("%d ", array[i]);
	}
}


int* copy_int_array(int *original_array, const int original_array_size)
{
	int* new_array = malloc(original_array_size * sizeof(int));
	for (int i = 0; i < original_array_size; i++) {
		new_array[i] = original_array[i];
	}
	return new_array;
}

