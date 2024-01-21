#ifndef DLLIST_H
#define DLLIST_H
#include <stdbool.h>

// Doubly-linked list

struct dlnode {
    int data;
    struct dlnode* previous;
    struct dlnode* next;
};

struct dllist {
    int size;
    struct dlnode* first;
    struct dlnode* last;
};

struct dllist* init_list(void);
int get_list_size(struct dllist* const list);
struct dllist* copy_int_list(struct dllist* const original_list);

void print_int_list_curses(struct dllist* const list);
bool list_contains_node(struct dllist* const list, struct dlnode* const node);
bool list_is_sorted(struct dllist* const list);
struct dlnode* find_max_node(struct dllist* const list);
struct dlnode* find_min_node(struct dllist* const list);

void insert_at_head(struct dllist* const list, struct dlnode* const new_node);
void insert_at_tail(struct dllist* const list, struct dlnode* const new_node);
void insert_before_index(
    struct dllist* const list,
    struct dlnode* const new_node,
    const int index);
void update_node(struct dlnode* const node, const int new_data);

void delete_head(struct dllist* const list);
void delete_tail(struct dllist* const list);
void unlink_node(struct dllist* const list, struct dlnode* const node);
void delete_node(struct dllist* const list, struct dlnode* const node);
void delete_list(struct dllist* const list);

#endif
