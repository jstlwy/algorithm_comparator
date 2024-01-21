#ifndef ARRAYSORT_H
#define ARRAYSORT_H
#include <stddef.h>

// QUADRATIC SORTING ALGORITHMS
void selection_sort(const size_t n, int array[const static n]); // Unstable (stable for LL)
void insertion_sort(const size_t n, int array[const static n]); // Stable
void shellsort(const size_t n, int array[const static n]);      // Unstable

// LINEARITHMIC SORTING ALGORITHMS
// Merge sort is stable
void merge_sort_array(const size_t n, int array[const static n]);
void merge_sort_td(int arr[const], int aux[const], const size_t low, const size_t high);
void merge_sort_bu(const size_t n, int arr[const static n], int helper_arr[const static n]);
void merge(int arr[const], int temp_arr[const], const size_t first, const size_t mid, const size_t last);

void quicksort(int array[const], const size_t low, const size_t high);
size_t partition(int array[const], const size_t low, const size_t high);

void swim_up(int arr[const], size_t k);
void sink_down(int arr[const], size_t k, const size_t size);
void heapsort_array(int arr[const], const size_t l, const size_t r);

#endif
