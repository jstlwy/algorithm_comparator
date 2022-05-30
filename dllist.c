#include "dllist.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

struct dllist* init_list(void)
{
	struct dllist* new_list = malloc(sizeof(struct dllist));
	new_list->size = 0;
	new_list->first = NULL;
	new_list->last = NULL;
	return new_list;
}


int get_list_size(struct dllist* list)
{
	if (list == NULL)
		return 0;

	return list->size;
}


struct dllist* copy_int_list(struct dllist* original_list)
{
	struct dllist* new_list = init_list();

	if (original_list == NULL)
		return new_list;

	struct dlnode* current_node = original_list->first;
	while (current_node != NULL) {
		struct dlnode* new_node = malloc(sizeof(struct dlnode));
		new_node->data = current_node->data;
		insert_at_tail(new_list, new_node);
		current_node = current_node->next;
	}

	return new_list;
}


void print_int_list_curses(struct dllist* list)
{
	if (list == NULL)
		return;

	struct dlnode* current_node = list->first;
	while (current_node != NULL) {
		printw("%d ", current_node->data);
		current_node = current_node->next;
	}
}


bool list_contains_node(struct dllist* list, struct dlnode* node)
{
	if (list == NULL || node == NULL)
		return false;

	struct dlnode* current_node = list->first;
	while (current_node != NULL) {
		if (node == current_node)
			return true;
		current_node = current_node->next;
	}

	return false;
}


struct dlnode* find_max_node(struct dllist* list)
{
	if (list == NULL)
		return NULL;

	struct dlnode* max_node = list->first;
	struct dlnode* current_node = max_node->next;
	while (current_node != NULL) {
		if (current_node->data > max_node->data)
			max_node = current_node;
		current_node = current_node->next;
	}

	return max_node;
}


struct dlnode* find_min_node(struct dllist* list)
{
	if (list == NULL)
		return NULL;

	struct dlnode* min_node = list->first;
	struct dlnode* current_node = min_node->next;
	while (current_node != NULL) {
		if (current_node->data < min_node->data)
			min_node = current_node;
		current_node = current_node->next;
	}

	return min_node;
}


void insert_at_head(struct dllist* list, struct dlnode* new_node)
{
	if (list == NULL)
		return;

	new_node->previous = NULL;

	if (list->first == NULL) {
		new_node->next = NULL;
		list->last = new_node;
	}
	else {
		struct dlnode* old_first_node = list->first;
		new_node->next = old_first_node;
		old_first_node->previous = new_node;   
	}

	list->first = new_node;
	list->size += 1;
}


void insert_at_tail(struct dllist* list, struct dlnode* new_node)
{
	if (list == NULL)
		return;

	new_node->next = NULL;

	if (list->last == NULL) {
		list->first = new_node;
		new_node->previous = NULL;
	}
	else {
		struct dlnode* old_last_node = list->last;
		old_last_node->next = new_node;
		new_node->previous = old_last_node;
	}

	list->last = new_node;
	list->size += 1;
}


void insert_before_index(struct dllist* list, struct dlnode* new_node, const int index)
{
	if (list == NULL || new_node == NULL)
		return;

	struct dlnode* current_node = list->first;
	int current_index = 0;
	while (current_node != NULL && current_index != index) {
		current_node = current_node->next;
		current_index++;
	}

	// TODO
}


void update_node(struct dlnode* node, const int new_data)
{
	if (node == NULL)
		return;

	node->data = new_data;
}


void delete_head(struct dllist* list)
{
	if (list == NULL)
		return;

	struct dlnode* old_first_node = list->first;
	if (old_first_node != NULL) {
		if (old_first_node == list->last) {
			list->first = NULL;
			list->last = NULL;
		}
		else {
			struct dlnode* new_first_node = old_first_node->next;
			new_first_node->previous = NULL;
			list->first = new_first_node;
		}
		free(old_first_node);
		list->size -= 1;
	}
}


void delete_tail(struct dllist* list)
{
	if (list == NULL)
		return;

	struct dlnode* old_last_node = list->last;
	if (old_last_node != NULL) {
		if (old_last_node == list->first) {
			list->first = NULL;
			list->last = NULL;
		}
		else {
			struct dlnode* new_last_node = old_last_node->previous;
			new_last_node->next = NULL;
			list->last = new_last_node;
		}
		free(old_last_node);
		list->size -= 1;
	}
}


void unlink_node(struct dllist* list, struct dlnode* node)
{
	if (list == NULL || node == NULL)
		return;

	bool previous_node_is_null = (node->previous == NULL);
	bool next_node_is_null = (node->next == NULL);

	if (previous_node_is_null && next_node_is_null) {
		// The node doesn't link to anything.
		list->first = NULL;
		list->last = NULL;
	}
	else if (next_node_is_null) {
		// The node only links to a preceding node.
		// It must be the tail of the list.
		list->last = node->previous;
		node->previous->next = NULL;
	}
	else if (previous_node_is_null) {
		// The node only links to a succeeding node.
		// It must be the head of the list.
		list->first = node->next;
		node->next->previous = NULL;
	}
	else {
		// The node is between two other nodes.
		node->previous->next = node->next;
		node->next->previous = node->previous;
	}

	list->size -= 1;
}


void delete_node(struct dllist* list, struct dlnode* node)
{
	if (list != NULL && node != NULL) {
		unlink_node(list, node);
		free(node);
	}
}


void delete_list(struct dllist* list)
{
	if (list == NULL)
		return;

	struct dlnode* current_node = list->first;
	while (current_node != NULL) {
		struct dlnode* next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}

	free(list);
}

