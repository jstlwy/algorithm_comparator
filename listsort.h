#ifndef LISTSORT_H
#define LISTSORT_H
#include "linklist.h"

// Quadratic
void selectionSortIntLL(List* list);
List* selectionSortIntLLSedge(List* list);
void insertionSortIntLL(List* list);
void insertionSortIntLLSedge(List* list);

// Alternate directions in passes through the list?
void shellSortIntLL(List* list);

// Linearithmic
Node* mergeIntLL(Node* a, Node *b);
Node* mergeSortIntLL(Node* c);

#endif
