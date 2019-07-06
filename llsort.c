#include "llsort.h"
#include <stdlib.h>

void insertionSortIntLL(List* list)
{
	Node* node1 = list->first->next;
    Node* node2;
    while(node1 != NULL)
	{
        node2 = node1->previous;
        int* node1Data = node1->data;
        int* node2Data = node2->data;
		while(node2 != NULL && *node2Data > *node1Data)
		{
            node2->next->data = node2->data;
			node2 = node2->previous;
            if(node2 != NULL)
            {
                node2Data = node2->data;
            }
		}
        node2->next->data = node1Data;
        node1 = node1->next;
	}
}

void mergeSortIntLL(Node* head, Node* tail, int size)
{
    if(head != tail)
    {
        int middle = size / 2;
        Node* leftTail = head;
        for(int i = 0; i < middle; i = i + 1)
        {
            leftTail = head->next;
        }
        Node* rightHead = leftTail->next;
        int rightSize = size - middle;
        mergeSortIntLL(head, leftTail, middle);
        mergeSortIntLL(rightHead, tail, rightSize);
        mergeIntLL(head, middle, rightHead, rightSize);
    }
}

void mergeIntLL(Node* leftHead, int leftSize, Node* rightHead, int rightSize)
{
    Node* origin = leftHead;
    int i = 0;
    int j = 0;
    int k = 0;
    int tempArraySize = leftSize + rightSize;
    int* tempArray[tempArraySize];
    int* leftData;
    int* rightData;

    while(i < leftSize && j < rightSize)
    {
        int* leftData = leftHead->data;
        int* rightData = rightHead->data;
        if(*leftData <= *rightData)
        {
            tempArray[k] = leftData;
            i = i + 1;
            if(i < leftSize)
            {
                leftHead = leftHead->next;
                leftData = leftHead->data;
            }
        }
        else
        {
            tempArray[k] = rightData;
            j = j + 1;
            if(j < rightSize)
            {
                rightHead = rightHead->next;
                rightData = rightHead->data;
            }
        }
        k = k + 1;
    }

    while(i < leftSize)
    {
        tempArray[k] = leftData;
        k = k + 1;
        i = i + 1;
        if(i < leftSize)
        {
            leftHead = leftHead->next;
            leftData = leftHead->data;
        }
    }

    while(j < rightSize)
    {
        tempArray[k] = rightData;
        k = k + 1;
        j = j + 1;
        if(j < rightSize)
        {
            rightHead = rightHead->next;
            rightData = rightHead->data;
        }
    }

    for(k = 0; k < tempArraySize; k = k + 1)
    {
        origin->data = tempArray[k];
        origin = origin->next;
    }
}
