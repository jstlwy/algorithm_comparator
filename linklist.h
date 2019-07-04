#ifndef LINKLIST_H
#define LINKLIST_H

typedef struct Node {
    void* data;
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
void insertAtHead(List* list, void* newData);
void insertAtTail(List* list, void* newData);
void insertAtIndex(List* list, void* newData, int position);
void deleteFromHead(List* list);
void deleteFromTail(List* list);
void deleteFromIndex(List* list, int position);
void deleteList(List* list);

#endif