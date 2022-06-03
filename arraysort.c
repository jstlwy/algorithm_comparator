#include "arraysort.h"
#include <limits.h>

void selection_sort(int *array, const int array_size)
{
	for (int i = 0; i < array_size; i++) {
		int min = i;
		for (int j = i + 1; j < array_size; j++) {
			if (array[j] < array[min]) {
				min = j;
			}
		}
		int temp = array[i];
		array[i] = array[min];
		array[min] = temp;
	}
}


void insertion_sort(int *array, const int array_size)
{
	for (int i = 1; i < array_size; i++) {
		int key = array[i];
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
	// h = "gap"
	int h = 1;
	// First, find largest number by which to divide array
	// OEIS A003462: 0.5(3^k - 1) results in worst-case Theta(N^1.5)
	while (h < array_size / 3) {
		// 1, 4, 13, 40, 121, 364, 1093, ...
		h = (3 * h) + 1;
	}
	// Now, commence h-sorting the array
	while (h >= 1) {
		for (int i = h; i < array_size; i++) {
			for (int j = i; j >= h && array[j] < array[j - h]; j -= h) {
				int temp = array[j];
				array[j] = array[j - h];
				array[j - h] = temp;
			}
		}
		h /= 3;
	}
}


void merge_sort_array(int* array, const int array_size)
{
	int aux[array_size];
	merge_sort_td(array, aux, 0, array_size - 1);
	//merge_sort_bu(array, aux, array_size);
}


void merge_sort_td(int* arr, int* aux, int low, int high)
{
	if (low < high) {
		int mid = low + ((high - low) / 2);
		merge_sort_td(arr, aux, low, mid);
		merge_sort_td(arr, aux, mid + 1, high);
		merge(arr, aux, low, mid, high);
	}
}


void merge_sort_bu(int* arr, int* aux, const int array_size)
{
	for (int size = 1; size < array_size; size = size + size) {
		for (int low = 0; low < array_size - size; low = low + size + size) {
			int value1 = low + size + size - 1;
			int value2 = array_size - 1;
			int min = (value1 < value2) ? value1 : value2;
			merge(arr, aux, low, low + size - 1, min);
		}
	}
}


void merge(int* arr, int* aux, int low, int mid, int high)
{
	int i = low;
	int j = mid + 1;

	for (int k = low; k <= high; k++) {
		aux[k] = arr[k];
	}

	for (int k = low; k <= high; k++) {
		if (i > mid) {
			arr[k] = aux[j];
			j++;
		}
		else if (j > high) {
			arr[k] = aux[i];
			i++;
		}
		else if (aux[j] < aux[i]) {
			arr[k] = aux[j];
			j++;
		}
		else {
			arr[k] = aux[i];
			i++;
		}
	}
}


void quicksort(int* array, int low, int high)
{
	if (low < high) {
		int j = partition(array, low, high);
		quicksort(array, low, j - 1);
		quicksort(array, j + 1, high);
	}
}


int partition(int* array, int low, int high)
{
	int i = low;
	int j = high + 1;
	int v = array[low];
	int temp;
	while (1) {
		i++;
		while (array[i] < v) {
			if (i == high)
				break;
			i++;
		}
		j--;
		while (v < array[j]) {
			if (j == low)
				break;
			j--;
		}
		if (i >= j)
			break;
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
	if (low != j) {
		temp = array[low];
		array[low] = array[j];
		array[j] = temp;
	}
	return j;
}


void swim_up(int* arr, int k)
{
	while (k > 1 && arr[k/2] < arr[k]) {
		int temp = arr[k/2];
		arr[k/2] = arr[k];
		arr[k] = temp;
		k = k/2;
	}
}


void sink_down(int* arr, int k, int size)
{
	while (2*k <= size) {
		int j = 2 * k;
		if (j < size && arr[j] < arr[j+1])
			j++;
		if (arr[k] >= arr[j])
			break;
		int temp = arr[k];
		arr[k] = arr[j];
		arr[j] = temp;
		k = j;
	}
}


void heapsort_array(int* arr, int l, int r)
{
	int N = r - l + 1;
	int* pq = arr + l - 1;
	for (int k = N/2; k >= 1; k--) {
		sink_down(pq, k, N);
	}
	while (N > 1) {
		int temp = pq[1];
		pq[1] = pq[N];
		pq[N] = temp;
		N--;
		sink_down(pq, 1, N);
	}
}


struct max_subarray find_max_crossing_subarray(int *array, int low, int mid, int high)
{
	struct max_subarray m;

	int left_sum = INT_MIN;
	int sum = 0;
	for (int i = mid; i >= low; i--) {
		sum += array[i];
		if (sum > left_sum) {
			left_sum = sum;
			m.low_index = i;
		}
	}

	int right_sum = INT_MIN;
	sum = 0;
	for (int j = mid + 1; j <= high; j++) {
		sum += array[j];
		if (sum > right_sum) {
			right_sum = sum;
			m.high_index = j;
		}
	}

	m.max_sum = left_sum + right_sum; 
	return m;
}


struct max_subarray find_max_subarray(int *array, int low, int high)
{
	struct max_subarray leftms;
	struct max_subarray rightms;
	struct max_subarray crossms;

	if (high == low) {
		crossms.low_index = low;
		crossms.high_index = high;
		crossms.max_sum = array[low];
		return crossms;
	}
	else {
		int mid = (low + high) / 2;
		leftms = find_max_subarray(array, low, mid);
		rightms = find_max_subarray(array, mid + 1, high);
		crossms = find_max_crossing_subarray(array, low, mid, high);
		if (leftms.max_sum >= rightms.max_sum && leftms.max_sum >= crossms.max_sum)
			return leftms;
		else if (rightms.max_sum >= leftms.max_sum && rightms.max_sum >= crossms.max_sum)
			return rightms;
		else
			return crossms;
	}
}

