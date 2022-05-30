#include "pqueue.h"
#include <stdlib.h>

MaxPQ* initMaxPQOfSize(int size)
{
	MaxPQ* pq = malloc(sizeof(MaxPQ));
	// MaxPQ array will be initialized with n slots,
	// n-1 of which can be used to hold keys.
	// First slot will always be an empty sentinel.
	int initArraySize = size + 1;
	Key** newArray = malloc(initArraySize * sizeof(Key*));
	for(int i = 0; i < initArraySize; i++)
	{
		newArray[i] = NULL;
	}
	pq->keys = newArray;
	pq->numItems = 0;
	pq->arraySize = initArraySize - 1;
	return pq;
}

void insertIntoPQ(MaxPQ* pq, Key* key)
{
	int n = pq->numItems + 1;
	if(pq->arraySize == pq->numItems)
	{
		int newArraySize = (pq->arraySize * 2) + 1;
		pq->arraySize = newArraySize;
		Key** newArray = malloc(newArraySize * sizeof(Key*));
		for(int i = 1; i <= pq->arraySize; i++)
		{
			newArray[i] = pq->keys[i];
		}
		int* oldArray = pq->keys;
		pq->keys = newArray;
		free(oldArray);
	}
	pq->keys[n] = key;
	swimUpPQ(pq->keys, n);
	pq->numItems = n;
}

Key* maxInPQ(MaxPQ* pq)
{
	return pq->keys[1];
}

void deleteMaxInPQ(MaxPQ* pq)
{
	Key* max = pq->keys[1];
	free(max);
	pq->keys[1] = pq->keys[pq->numItems];
	pq->numItems -= 1;
	sinkDownPQ(pq->keys, pq->numItems, 1);
	if(pq->numItems <= (pq->arraySize / 4))
	{
		int newArraySize = (pq->arraySize / 2) + 1;
		pq->arraySize = newArraySize;
		int* newArray = malloc(newArraySize * sizeof(Key));
		for(int i = 1; i <= pq->arraySize; i++)
		{
			newArray[i] = pq->keys[i];
		}
		int* oldArray = pq->keys;
		pq->keys = newArray;
		free(oldArray);        
	}
}

void swimUpPQ(Key** array, int k)
{
	while(k > 1 && array[k/2]->value < array[k]->value)
	{
		Key* temp = array[k/2];
		array[k/2] = array[k];
		array[k] = temp;
		k = k/2;
	}
}

void sinkDownPQ(Key** array, int size, int k)
{
	while(2*k <= size)
	{
		int j = 2 * k;
		if(j < size && array[j]->value < array[j+1]->value)
		{
			j++;
		}
		if(array[k]->value >= array[j]->value)
		{
			break;
		}
		Key* temp = array[k];
		array[k] = array[j];
		array[j] = temp;
		k = j;
	}
}

bool isEmptyPQ(MaxPQ* pq)
{
	if(pq->numItems == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int sizeOfPQ(MaxPQ* pq)
{
	return pq->numItems;
}

void heapsort(array, int size)
{
	for(int k = size / 2; k >= 1; k--)
	{

	}
	while(size > 1)
	{

	}
}
