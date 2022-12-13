#ifndef ARRAYSORT_H
#define ARRAYSORT_H
#include <stddef.h>

// QUADRATIC SORTING ALGORITHMS
void selection_sort(size_t const n, int array[n]); // Unstable (stable for LL)
void insertion_sort(size_t const n, int array[n]); // Stable
void shellsort(size_t const n, int array[n]);      // Unstable


// LINEARITHMIC SORTING ALGORITHMS
// Merge sort is stable
void merge_sort_array(size_t const n, int array[n]);
void merge_sort_td(int* const arr, int* const aux, size_t const low, size_t const high);
void merge_sort_bu(size_t const n, int arr[n], int helper_arr[n]);
void merge(int* const arr, int* const temp_arr, size_t const first, size_t const mid, size_t const last);

void quicksort(int* const array, size_t const low, size_t const high);
size_t partition(int* const array, size_t const low, size_t const high);

void swim_up(int* const arr, size_t k);
void sink_down(int* const arr, size_t k, size_t const size);
void heapsort_array(int* const arr, size_t const l, size_t const r);


#endif
