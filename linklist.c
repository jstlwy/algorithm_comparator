#include "linklist.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

LLNode* initRandIntLL(int size, int smallestInt, int largestInt)
{
    if(size <= 0)
    {
        return NULL;
    }
    else
    {
        LLNode* headNode = NULL;
        for(int i = 0; i < size; i = i + 1)
        {
            LLNode* newNode = malloc(sizeof(LLNode));
            newNode->data = randomNum(smallestInt, largestInt);
            insertAtTail(&headNode, newNode);
        }
        return headNode;
    }
}

void insertAtHead(LLNode** headNode, LLNode* newNode)
{
    newNode->previous = NULL;

    if(*headNode == NULL)
    {
        newNode->next = NULL;
    }
    else
    {
        newNode->next = *headNode;
        (*headNode)->previous = newNode;   
    }

    *headNode = newNode;
}

void insertAtTail(LLNode** headNode, LLNode* newNode)
{
    if(*headNode == NULL)
    {
        *headNode = newNode;
    }
    else
    {
        LLNode* tempNode = *headNode;
        while(tempNode->next != NULL)
        {
            tempNode = tempNode->next;
        }
        tempNode->next = newNode;
        newNode->previous = tempNode;
        newNode->next = NULL;
    }
}

void insertAtIndex(LLNode** headNode, int position)
{

}

void deleteFromHead(LLNode** headNode)
{
    if(*headNode != NULL)
    {
        if((*headNode)->next == NULL)
        {
            free(*headNode);
            *headNode = NULL;
        }
        else
        {
            LLNode* tempNode = (*headNode)->next;
            tempNode->previous = NULL;
            free(*headNode);
            *headNode = tempNode;
        }
    }
}

void deleteFromTail(LLNode** headNode)
{
    if(*headNode != NULL)
    {
        if((*headNode)->next == NULL)
        {
            free(*headNode);
            *headNode = NULL;
        }
        else
        {
            LLNode* tempNode = *headNode;
            while(tempNode->next != NULL)
            {
                tempNode = tempNode->next;
            }
            tempNode->previous->next = NULL;
            free(tempNode);
        }
    }
}

void deleteFromIndex(LLNode** headNode, int position)
{

}

void deleteList(LLNode** headNode)
{
    LLNode* tempNode;
    while(*headNode != NULL)
    {
        tempNode = *headNode;
        *headNode = tempNode->next;
        free(tempNode);
    }
}

int sizeOfList(LLNode* headNode)
{
    if(headNode == NULL)
    {
        return 0;
    }
    else
    {
        int size = 0;
        LLNode* tempNode = headNode;
        do
        {
            size = size + 1;
            tempNode = tempNode->next;
        } while (tempNode != NULL);
        return size;
    }
}

void printList(LLNode* headNode)
{
    if(headNode != NULL)
    {
        LLNode* tempNode = headNode;
        do
        {
            printf("%d ", tempNode->data);
            tempNode = tempNode->next;
        } while (tempNode != NULL);
        printf("\n");
    }
}