#include "listsort.h"
#include <stdlib.h>

void dllist_selection_sort(dllist_t list[const static 1])
{
    dlnode_t* current_node = list->first;
    while (current_node != NULL) {
        // Start by assuming the current node has the smallest value
        dlnode_t* min_node = current_node;
        int min_value = current_node->data;
        // Now look at every node after the current node.
        dlnode_t* next_node = current_node->next;
        while (next_node != NULL) {
            // Check the value of each subsequent node.
            // Keep updating the minimum node/value
            // as smaller values are discovered.
            int next_node_value = next_node->data;
            if (next_node_value < min_value) {
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

dllist_t dllist_selection_sort_sw(dllist_t list[const static 1])
{
    // Create a new list
    dllist_t new_list = dllist_init();
    while (list->first != NULL) {
        // Find the largest node in the original list
        dlnode_t* const max_node = dllist_get_max_node(list);
        // Remove it from the original list
        dllist_unlink_node(list, max_node);
        // Put it at the head of the new list.
        // Notice that each time this is done,
        // the head will be smaller.
        dllist_prepend(&new_list, max_node);
    }
    // Destroy the original list
    dllist_destroy(list);
    // Return the new list in place of the original list
    return new_list;
}

void dllist_insertion_sort(dllist_t list[const static 1])
{
    // Start at the second node
    dlnode_t* current_node = list->first->next;
    while (current_node != NULL) {
        dlnode_t* prior_node = current_node->previous;
        dlnode_t* prior_node_next = current_node;
        // As long as the prior nodes contain larger values than the current,
        // keep moving the current value backward through the list
        while ((prior_node != NULL) && (prior_node->data > prior_node_next->data)) {
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

void dllist_insertion_sort_sw(dllist_t list[const static 1])
{
    dlnode_t dummy;
    dlnode_t* b = &dummy;
    b->next = NULL;
    dlnode_t* t;
    dlnode_t* u; 
    dlnode_t* x;
    for (t = list->first; t != NULL; t = u) {
        u = t->next;
        for (x = b; x->next != NULL; x = x->next) {
            if (x->next->data > t->data) {
                break;
            }
        }
        t->next = x->next;
        x->next = t;
    }
    list->first = b->next;
}

dlnode_t* dllist_merge(dlnode_t* a, dlnode_t* b)
{
    dlnode_t head;
    dlnode_t* c = &head;

    while ((a != NULL) && (b != NULL)) {
        if (a->data < b->data) {
            c->next = a;
            c = a;
            a = a->next;
        } else {
            c->next = b;
            c = b;
            b = b->next;
        }
    }

    c->next = (a == NULL) ? b : a;
    return head.next;
}

dlnode_t* dllist_merge_sort(dlnode_t* c)
{
    dlnode_t* a;
    dlnode_t* b;

    if ((c == NULL) || (c->next == NULL)) {
        return c;
    }

    a = c;
    b = c->next;

    while ((b != NULL) && (b->next != NULL)) {
        c = c->next;
        b = b->next->next;
    }

    b = c->next;
    c->next = NULL;
    return dllist_merge(dllist_merge_sort(a), dllist_merge_sort(b));
}

