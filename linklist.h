#ifndef LINKLIST_H
#define LINKLIST_H

typedef struct LLNode {
    int rank;
    int data;
    struct LLNode* previous;
    struct LLNode* next;
} LLNode;

LLNode* initLinkedList(int numNodes);

void insertNodeAtHead (LLNode* newNode);

void insertNodeAtTail (LLNode* newNode);

void removeNode (LLNode* targetNode);

#endif