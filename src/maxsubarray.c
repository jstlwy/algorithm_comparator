#include "maxsubarray.h"
#include <limits.h>

struct max_subarray find_max_crossing_subarray(int* const array,
	size_t const low, size_t const mid, size_t const high)
{
	struct max_subarray m;

	int left_sum = INT_MIN;
	int sum = 0;
	for (size_t i = mid; i >= low; i--)
	{
		sum += array[i];
		if (sum > left_sum)
		{
			left_sum = sum;
			m.low_index = i;
		}
	}

	int right_sum = INT_MIN;
	sum = 0;
	for (size_t j = mid + 1; j <= high; j++)
	{
		sum += array[j];
		if (sum > right_sum)
		{
			right_sum = sum;
			m.high_index = j;
		}
	}

	m.max_sum = left_sum + right_sum; 
	return m;
}


struct max_subarray find_max_subarray(int* const array,
	size_t const low, size_t const high)
{
	struct max_subarray leftms;
	struct max_subarray rightms;
	struct max_subarray crossms;

	if (high == low)
	{
		crossms.low_index = low;
		crossms.high_index = high;
		crossms.max_sum = array[low];
		return crossms;
	}
	else
	{
		size_t const mid = (low + high) / 2;
		leftms = find_max_subarray(array, low, mid);
		rightms = find_max_subarray(array, mid + 1, high);
		crossms = find_max_crossing_subarray(array, low, mid, high);
		if (leftms.max_sum >= rightms.max_sum && leftms.max_sum >= crossms.max_sum)
		{
			return leftms;
		}
		else if (rightms.max_sum >= leftms.max_sum && rightms.max_sum >= crossms.max_sum)
		{
			return rightms;
		}
		else
		{
			return crossms;
		}
	}
}

