#ifndef LISTSORT_H
#define LISTSORT_H
#include "dllist.h"

// Quadratic
void dllist_selection_sort(dllist_t list[const static 1]);
dllist_t dllist_selection_sort_sw(dllist_t list[const static 1]);
void dllist_insertion_sort(dllist_t list[const static 1]);
void dllist_insertion_sort_sw(dllist_t list[const static 1]);

// Linearithmic
dlnode_t* dllist_merge(dlnode_t* a, dlnode_t* b);
dlnode_t* dllist_merge_sort(dlnode_t* c);

#endif
