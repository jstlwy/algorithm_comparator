#include "linklist.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

List* initList(void)
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

List* copyIntList(List* originalList)
{
    List* newList = initList();
    Node* currentNode = originalList->first;
    while(currentNode != NULL)
    {
        Node* newNode = malloc(sizeof(Node));
        newNode->data = currentNode->data;
		insertAtTail(newList, newNode);
        currentNode = currentNode->next;
    }
    return newList;
}

void printIntListCurses(List* list)
{
    Node* currentNode = list->first;
	while(currentNode != NULL)
	{
		printw("%d ", currentNode->data);
		currentNode = currentNode->next;
	}
}

bool listContainsNode(List* list, Node* node)
{
    bool doesContainNode = false;
    if(list != NULL && node != NULL)
    {
        Node* currentNode = list->first;
        while(currentNode != NULL)
        {
            if(node == currentNode)
            {
                doesContainNode = true;
            }
            currentNode = currentNode->next;
        }
    }
    return doesContainNode;
}

Node* findMaxNode(List* list)
{
    Node* maxNode = list->first;
    if(maxNode != NULL)
    {
        Node* currentNode = maxNode->next;
        while(currentNode != NULL)
        {
            if(currentNode->data > maxNode->data)
            {
                maxNode = currentNode;
            }
            currentNode = currentNode->next;
        }
    }
    return maxNode;
}

Node* findMinNode(List* list)
{
    Node* minNode = list->first;
    if(minNode != NULL)
    {
        Node* currentNode = minNode->next;
        while(currentNode != NULL)
        {
            if(currentNode->data < minNode->data)
            {
                minNode = currentNode;
            }
            currentNode = currentNode->next;
        }
    }
    return minNode;
}

void insertAtHead(List* list, Node* newNode)
{
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

void insertAtTail(List* list, Node* newNode)
{
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

void insertBeforeIndex(List* list, Node* newNode, int index)
{

}

void updateNode(Node* node, int newData)
{

}

void deleteHead(List* list)
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

void deleteTail(List* list)
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

void unlinkNode(List* list, Node* node)
{
    if(list != NULL && node != NULL)
    {
        short linkCond = 0;

        if(node->previous != NULL)
        {
            linkCond = linkCond | 0b01;
        }
        if(node->next != NULL)
        {
            linkCond = linkCond | 0b10;
        }

        switch(linkCond)
        {
            case 0b00:
                // The node doesn't link to anything.
                list->first = NULL;
                list->last = NULL;
                break;
            case 0b01:
                // The node only links to a preceding node.
                // It must be the tail of the list.
                list->last = node->previous;
                node->previous->next = NULL;
                break;
            case 0b10:
                // The node only links to a succeeding node.
                // It must be the head of the list.
                list->first = node->next;
                node->next->previous = NULL;
                break;
            case 0b11:
                // The node is between two other nodes.
                node->previous->next = node->next;
                node->next->previous = node->previous;
                break;
            default:
                break;
        }

        list->size -= 1;
    }
}

void deleteNode(List* list, Node* node)
{
    if(node != NULL)
    {
        unlinkNode(list, node);
        free(node);
    }
}

void deleteList(List* list)
{
    Node* currentNode = list->first;
    while(currentNode != NULL)
    {
        Node* nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }
    free(list);
}
