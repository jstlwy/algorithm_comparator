#ifndef SORT_H
#define SORT_H

struct MaxSA
{
    int lowIndex;
    int highIndex;
    int maxSum;
};

void insertionSort(int *array, int arraySize);

void mergeSort(int *array, int l, int r);
void merge(int *arr, int l, int m, int r);

struct MaxSA findMaxCrossingSubarray(int* A, int low, int mid, int high);
struct MaxSA findMaxSubarray(int* A, int low, int high);

#endif