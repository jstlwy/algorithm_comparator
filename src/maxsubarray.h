#ifndef MAXSUBARRAY_H
#define MAXSUBARRAY_H

struct max_subarray {
    int low_index;
    int high_index;
    int max_sum;
};

struct max_subarray find_max_crossing_subarray(int * const array,
	const int low, const int mid, const int high);
struct max_subarray find_max_subarray(int * const array,
	const int low, const int high);

#endif
