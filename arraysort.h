#ifndef ARRAYSORT_H
#define ARRAYSORT_H

/**
 * O(n^2) SORTING ALGORITHMS
 */

void selection_sort(int* array, const int array_size); // Unstable (stable for LL)
void insertion_sort(int* array, const int array_size); // Stable
void shell_sort(int* array, const int array_size);     // Unstable


/**
 * LINEARITHMIC SORTING ALGORITHMS
 */

void merge_sort_int_array(int* array, const int array_size);  // Stable
void merge_sort_td(int* arr, int* aux, int low, int high);
void merge_sort_bu(int* arr, int* aux, const int array_size);
void merge(int* arr, int* aux, int low, int mid, int high);

void quicksort(int* array, int low, int high);
int partition(int* array, int low, int high);
//int partition2(int* array, int low, int high);

void swim_up_array(int* arr, int k);
void sink_down_array(int* arr, int k, int size);
void heapsort_array(int* arr, int l, int r);


/**
 * MAX SUBARRAY
 */

typedef struct MaxSA {
    int lowIndex;
    int highIndex;
    int maxSum;
} MaxSA;

MaxSA find_max_crossing_subarray(int* A, int low, int mid, int high);
MaxSA find_max_subarray(int* A, int low, int high);

#endif
