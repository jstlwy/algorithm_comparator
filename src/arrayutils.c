#include "arrayutils.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

bool array_is_sorted(size_t const n, int array[n])
{
	for (size_t i = 1; i < n; i++)
	{
		if (array[i] < array[i-1])
			return false;
	}

	return true;
}


// Returns index of sought-after number
size_t binary_search(int* const array, size_t first, size_t last, int const target)
{
	// Return -1 if the index isn't found
	size_t soln_index = -1;

	while (first <= last)
	{
		size_t middle = (first + last) / 2;
		if (array[middle] == target)
		{
			soln_index = middle;
			break;
		}
		else if (target < array[middle])
		{
			last = middle - 1;
		}
		else
		{
			first = middle + 1;
		}
	}

	return soln_index;
}


void print_int_array(size_t const n, int array[n])
{
	for (size_t i = 0; i < n; i++)
	{
		printf("%d ", array[i]);
	}
}


void print_int_array_curses(size_t const n, int array[n])
{
	for (size_t i = 0; i < n; i++)
	{
		printw("%d ", array[i]);
	}
}


int* copy_int_array(size_t const n, int array[n])
{
	int* const new_array = malloc(n * sizeof(int));
	for (size_t i = 0; i < n; i++)
	{
		new_array[i] = array[i];
	}
	return new_array;
}

