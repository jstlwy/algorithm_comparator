#ifndef MAXSUBARRAY_H
#define MAXSUBARRAY_H
#include <stddef.h>

struct max_subarray {
    size_t low_index;
    size_t high_index;
    int max_sum;
};

struct max_subarray find_max_crossing_subarray(int* const array,
	size_t const low, size_t const mid, size_t const high);
struct max_subarray find_max_subarray(int* const array,
	size_t const low, size_t const high);

#endif
