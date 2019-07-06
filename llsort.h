#ifndef LLSORT_H
#define LLSORT_H
#include "linklist.h"

void insertionSortIntLL(List* list);
void mergeSortIntLL(Node* head, Node* tail, int size);
void mergeIntLL(Node* leftHead, int leftSize, Node* rightHead, int rightSize);

#endif