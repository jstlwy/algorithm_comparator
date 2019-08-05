#ifndef PQUEUE_H
#define PQUEUE_H
#include <stdbool.h>

typedef struct Key {
    int value;
} Key;

typedef struct MaxPQ {
    int arraySize;
    int numItems;
    Key** keys;
} MaxPQ;

MaxPQ* initMaxPQ();
MaxPQ* initMaxPQOfSize(int size);
void insertIntoPQ(MaxPQ* pq, Key* key);
Key* maxInPQ(MaxPQ* pq);
void deleteMaxInPQ(MaxPQ* pq);
void swim(Key* array, int k);
void sink(Key* array, int size, int k);
bool isEmptyPQ(MaxPQ* pq);
int sizeOfPQ(MaxPQ* pq);
void heapsort(array, int size);

#endif