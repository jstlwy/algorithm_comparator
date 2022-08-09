#ifndef ARRAYUTILS_H
#define ARRAYUTILS_H
#include <stdbool.h>

bool array_is_sorted(int * const array, const int array_size);
int binary_search(int * const array, int first, int last, const int target);
void print_int_array(int * const array, const int array_size);
void print_int_array_curses(int * const array, const int array_size);
int* copy_int_array(int * const original_array, const int original_array_size);

#endif
