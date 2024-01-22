#include "dllist.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ncurses.h>

dllist_t dllist_init(void)
{
    return (dllist_t) {.size = 0, .first = NULL, .last = NULL};
}

void dllist_destroy(dllist_t list[const static 1])
{
    dlnode_t* current = list->first;
    while (current != NULL) {
        dlnode_t* const next = current->next;
        free(current);
        current = next;
    }
    list->size = 0;
}

size_t dllist_size(const dllist_t list[const static 1])
{
    return list->size;
}

void dllist_print_curses(const dllist_t list[const static 1])
{
    for (const dlnode_t* node = list->first; node != NULL; node = node->next) {
        printw("%d ", node->data);
    }
}

bool dllist_is_sorted(const dllist_t list[const static 1])
{
    const dlnode_t* current = list->first;
    while (current != NULL) {
        const dlnode_t* const next = current->next;
        if ((next != NULL) && (current->data > next->data)) {
            return false;
        }
        current = next;
    }
    return true;
}

bool dllist_contains_node(const dllist_t list[const static 1], const dlnode_t target[const static 1])
{
    for (const dlnode_t* current = list->first; current != NULL; current = current->next) {
        if (current == target) {
            return true;
        }
    }
    return false;
}

dlnode_t* dllist_get_max_node(const dllist_t list[const static 1])
{
    dlnode_t* max = list->first;
    for (dlnode_t* current = max->next; current != NULL; current = current->next) {
        if (current->data > max->data) {
            max = current;
        }
    }
    return max;
}


dlnode_t* dllist_get_min_node(const dllist_t list[const static 1])
{
    dlnode_t* min = list->first;
    for (dlnode_t* current = min->next; current != NULL; current = current->next) {
        if (current->data < min->data) {
            min = current;
        }
    }
    return min;
}

void dllist_append(dllist_t list[const static 1], dlnode_t new_node[const static 1])
{
    new_node->next = NULL;

    dlnode_t* const old_last = list->last;
    if (old_last == NULL) {
        list->first = new_node;
        new_node->previous = NULL;
    } else {
        old_last->next = new_node;
        new_node->previous = old_last;
    }

    list->last = new_node;
    list->size += 1;
}

void dllist_prepend(dllist_t list[const static 1], dlnode_t new_node[const static 1])
{
    new_node->previous = NULL;

    dlnode_t* const old_first = list->first;
    if (old_first == NULL) {
        new_node->next = NULL;
        list->last = new_node;
    } else {
        new_node->next = old_first;
        old_first->previous = new_node;   
    }

    list->first = new_node;
    list->size += 1;
}

#if 0
void dllist_insert_before_index(
    dllist_t list[const static 1],
    dlnode_t new_node[const static 1],
    const size_t index)
{
    struct dlnode* current_node = list->first;
    int current_index = 0;
    while (current_node != NULL && current_index != index) {
        current_node = current_node->next;
        current_index++;
    }

    // TODO
}
#endif

dllist_t dllist_create_copy(const dllist_t src_list[const static 1])
{
    dllist_t new_list = {.first = NULL, .last = NULL, .size = 0};
    for (dlnode_t* current = src_list->first; current != NULL; current = current->next) {
        dlnode_t* const new_node = malloc(sizeof(dlnode_t));
        if (new_node == NULL) {
            fprintf(stderr, "%s: ERROR: malloc failed.\n", __func__);
            exit(1);
        }
        memcpy(new_node, current, sizeof(dlnode_t));
        dllist_append(&new_list, new_node);
    }
    return new_list;
}

void dllist_delete_head(dllist_t list[const static 1])
{
    dlnode_t* const old_first = list->first;
    if (old_first == NULL) {
        return;
    }
    assert(list->size > 0);
    if (old_first == list->last) {
        list->first = NULL;
        list->last = NULL;
    } else {
        dlnode_t* const new_first = old_first->next;
        new_first->previous = NULL;
        list->first = new_first;
    }
    free(old_first);
    list->size -= 1;
}

void dllist_delete_tail(dllist_t list[const static 1])
{
    dlnode_t* const old_last = list->last;
    if (old_last == NULL) {
        return;
    }
    assert(list->size > 0);
    if (old_last == list->first) {
        list->first = NULL;
        list->last = NULL;
    } else {
        dlnode_t* const new_last = old_last->previous;
        new_last->next = NULL;
        list->last = new_last;
    }
    free(old_last);
    list->size -= 1;
}

void dllist_unlink_node(dllist_t list[const static 1], dlnode_t* const node)
{
    if (node == NULL) {
        return;
    }

    bool previous_node_is_null = (node->previous == NULL);
    bool next_node_is_null = (node->next == NULL);

    if (previous_node_is_null && next_node_is_null) {
        // The node doesn't link to anything.
        list->first = NULL;
        list->last = NULL;
    } else if (next_node_is_null) {
        // The node only links to a preceding node.
        // It must be the tail of the list.
        list->last = node->previous;
        node->previous->next = NULL;
    } else if (previous_node_is_null) {
        // The node only links to a succeeding node.
        // It must be the head of the list.
        list->first = node->next;
        node->next->previous = NULL;
    } else {
        // The node is between two other nodes.
        node->previous->next = node->next;
        node->next->previous = node->previous;
    }

    list->size -= 1;
}

void dllist_delete_node(dllist_t list[const static 1], dlnode_t* const node)
{
    if (node != NULL) {
        dllist_unlink_node(list, node);
        free(node);
    }
}
