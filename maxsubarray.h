#ifndef MAXSUBARRAY_H
#define MAXSUBARRAY_H

struct max_subarray {
    int low_index;
    int high_index;
    int max_sum;
};

struct max_subarray find_max_crossing_subarray(int *array, int low, int mid, int high);
struct max_subarray find_max_subarray(int *array, int low, int high);

#endif
