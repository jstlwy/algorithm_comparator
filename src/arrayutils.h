#ifndef ARRAYUTILS_H
#define ARRAYUTILS_H
#include <stddef.h>
#include <stdbool.h>

bool array_is_sorted(size_t const n, int array[n]);
size_t binary_search(int* const array, size_t first, size_t last, int const target);
void print_int_array(size_t const n, int array[n]);
void print_int_array_curses(size_t const n, int array[n]);
int* copy_int_array(size_t const n, int array[n]);

#endif
