#include "listsort.h"
#include <stdlib.h>

void selection_sort_list(struct dllist * const list)
{
	if (list == NULL)
	{
		return;
	}

	struct dlnode* current_node = list->first;
	while (current_node != NULL)
	{
		// Start by assuming the current node has the smallest value
		struct dlnode* min_node = current_node;
		int min_value = current_node->data;
		// Now look at every node after the current node.
		struct dlnode* next_node = current_node->next;
		while (next_node != NULL)
		{
			// Check the value of each subsequent node.
			// Keep updating the minimum node/value
			// as smaller values are discovered.
			int next_node_value = next_node->data;
			if (next_node_value < min_value)
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


struct dllist* selection_sort_list_sw(struct dllist * const list)
{
	if (list == NULL)
	{
		return NULL;
	}

	// Create a new list
	struct dllist* new_list = init_list();
	while (list->first != NULL)
	{
		// Find the largest node in the original list
		struct dlnode* max_node = find_max_node(list);
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


void insertion_sort_list(struct dllist * const list)
{
	if (list == NULL)
	{
		return;
	}

	// Start at the second node
	struct dlnode *current_node = list->first->next;
	while (current_node != NULL)
	{
		struct dlnode* prior_node = current_node->previous;
		struct dlnode* prior_node_next = current_node;
		// As long as the prior nodes contain larger values than the current,
		// keep moving the current value backward through the list
		while (prior_node != NULL && prior_node->data > prior_node_next->data)
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


void insertion_sort_list_sw(struct dllist * const list)
{
	struct dlnode dummy;
	struct dlnode *b = &dummy;
	b->next = NULL;
	struct dlnode *t;
	struct dlnode *u; 
	struct dlnode *x;
	for (t = list->first; t != NULL; t = u)
	{
		u = t->next;
		for (x = b; x->next != NULL; x = x->next)
		{
			if (x->next->data > t->data)
			{
				break;
			}
		}
		t->next = x->next;
		x->next = t;
	}
	list->first = b->next;
}


struct dlnode* merge_list(struct dlnode *a, struct dlnode *b)
{
	struct dlnode head;
	struct dlnode *c = &head;

	while (a != NULL && b != NULL)
	{
		if (a->data < b->data)
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


struct dlnode* merge_sort_list(struct dlnode *c)
{
	struct dlnode *a;
	struct dlnode *b;

	if (c == NULL || c->next == NULL)
	{
		return c;
	}

	a = c;
	b = c->next;

	while (b != NULL && b->next != NULL)
	{
		c = c->next;
		b = b->next->next;
	}

	b = c->next;
	c->next = NULL;
	return merge_list(merge_sort_list(a), merge_sort_list(b));
}

