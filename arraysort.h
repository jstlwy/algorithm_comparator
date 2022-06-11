#ifndef ARRAYSORT_H
#define ARRAYSORT_H
#include <stdbool.h>

bool array_is_sorted(int *array, const int array_size);

// QUADRATIC SORTING ALGORITHMS
void selection_sort(int *array, const int array_size); // Unstable (stable for LL)
void insertion_sort(int *array, const int array_size); // Stable
void shellsort(int *array, const int array_size);      // Unstable


// LINEARITHMIC SORTING ALGORITHMS
void merge_sort_array(int *array, const int array_size);      // Stable
void merge_sort_td(int *arr, int *aux, int low, int high);
void merge_sort_bu(int *arr, int *aux, const int array_size);
void merge(int *arr, int *aux, int low, int mid, int high);

void quicksort(int *array, int low, int high);
int partition(int *array, int low, int high);

void swim_up(int *arr, int k);
void sink_down(int *arr, int k, int size);
void heapsort_array(int *arr, int l, int r);


// MAX SUBARRAY
struct max_subarray {
    int low_index;
    int high_index;
    int max_sum;
};

struct max_subarray find_max_crossing_subarray(int *array, int low, int mid, int high);
struct max_subarray find_max_subarray(int *array, int low, int high);

#endif
