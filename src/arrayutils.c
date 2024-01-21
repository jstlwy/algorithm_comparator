#include "arrayutils.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

bool array_is_sorted(const size_t n, const int array[const static n])
{
    for (size_t i = 1; i < n; i++)
    {
        if (array[i] < array[i-1]) {
            return false;
        }
    }

    return true;
}


// Returns index of sought-after number
size_t binary_search(const int array[const], size_t first, size_t last, const int target)
{
    // Return -1 if the index isn't found
    size_t soln_index = -1;

    while (first <= last) {
        size_t middle = (first + last) / 2;
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


void print_int_array(const size_t n, const int array[const static n])
{
    if (n == 0) {
        puts("[]");
        return;
    }

    printf("[%d", array[0]);
    for (size_t i = 1; i < n; i++) {
        printf(", %d", array[i]);
    }
    puts("]");
}


void print_int_array_curses(const size_t n, const int array[const static n])
{
    for (size_t i = 0; i < n; i++) {
        printw("%d ", array[i]);
    }
}


int* copy_int_array(const size_t n, const int array[const static n])
{
    int* const new_array = malloc(n * sizeof(int));
    if (new_array == NULL) {
        fprintf(stderr, "%s: ERROR: malloc failed.\n", __func__);
        exit(1);
    }
    memcpy(new_array, array, n * sizeof(int));
    return new_array;
}

