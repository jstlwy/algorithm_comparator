#include "listsort.h"
#include <stdlib.h>

void selection_sort_list(doubly_linked_list* list)
{
	if(list == NULL)
	{
		return;
	}

	doubly_linked_node* current_node = list->first;
	while(main_node != NULL)
	{
		// Start by assuming the current node has the smallest value
		doubly_linked_node* min_node = current_node;
		int min_value = current_node->data;
		// Now look at every node after the current node.
		doubly_linked_node* next_node = current_node->next;
		while(next_node != NULL)
		{
			// Check the value of each subsequent node.
			// Keep updating the minimum node/value
			// as smaller values are discovered.
			int next_node_value = next_node->data;
			if(next_node_value < min_value)
			{
				min_value = next_node_value;
				min_node = next_node;
			}
			next_node = next_node->next;
		}
		// Swap the values of the current node
		// and the node with the smallest value
		min_node->data = current_node->data;
		current_node->data = min_value;
		// Start all over again from the next node
		current_node = current_node->next;
	}
}


doubly_linked_list* selection_sort_list_sw(doubly_linked_list* list)
{
	if(list == NULL)
	{
		return NULL;
	}

	// Create a new list
    doubly_linked_list* new_list = init_list();
	while(list->first != NULL)
	{
		// Find the largest node in the original list
        doubly_linked_node* max_node = find_max_node(list);
		// Remove it from the original list
        unlink_node(list, max_node);
		// Put it at the head of the new list.
		// Notice that each time this is done,
		// the head will be smaller.
        insert_at_head(new_list, max_node);
	}
	// Destroy the original list
    free(list);
	// Return the new list in place of the original list
    return new_list;
}


void insertion_sort_list(doubly_linked_list* list)
{
	if(list == NULL)
	{
		return;
	}

	// Start at the second node
	doubly_linked_node* current_node = list->first->next;
    while(current_node != NULL)
	{
        int current_value = current_node->data;
        doubly_linked_node* prior_node = current_node->previous;
        doubly_linked_node* prior_node_next = current_node;
		// As long as the prior nodes contain larger values than the current,
		// keep moving the current value backward through the list
		while(prior_node != NULL && prior_node->data > prior_node_next->data)
		{
			// Swap the values of the current pair
			int temp = prior_node->data;
            prior_node->data = prior_node_next->data;
			prior_node_next->data = temp;
			// Move on to the previous pair
            prior_node_next = prior_node;
			prior_node = prior_node->previous;
		}
        current_node = current_node->next;
	}
}


void insertion_sort_list_sw(doubly_linked_list* list)
{
    doubly_linked_node dummy;
    doubly_linked_node* b = &dummy;
    b->next = NULL;
    doubly_linked_node* t;
    doubly_linked_node* u; 
    doubly_linked_node* x;
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


doubly_linked_node* merge_list(doubly_linked_node* a, doubly_linked_node* b)
{
    doubly_linked_node head;
    doubly_linked_node* c = &head;

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

	c->next = (a == NULL) ? b : a;
    
    return head.next;
}


doubly_linked_node* merge_sort_list(doubly_linked_node* c)
{
    doubly_linked_node* a;
    doubly_linked_node* b;

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
    return merge_list(merge_sort_list(a), merge_sort_list(b));
}

