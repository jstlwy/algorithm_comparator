#ifndef ARRAYSORT_H
#define ARRAYSORT_H

// QUADRATIC SORTING ALGORITHMS
void selection_sort(int *array, const int array_size); // Unstable (stable for LL)
void insertion_sort(int *array, const int array_size); // Stable
void shellsort(int *array, const int array_size);      // Unstable


// LINEARITHMIC SORTING ALGORITHMS
void merge_sort_array(int *array, const int array_size);           // Stable
void merge_sort_td(int *arr, int *aux, int low, int high);
void merge_sort_bu(int *arr, int *aux, const int array_size);
void merge(int *arr, int *temp_arr, int first, int mid, int last);

void quicksort(int *array, int low, int high);
int partition(int *array, int low, int high);

void swim_up(int *arr, int k);
void sink_down(int *arr, int k, int size);
void heapsort_array(int *arr, int l, int r);


#endif
