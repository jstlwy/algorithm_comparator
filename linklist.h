#ifndef LINKLIST_H
#define LINKLIST_H

typedef struct LLNode {
    int rank;
    int data;
    struct LLNode* previous;
    struct LLNode* next;
} LLNode;

LLNode* initRandIntLL(int size, int smallestInt, int largestInt);
void insertAtHead(LLNode** headNode, LLNode* newNode);
void insertAtTail(LLNode** headNode, LLNode* newNode);
void insertAtIndex(LLNode** headNode, int position);
void deleteFromHead(LLNode** headNode);
void deleteFromTail(LLNode** headNode);
void deleteFromIndex(LLNode** headNode, int position);
void deleteList(LLNode** headNode);
int sizeOfList(LLNode* headNode);
void printList(LLNode* headNode);

#endif