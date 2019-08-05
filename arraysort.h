#ifndef ARRAYSORT_H
#define ARRAYSORT_H

/**
 * NON-RECURSIVE SORTING ALGORITHMS
 */

void selectionSort(int* array, int arraySize);                  // Unstable (stable for LL)
void insertionSort(int* array, int arraySize);                  // Stable
void shellSort(int* array, int arraySize);                      // Unstable

/**
 * RECURSIVE SORTING ALGORITHMS
 */

void mergeSortIntArr(int* array, int arraySize);                // Stable
void mergeSortTD(int* arr, int* aux, int low, int high);
void mergeSortBU(int* arr, int* aux, int arraySize);
void merge(int* arr, int* aux, int low, int mid, int high);

void quickSort(int* array, int low, int high);
int partition(int* array, int low, int high);
//int partition2(int* array, int low, int high);

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
