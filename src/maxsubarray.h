#ifndef MAXSUBARRAY_H
#define MAXSUBARRAY_H
#include <stddef.h>

struct max_subarray {
    size_t low_index;
    size_t high_index;
    int max_sum;
};

struct max_subarray find_max_crossing_subarray(
    int array[const],
    const size_t low,
    const size_t mid,
    const size_t high);

struct max_subarray find_max_subarray(int array[const], const size_t low, const size_t high);

#endif
