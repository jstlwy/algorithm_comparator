#ifndef DLLIST_H
#define DLLIST_H
#include <stdbool.h>

struct dlnode {
	int data;
	struct dlnode *previous;
	struct dlnode *next;
};

struct dllist {
	int size;
	struct dlnode *first;
	struct dlnode *last;
};

struct dllist* init_list(void);
int get_list_size(struct dllist *list);
struct dllist* copy_int_list(struct dllist *original_list);

void print_int_list_curses(struct dllist *list);
bool list_contains_node(struct dllist *list, struct dlnode *node);
struct dlnode* find_max_node(struct dllist *list);
struct dlnode* find_min_node(struct dllist *list);

void insert_at_head(struct dllist *list, struct dlnode *new_node);
void insert_at_tail(struct dllist *list, struct dlnode *new_node);
void insert_before_index(struct dllist *list, struct dlnode *new_node, const int index);
void update_node(struct dlnode *node, const int new_data);

void delete_head(struct dllist *list);
void delete_tail(struct dllist *list);
void unlink_node(struct dllist *list, struct dlnode *node);
void delete_node(struct dllist *list, struct dlnode *node);
void delete_list(struct dllist *list);

#endif
