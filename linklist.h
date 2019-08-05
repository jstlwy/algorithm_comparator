#ifndef LINKLIST_H
#define LINKLIST_H
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* previous;
    struct Node* next;
} Node;

typedef struct List {
    int size;
    Node* first;
    Node* last;
} List;

List* initList();
int sizeOfList(List* list);
List* copyIntList(List* originalList);

void printIntListCurses(List* list);
bool listContainsNode(List* list, Node* node);
Node* findMaxNode(List* list);
Node* findMinNode(List* list);

void insertAtHead(List* list, Node* newNode);
void insertAtTail(List* list, Node* newNode);
void insertBeforeIndex(List* list, Node* newNode, int index);
void updateNode(Node* node, int newData);

void deleteHead(List* list);
void deleteTail(List* list);
void unlinkNode(List* list, Node* node);
void deleteNode(List* list, Node* node);
void deleteList(List* list);

#endif