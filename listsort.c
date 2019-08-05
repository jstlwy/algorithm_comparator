#include "listsort.h"
#include <stdlib.h>

void selectionSortIntLL(List* list)
{
	Node* mainNode = list->first;
	Node* nextNode;
	Node* minNode;
	int minValue;
	int nextNodeValue;
	while(mainNode != NULL)
	{
		minValue = mainNode->data;
		nextNode = mainNode->next;
		while(nextNode != NULL)
		{
			nextNodeValue = nextNode->data;
			if(nextNodeValue < minValue)
			{
				minValue = nextNodeValue;
				minNode = nextNode;
			}
			nextNode = nextNode->next;
		}
		minNode->data = mainNode->data;
		mainNode->data = minValue;
		mainNode = mainNode->next;
	}
}

List* selectionSortIntLLSedge(List* list)
{
    List* newList = initList();
    Node* maxNode;
	while(list->first != NULL)
	{
        maxNode = findMaxNode(list);
        unlinkNode(list, maxNode);
        insertAtHead(newList, maxNode);
	}
    free(list);
    return newList;
}

void insertionSortIntLL(List* list)
{
	Node* fwdNode = list->first->next;
    Node* revNode;
    Node* revNodeNext;
    while(fwdNode != NULL)
	{
        int key = fwdNode->data;
        revNode = fwdNode->previous;
        revNodeNext = fwdNode;
        int revNodeData = revNode->data;
		while(revNode != NULL && revNodeData > key)
		{
            revNode->next->data = revNodeData;
            revNodeNext = revNode;
			revNode = revNode->previous;
            if(revNode != NULL)
            {
                revNodeData = revNode->data;
            }
		}
        revNodeNext->data = key;
        fwdNode = fwdNode->next;
	}
}

void insertionSortIntLLSedge(List* list)
{
    Node dummy;
    Node* b = &dummy;
    b->next = NULL;
    Node* t;
    Node* u; 
    Node* x;
    for(t = list->first; t != NULL; t = u)
    {
        u = t->next;
        for(x = b; x->next != NULL; x = x->next)
        {
            if(x->next->data > t->data)
            {
                break;
            }
        }
        t->next = x->next;
        x->next = t;
    }
    list->first = b->next;
}

Node* mergeIntLL(Node* a, Node* b)
{
    Node head;
    Node* c = &head;

    while(a != NULL && b != NULL)
    {
        if(a->data < b->data)
        {
            c->next = a;
            c = a;
            a = a->next;
        }
        else
        {
            c->next = b;
            c = b;
            b = b->next;
        }
        
    }

    if(a == NULL)
    {
        c->next = b;
    }
    else
    {
        c->next = a;
    }
    
    return head.next;
}

Node* mergeSortIntLL(Node* c)
{
    Node* a;
    Node* b;

    if(c == NULL || c->next == NULL)
    {
        return c;
    }

    a = c;
    b = c->next;

    while(b != NULL && b->next != NULL)
    {
        c = c->next;
        b = b->next->next;
    }

    b = c->next;
    c->next = NULL;
    return mergeIntLL(mergeSortIntLL(a), mergeSortIntLL(b));
}
