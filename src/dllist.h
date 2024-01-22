#ifndef DLLIST_H
#define DLLIST_H
#include <stddef.h>
#include <stdbool.h>

// Doubly-linked list

typedef struct dlnode dlnode_t;
struct dlnode {
    int data;
    struct dlnode* previous;
    struct dlnode* next;
};

typedef struct dllist dllist_t;
struct dllist {
    size_t size;
    dlnode_t* first;
    dlnode_t* last;
};

dllist_t dllist_init(void);
void dllist_destroy(dllist_t list[const static 1]);

size_t dllist_size(const dllist_t list[const static 1]);
void dllist_print_curses(const dllist_t list[const static 1]);

bool dllist_is_sorted(const dllist_t list[const static 1]);
bool dllist_contains_node(const dllist_t list[const static 1], const dlnode_t target[const static 1]);
dlnode_t* dllist_get_max_node(const dllist_t list[const static 1]);
dlnode_t* dllist_get_min_node(const dllist_t list[const static 1]);

void dllist_append(dllist_t list[const static 1], dlnode_t new_node[const static 1]);
void dllist_prepend(dllist_t list[const static 1], dlnode_t new_node[const static 1]);
#if 0
void dllist_insert_before_idx(
    dllist_t list[const static 1],
    dlnode_t new_node[const static 1],
    const size_t index);
#endif

dllist_t dllist_create_copy(const dllist_t src_list[const static 1]);

void dllist_delete_head(dllist_t list[const static 1]);
void dllist_delete_tail(dllist_t list[const static 1]);

void dllist_unlink_node(dllist_t list[const static 1], dlnode_t* const node);
void dllist_delete_node(dllist_t list[const static 1], dlnode_t* const node);

#endif
