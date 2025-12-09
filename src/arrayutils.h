#ifndef ARRAYUTILS_H
#define ARRAYUTILS_H
#include <stddef.h>
#include <stdbool.h>
#include <sys/types.h>

bool array_is_sorted(const size_t n, const int array[const static n]);
ssize_t binary_search(const int array[const], ssize_t first, ssize_t last, int const target);
void print_int_array(const size_t n, const int array[const static n]);
void print_int_array_curses(const size_t n, const int array[const static n]);

#endif
