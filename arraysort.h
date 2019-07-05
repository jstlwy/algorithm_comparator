#ifndef ARRAYSORT_H
#define ARRAYSORT_H

typedef struct MaxSA {
    int lowIndex;
    int highIndex;
    int maxSum;
} MaxSA;

void insertionSort(int* array, int arraySize);

void mergeSort(int* array, int l, int r);
void merge(int* arr, int l, int m, int r);

MaxSA findMaxCrossingSubarray(int* A, int low, int mid, int high);
MaxSA findMaxSubarray(int* A, int low, int high);

#endif