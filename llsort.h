#ifndef LLSORT_H
#define LLSORT_H
#include "linklist.h"

void insertionSortIntLL(List* list);
void mergeSortIntLL(Node* head, Node* tail, int size);
void mergeIntLL(Node* leftHead, int leftSize, Node* rightHead, int rightSize);

Node* mergeSedg(Node* a, Node *b);
Node* mergeSortSedg(Node* c);

Node* mergeSortList(Node* head);
Node* mergeList(Node* list1, Node* list2);
Node* bisectList(Node* head);

#endif