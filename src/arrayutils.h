#ifndef ARRAYUTILS_H
#define ARRAYUTILS_H
#include <stdbool.h>

bool array_is_sorted(int *array, const int array_size);
int binary_search(int array[], int first, int last, int target);
void print_int_array(int *array, const int array_size);
void print_int_array_curses(int *array, const int array_size);
int* copy_int_array(int *original_array, const int original_array_size);

#endif
