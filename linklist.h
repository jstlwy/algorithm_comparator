#ifndef LINKLIST_H
#define LINKLIST_H

typedef struct LLNode {
    int rank;
    int data;
    struct LLNode* previous;
    struct LLNode* next;
} LLNode;

LLNode* initRandLinkedList(int numNodes);
void addToHead(LLNode* headNode, LLNode* newNode);
void deleteFromHead(LLNode* headNode);
void addToTail(LLNode* headNode, LLNode* newNode);
void deleteFromTail(LLNode* headNode);
void addAtPosition(LLNode* headNode, int position);
void deleteFromPosition(LLNode* headNode, int position);

#endif