#include "listsort.h"
#include <stdlib.h>

void insertionSortIntLL(List* list)
{
	Node* node1 = list->first->next;
    Node* node2;
    Node* node2Next;
    while(node1 != NULL)
	{
        node2Next = node1;
        node2 = node1->previous;
        int* node1Data = node1->data;
        int* node2Data = node2->data;
		while(node2 != NULL && *node2Data > *node1Data)
		{
            node2->next->data = node2Data;
            node2Next = node2;
			node2 = node2->previous;
            if(node2 != NULL)
            {
                node2Data = node2->data;
            }
		}
        node2Next->data = node1Data;
        node1 = node1->next;
	}
}

Node* mergeSedg(Node* a, Node* b)
{
    Node head;
    Node* c = &head;

    while(a != NULL && b != NULL)
    {
        int* aData = a->data;
        int* bData = b->data;
        if(*aData < *bData)
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

Node* mergeSortSedg(Node* c)
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
    return mergeSedg(mergeSortSedg(a), mergeSortSedg(b));
}

Node* mergeSortList(Node* head) 
{   
    Node* list1 = head; 
    if (list1 == NULL || list1->next == NULL)
    {   
        return list1;
    }   

    Node* list2 = bisectList(list1);

    return mergeList(mergeSortList(list1), mergeSortList(list2));
}

Node* mergeList(Node* list1, Node* list2)
{
    Node dummy_head;
    Node* tail = &dummy_head;

    while ( (list1 != NULL) && (list2 != NULL) )
    {   
        int* list1Data = list1->data;
        int* list2Data = list2->data;
        Node **min = (*list1Data < *list2Data) ? &list1 : &list2;
        Node *next = (*min)->next;
        tail = tail->next = *min;
        *min = next;
    }
    tail->next = list1 ? list1 : list2;
    return dummy_head.next;
}

Node* bisectList(Node* head)
{
    /* The fast pointer moves twice as fast as the slow pointer. */
    /* The prev pointer points to the node preceding the slow pointer. */
    Node* fast = head, *slow = head, *prev = NULL;

    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        prev = slow;
        slow = slow->next;
    }

    if (prev != NULL)
    {
        prev->next = NULL;
    }
    return slow;
}