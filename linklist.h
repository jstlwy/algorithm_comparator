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
void insertBeforeIndex(List* list, void* newData, int index);
void changeIndex(List* list, void* newData, int index);
void deleteHead(List* list);
void deleteTail(List* list);
void deleteIndex(List* list, int index);
void deleteNode(List* list, Node* node);
void deleteList(List* list);

#endif