#ifndef LISTSORT_H
#define LISTSORT_H
#include "linklist.h"

// Quadratic
void selection_sort_list(doubly_linked_list* list);
doubly_linked_list* selection_sort_list_sw(doubly_linked_list* list);
void insertion_sort_list(doubly_linked_list* list);
void insertion_sort_list_sw(doubly_linked_list* list);

// Alternate directions in passes through the list?
void shellsort_list(doubly_linked_list* list);

// Linearithmic
doubly_linked_node* merge_list(doubly_linked_node* a, doubly_linked_node *b);
doubly_linked_node* merge_sort_list(doubly_linked_node* c);

#endif
