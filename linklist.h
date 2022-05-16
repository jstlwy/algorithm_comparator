#ifndef LINKLIST_H
#define LINKLIST_H
#include <stdbool.h>

typedef struct doubly_linked_node {
    int data;
    struct doubly_linked_node* previous;
    struct doubly_linked_node* next;
} doubly_linked_node;

typedef struct doubly_linked_list {
    int size;
    doubly_linked_node* first;
    doubly_linked_node* last;
} doubly_linked_list;

doubly_linked_list* init_list(void);
int size_of_list(doubly_linked_list* list);
doubly_linked_list* copy_int_list(doubly_linked_list* original_list);

void print_int_list_curses(doubly_linked_list* list);
bool list_contains_node(doubly_linked_list* list, doubly_linked_node* node);
doubly_linked_node* find_max_node(doubly_linked_list* list);
doubly_linked_node* find_min_node(doubly_linked_list* list);

void insert_at_head(doubly_linked_list* list, doubly_linked_node* new_node);
void insert_at_tail(doubly_linked_list* list, doubly_linked_node* new_node);
void insert_before_index(doubly_linked_list* list, doubly_linked_node* new_node, const int index);
void update_node(doubly_linked_node* node, const int new_data);

void delete_head(doubly_linked_list* list);
void delete_tail(doubly_linked_list* list);
void unlink_node(doubly_linked_list* list, doubly_linked_node* node);
void delete_node(doubly_linked_list* list, doubly_linked_node* node);
void delete_list(doubly_linked_list* list);

#endif
