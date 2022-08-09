#ifndef ARRAYSORT_H
#define ARRAYSORT_H

// QUADRATIC SORTING ALGORITHMS
void selection_sort(int * const array, const int array_size); // Unstable (stable for LL)
void insertion_sort(int * const array, const int array_size); // Stable
void shellsort(int * const array, const int array_size);      // Unstable


// LINEARITHMIC SORTING ALGORITHMS
// Merge sort is stable
void merge_sort_array(int * const array, const int array_size); 
void merge_sort_td(int * const arr, int * const aux, const int low, const int high);
void merge_sort_bu(int * const arr, int * const aux, const int array_size);
void merge(int * const arr, int * const temp_arr, const int first, const int mid, const int last);

void quicksort(int * const array, const int low, const int high);
int partition(int * const array, const int low, const int high);

void swim_up(int * const arr, int k);
void sink_down(int * const arr, int k, const int size);
void heapsort_array(int * const arr, const int l, const int r);


#endif
