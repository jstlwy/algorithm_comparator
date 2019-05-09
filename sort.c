#include "sort.h"

void insertionSort(int *array, int arraySize)
{
	int j;
	for(int i = 1; i < arraySize; i = i + 1)
	{
		int key = array[i];
		j = i - 1;
		while(j >= 0 && array[j] > key)
		{
			array[j + 1] = array[j];
			j = j - 1;
		}
		array[j + 1] = key;	
	}
}

void mergeSort(int *array, int l, int r)
{
	int median;
	if(l < r)
	{
		median = l + ((r - l) / 2);
		mergeSort(array, l, median);
		mergeSort(array, median + 1, r);
		merge(array, l, median, r);
	}
}

void merge(int *arr, int l, int m, int r)
{
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 

    // create temp arrays
    int L[n1], R[n2]; 

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i = i + 1) 
	{
        L[i] = arr[l + i]; 
	}
    for (j = 0; j < n2; j = j + 1) 
	{
        R[j] = arr[m + 1 + j]; 
	}

    // Merge the temp arrays back into arr[l..r]
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
		// Note: i or j only incremented
		// when their values are placed in k
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i = i + 1; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j = j + 1; 
        } 
        k = k + 1; 
    }

    // Copy any remaining elements of L[]
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i = i + 1; 
        k = k + 1; 
    } 
  
    // Copy any remaining elements of R[]
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j = j + 1; 
        k = k + 1; 
    } 
}