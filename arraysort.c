#include "arraysort.h"
#include <limits.h>

void selectionSort(int* array, int arraySize)
{
	int min;
	int minIndex;
	for(int i = 0; i < arraySize; i = i + 1)
	{
		min = i;
		for(int j = i + 1; j < arraySize; j = j + 1)
		{
			if(array[j] < min)
			{
				min = array[j];
				minIndex = j;
			}
		}
		array[minIndex] = array[i];
		array[i] = min;
	}
}

void insertionSort(int* array, int arraySize)
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

void shellSort(int* array, int arraySize)
{
    // h = "gap"
    int h = 1;
    // First, find largest number by which to divide array
    // OEIS A003462: 0.5(3^k - 1) results in worst-case Theta(N^1.5)
    while(h < arraySize / 3)
    {
        // 1, 4, 13, 40, 121, 364, 1093, ...
        h = (3 * h) + 1;
    }
    // Now, commence h-sorting the array
    while(h >= 1)
    {
        for(int i = h; i < arraySize; i = i + 1)
        {
            for(int j = i; j >= h && array[j] < array[j - h]; j = j - h)
            {
                int temp = array[j];
                array[j] = array[j - h];
                array[j - h] = temp;
            }
        }
        h = h/3;
    }
}

void mergeSortIntArr(int* array, int arraySize)
{
    int aux[arraySize];
    mergeSortTD(array, aux, 0, arraySize - 1);
    //mergeSortBU(array, aux, arraySize);
}

void mergeSortTD(int* arr, int* aux, int low, int high)
{
	if(low < high)
	{
		int mid = low + ((high - low) / 2);
		mergeSortTD(arr, aux, low, mid);
		mergeSortTD(arr, aux, mid + 1, high);
		merge(arr, aux, low, mid, high);
	}
}

void mergeSortBU(int* arr, int* aux, int arraySize)
{
    for(int size = 1; size < arraySize; size = size + size)
    {
        for(int low = 0; low < arraySize - size; low = low + size + size)
        {
            int min;
            int value1 = low + size + size - 1;
            int value2 = arraySize - 1;
            if(value1 < value2)
            {
                min = value1;
            }
            else
            {
                min = value2;
            }
            merge(arr, aux, low, low + size - 1, min);
        }
    }
}

void merge(int* arr, int* aux, int low, int mid, int high)
{
    int i = low;
    int j = mid + 1;

    for(int k = low; k <= high; k = k + 1)
    {
        aux[k] = arr[k];
    }

    for(int k = low; k <= high; k = k + 1)
    {
        if(i > mid)
        {
            arr[k] = aux[j];
            j = j + 1;
        }
        else if(j > high)
        {
            arr[k] = aux[i];
            i = i + 1;
        }
        else if(aux[j] < aux[i])
        {
            arr[k] = aux[j];
            j = j + 1;
        }
        else
        {
            arr[k] = aux[i];
            i = i + 1;
        }
    }
}

/*
void merge2(int* arr, int low, int mid, int high)
{
    int i, j, k; 
    int n1 = mid - low + 1; 
    int n2 =  high - mid; 

    // create temp arrays
    int L[n1], R[n2]; 

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i = i + 1) 
	{
        L[i] = arr[low + i]; 
	}
    for (j = 0; j < n2; j = j + 1) 
	{
        R[j] = arr[mid + 1 + j]; 
	}

    // Merge the temp arrays back into arr[l..r]
    i = 0;      // Initial index of first subarray 
    j = 0;      // Initial index of second subarray 
    k = low;    // Initial index of merged subarray 
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
*/

void quickSort(int* array, int low, int high)
{
    if(low < high)
    {
        int j = partition(array, low, high);
        quickSort(array, low, j - 1);
        quickSort(array, j + 1, high);
    }
}

int partition(int* array, int low, int high)
{
    int i = low;
    int j = high + 1;
    int v = array[low];
    int temp;
    while(1)
    {
        i = i + 1;
        while(array[i] < v)
        {
            if(i == high)
            {
                break;
            }
            i = i + 1;
        }
        j = j - 1;
        while(v < array[j])
        {
            if(j == low)
            {
                break;
            }
            j = j - 1;
        }
        if(i >= j)
        {
            break;
        }
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
    temp = array[low];
    array[low] = array[j];
    array[j] = temp;
    return j;
}

/*
// From the Cormen text - much slower
int partition2(int* array, int low, int high)
{
    int x = array[high];
    int i = low - 1;
    int temp;
    for(int j = low; j < high; j = j + 1)
    {
        if(array[j] <= x)
        {
            i = i + 1;
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return i + 1;
}
*/

MaxSA findMaxCrossingSubarray(int* A, int low, int mid, int high)
{
    MaxSA msdata;

    int leftSum = INT_MIN;
    int sum = 0;
    for(int i = mid; i >= low; i = i - 1)
    {
        sum = sum + A[i];
        if(sum > leftSum)
        {
            leftSum = sum;
            msdata.lowIndex = i;
        }
    }

    int rightSum = INT_MIN;
    sum = 0;
    for(int j = mid + 1; j <= high; j = j + 1)
    {
        sum = sum + A[j];
        if(sum > rightSum)
        {
            rightSum = sum;
            msdata.highIndex = j;
        }
    }

    msdata.maxSum = leftSum + rightSum; 
    return msdata;
}

MaxSA findMaxSubarray(int* A, int low, int high)
{
    MaxSA leftms;
    MaxSA rightms;
    MaxSA crossms;

    if(high == low)
    {
        crossms.lowIndex = low;
        crossms.highIndex = high;
        crossms.maxSum = A[low];
        return crossms;
    }
    else
    {
        int mid = (low + high) / 2;
        leftms = findMaxSubarray(A, low, mid);
        rightms = findMaxSubarray(A, mid + 1, high);
        crossms = findMaxCrossingSubarray(A, low, mid, high);
        if(leftms.maxSum >= rightms.maxSum && leftms.maxSum >= crossms.maxSum)
        {
            return leftms;
        }
        else if(rightms.maxSum >= leftms.maxSum && rightms.maxSum >= crossms.maxSum)
        {
            return rightms;
        }
        else
        {
            return crossms;
        }
    }
}
