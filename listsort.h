#ifndef LISTSORT_H
#define LISTSORT_H
#include "linklist.h"

// Quadratic
void selectionSortIntLL(List* list);
void insertionSortIntLL(List* list);

// Alternate directions in passes through the list?
void shellSortIntLL(List* list);

// Linearithmic
Node* mergeSedg(Node* a, Node *b);
Node* mergeSortSedg(Node* c);

Node* mergeSortList(Node* head);
Node* mergeList(Node* list1, Node* list2);
Node* bisectList(Node* head);

#endif
