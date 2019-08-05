#ifndef ARRAYSORT_H
#define ARRAYSORT_H

/**
 * O(n^2) SORTING ALGORITHMS
 */

void selectionSort(int* array, int arraySize);                  // Unstable (stable for LL)
void insertionSort(int* array, int arraySize);                  // Stable
void shellSort(int* array, int arraySize);                      // Unstable

/**
 * LINEARITHMIC SORTING ALGORITHMS
 */

void mergeSortIntArr(int* array, int arraySize);                // Stable
void mergeSortTD(int* arr, int* aux, int low, int high);
void mergeSortBU(int* arr, int* aux, int arraySize);
void merge(int* arr, int* aux, int low, int mid, int high);

void quickSort(int* array, int low, int high);
int partition(int* array, int low, int high);
//int partition2(int* array, int low, int high);

void swimUpArray(int* arr, int k);
void sinkDownArray(int* arr, int k, int size);
void heapsortArray(int* arr, int l, int r);

/**
 * MAX SUBARRAY
 */

typedef struct MaxSA {
    int lowIndex;
    int highIndex;
    int maxSum;
} MaxSA;

MaxSA findMaxCrossingSubarray(int* A, int low, int mid, int high);
MaxSA findMaxSubarray(int* A, int low, int high);

#endif
