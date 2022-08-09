#ifndef LISTSORT_H
#define LISTSORT_H
#include "dllist.h"

// Quadratic
void selection_sort_list(struct dllist * const list);
struct dllist* selection_sort_list_sw(struct dllist * const list);
void insertion_sort_list(struct dllist * const list);
void insertion_sort_list_sw(struct dllist * const list);

// Linearithmic
struct dlnode* merge_list(struct dlnode *a, struct dlnode *b);
struct dlnode* merge_sort_list(struct dlnode *c);

#endif
