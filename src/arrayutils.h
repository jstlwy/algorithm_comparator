#ifndef ARRAYUTILS_H
#define ARRAYUTILS_H
#include <stddef.h>
#include <stdbool.h>

bool array_is_sorted(const size_t n, const int array[const static n]);
size_t binary_search(const int array[const], size_t first, size_t last, int const target);
void print_int_array(const size_t n, const int array[const static n]);
void print_int_array_curses(const size_t n, const int array[const static n]);
int* copy_int_array(const size_t n, const int array[const static n]);

#endif
