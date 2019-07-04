#include "linklist.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

List* initList()
{
    List* newList = malloc(sizeof(List));
    newList->size = 0;
    newList->first = NULL;
    newList->last = NULL;
    return newList;
}

int sizeOfList(List* list)
{
    return list->size;
}

void insertAtHead(List* list, void* newData)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->data = newData;
    newNode->previous = NULL;

    if(list->first == NULL)
    {
        newNode->next = NULL;
        list->last = newNode;
    }
    else
    {
        Node* oldFirstNode = list->first;
        newNode->next = oldFirstNode;
        oldFirstNode->previous = newNode;   
    }

    list->first = newNode;
    list->size = list->size + 1;
}

void insertAtTail(List* list, void* newData)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = NULL;

    if(list->last == NULL)
    {
        list->first = newNode;
        newNode->previous = NULL;
    }
    else
    {
        Node* oldLastNode = list->last;
        oldLastNode->next = newNode;
        newNode->previous = oldLastNode;
    }

    list->last = newNode;
    list->size = list->size + 1;
}

void insertAtIndex(List* list, void* newData, int position)
{
    if(list->first == NULL)
    {

    }
    else
    {
        
    }
    
    list->size = list->size + 1;
}

void deleteFromHead(List* list)
{
    Node* oldFirstNode = list->first;
    if(oldFirstNode != NULL)
    {
        if(oldFirstNode == list->last)
        {
            list->first = NULL;
            list->last = NULL;
        }
        else
        {
            Node* newFirstNode = oldFirstNode->next;
            newFirstNode->previous = NULL;
            list->first = newFirstNode;
        }
        free(oldFirstNode);
        list->size = list->size - 1;
    }
}

void deleteFromTail(List* list)
{
    Node* oldLastNode = list->last;
    if(oldLastNode != NULL)
    {
        if(oldLastNode == list->first)
        {
            list->first = NULL;
            list->last = NULL;
        }
        else
        {
            Node* newLastNode = oldLastNode->previous;
            newLastNode->next = NULL;
            list->last = newLastNode;
        }
        free(oldLastNode);
        list->size = list->size - 1;
    }
}

void deleteFromIndex(List* list, int position)
{

}

void deleteList(List* list)
{
    Node* currentNode = list->first;
    Node* nextNode;
    while(currentNode != NULL)
    {
        nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }
    free(list);
}
