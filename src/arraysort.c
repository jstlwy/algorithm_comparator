#include "arraysort.h"
#include <stdlib.h>

void selection_sort(const size_t n, int array[const static n])
{
    for (size_t i = 0; i < n; i++) {
        size_t min = i;
        for (size_t j = i + 1; j < n; j++) {
            if (array[j] < array[min]) {
                min = j;
            }
        }
        int const temp = array[i];
        array[i] = array[min];
        array[min] = temp;
    }
}

void insertion_sort(const size_t n, int array[const static n])
{
    for (size_t i = 1; i < n; i++) {
        int const key = array[i];
        int j = i - 1;
        while ((j >= 0) && (array[j] > key)) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;	
    }
}

void shellsort(const size_t n, int array[const static n])
{
    // Using the OEIS A003462 integer sequence to sort:
    // 0.5(3^n - 1) -> 1, 4, 13, 40, 121, 364, 1093, 3280, ...
    // Results in worst-case time complexity of Theta(N^1.5).

    // Start by setting h equal to the largest number
    // in that sequence that is less than 1/3 of the array size.
    size_t h = 1;
    while (h < n / 3) {
        h = (3 * h) + 1;
    }

    // Now, begin sorting the array
    while (h >= 1) {
        for (size_t i = h; i < n; i++) {
            for (size_t j = i; (j >= h) && (array[j] < array[j - h]); j -= h) {
                const int temp = array[j];
                array[j] = array[j - h];
                array[j - h] = temp;
            }
        }
        h /= 3;
    }
}

void merge_sort_array(const size_t n, int array[const static n])
{
    int* const helper_arr = malloc(n * sizeof(int));
    merge_sort_td(array, helper_arr, 0, n - 1);
    //merge_sort_bu(n, array, helper_arr);
    free(helper_arr);
}

void merge_sort_td(int arr[const], int helper_arr[const],
    const size_t low, const size_t high)
{
    if (low < high) {
        const int mid = low + ((high - low) / 2);
        merge_sort_td(arr, helper_arr, low, mid);
        merge_sort_td(arr, helper_arr, mid + 1, high);
        merge(arr, helper_arr, low, mid, high);
    }
}

void merge_sort_bu(const size_t n, int arr[const static n], int helper_arr[const static n])
{
    for (size_t size = 1; size < n; size = size + size) {
        for (size_t low = 0; low < n - size; low = low + size + size) {
            const size_t value1 = low + size + size - 1;
            const size_t value2 = n - 1;
            const size_t min = (value1 < value2) ? value1 : value2;
            merge(arr, helper_arr, low, low + size - 1, min);
        }
    }
}

void merge(
    int arr[const],
    int helper_arr[const],
    const size_t first,
    const size_t mid,
    const size_t last)
{
    // Copy the contents of the original array to the helper array
    for (size_t i = first; i <= last; i++) {
        helper_arr[i] = arr[i];
    }

    // Now copy from the helper array back to the original
    // while comparing the lower/left half to the upper/right half
    size_t i = first;
    size_t l = first;
    size_t r = mid + 1;
    while ((l <= mid) && (r <= last)) {
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

void quicksort(int array[const], const size_t low, const size_t high)
{
    if (low < high) {
        size_t j = partition(array, low, high);
        quicksort(array, low, j - 1);
        quicksort(array, j + 1, high);
    }
}

size_t partition(int array[const], const size_t low, const size_t high)
{
    size_t i = low;
    size_t j = high + 1;
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

void swim_up(int arr[const], size_t k)
{
    while ((k > 1) && (arr[k/2] < arr[k])) {
        const int temp = arr[k/2];
        arr[k/2] = arr[k];
        arr[k] = temp;
        k = k/2;
    }
}

void sink_down(int arr[const], size_t k, const size_t size)
{
    while (2*k <= size) {
        size_t j = 2 * k;
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

void heapsort_array(int arr[const], const size_t l, const size_t r)
{
    size_t N = r - l + 1;
    int* const pq = arr + l - 1;
    for (size_t k = N/2; k >= 1; k--) {
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
