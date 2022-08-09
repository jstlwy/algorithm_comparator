#include "arraysort.h"
#include <stdlib.h>

void selection_sort(int *array, const int array_size)
{
	for (int i = 0; i < array_size; i++) {
		int min = i;
		for (int j = i + 1; j < array_size; j++) {
			if (array[j] < array[min]) {
				min = j;
			}
		}
		const int temp = array[i];
		array[i] = array[min];
		array[min] = temp;
	}
}


void insertion_sort(int *array, const int array_size)
{
	for (int i = 1; i < array_size; i++) {
		const int key = array[i];
		int j = i - 1;
		while (j >= 0 && array[j] > key) {
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = key;	
	}
}


void shellsort(int *array, const int array_size)
{
	// Using the OEIS A003462 integer sequence to sort:
	// 0.5(3^n - 1) -> 1, 4, 13, 40, 121, 364, 1093, 3280, ...
	// Results in worst-case time complexity of Theta(N^1.5).

	// Start by setting h equal to the largest number
	// in that sequence that is less than 1/3 of the array size.
	int h = 1;
	while (h < array_size / 3) {
		h = (3 * h) + 1;
	}

	// Now, begin sorting the array
	while (h >= 1) {
		for (int i = h; i < array_size; i++) {
			for (int j = i; j >= h && array[j] < array[j - h]; j -= h) {
				const int temp = array[j];
				array[j] = array[j - h];
				array[j - h] = temp;
			}
		}
		h /= 3;
	}
}


void merge_sort_array(int *array, const int array_size)
{
	int *helper_arr = malloc(array_size * sizeof(int));
	merge_sort_td(array, helper_arr, 0, array_size - 1);
	//merge_sort_bu(array, helper_arr, array_size);
}


void merge_sort_td(int *arr, int *helper_arr, int low, int high)
{
	if (low < high) {
		int mid = low + ((high - low) / 2);
		merge_sort_td(arr, helper_arr, low, mid);
		merge_sort_td(arr, helper_arr, mid + 1, high);
		merge(arr, helper_arr, low, mid, high);
	}
}


void merge_sort_bu(int *arr, int *helper_arr, const int array_size)
{
	for (int size = 1; size < array_size; size = size + size) {
		for (int low = 0; low < array_size - size; low = low + size + size) {
			int value1 = low + size + size - 1;
			int value2 = array_size - 1;
			int min = (value1 < value2) ? value1 : value2;
			merge(arr, helper_arr, low, low + size - 1, min);
		}
	}
}


void merge(int *arr, int *helper_arr, int first, int mid, int last)
{
	// Copy the contents of the original array to the helper array
	for (int i = first; i <= last; i++) {
		helper_arr[i] = arr[i];
	}

	// Now copy from the helper array back to the original
	// while comparing the lower/left half to the upper/right half
	int i = first;
	int l = first;
	int r = mid + 1;
	while (l <= mid && r <= last) {
		if (helper_arr[l] <= helper_arr[r]) {
			arr[i++] = helper_arr[l++];
		} else {
			arr[i++] = helper_arr[r++];
		}
	}

	// Copy anything left in either half
	while (l <= mid) {
		arr[i++] = helper_arr[l++];
	}
	while (r <= last) {
		arr[i++] = helper_arr[r++];
	}
}


void quicksort(int *array, int low, int high)
{
	if (low < high) {
		int j = partition(array, low, high);
		quicksort(array, low, j - 1);
		quicksort(array, j + 1, high);
	}
}


int partition(int *array, int low, int high)
{
	int i = low;
	int j = high + 1;
	int v = array[low];
	while (1) {
		i++;
		while (array[i] < v) {
			if (i == high) {
				break;
			}
			i++;
		}
		j--;
		while (v < array[j]) {
			if (j == low) {
				break;
			}
			j--;
		}
		if (i >= j) {
			break;
		}
		const int temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
	if (low != j) {
		const int temp = array[low];
		array[low] = array[j];
		array[j] = temp;
	}
	return j;
}


void swim_up(int *arr, int k)
{
	while (k > 1 && arr[k/2] < arr[k]) {
		int temp = arr[k/2];
		arr[k/2] = arr[k];
		arr[k] = temp;
		k = k/2;
	}
}


void sink_down(int *arr, int k, int size)
{
	while (2*k <= size) {
		int j = 2 * k;
		if (j < size && arr[j] < arr[j+1]) {
			j++;
		}
		if (arr[k] >= arr[j]) {
			break;
		}
		const int temp = arr[k];
		arr[k] = arr[j];
		arr[j] = temp;
		k = j;
	}
}


void heapsort_array(int *arr, int l, int r)
{
	int N = r - l + 1;
	int* pq = arr + l - 1;
	for (int k = N/2; k >= 1; k--) {
		sink_down(pq, k, N);
	}
	while (N > 1) {
		const int temp = pq[1];
		pq[1] = pq[N];
		pq[N] = temp;
		N--;
		sink_down(pq, 1, N);
	}
}

