#include "arrayutils.h"
#include <stdio.h>
#include <ncurses.h>

bool array_is_sorted(const size_t n, const int array[const static n])
{
    for (size_t i = 1; i < n; i++) {
        if (array[i] < array[i-1]) {
            return false;
        }
    }
    return true;
}

// Returns index of target
ssize_t binary_search(const int array[const], ssize_t first, ssize_t last, const int target)
{
    while (first <= last) {
        const ssize_t middle = (first + last) / 2;
        if (array[middle] == target) {
            return middle;
        }
        if (target < array[middle]) {
            last = middle - 1;
        } else {
            first = middle + 1;
        }
    }
    return -1;
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
    if (n == 0) {
        addstr("[]\n");
        return;
    }

    printw("[%d", array[0]);
    for (size_t i = 1; i < n; i++) {
        printw(", %d", array[i]);
    }
    addstr("]\n");
}

