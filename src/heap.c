#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

heap_t heap_init(void)
{
    heap_key_t* const key_array = malloc(HEAP_INIT_SIZE * sizeof(heap_key_t));
    if (key_array == NULL) {
        fprintf(stderr, "%s: ERROR: Failed to initialize heap.\n", __func__);
        exit(1);
    }
    return (heap_t){.capacity = HEAP_INIT_SIZE, .size = 0, .keys = key_array};
}

void heap_free(heap_t heap[const static 1])
{
    heap_key_t* const keys = heap->keys;
    if (keys != NULL) {
        free(keys);
    }
    heap->capacity = 0;
    heap->size = 0;
}

size_t heap_get_size(const heap_t heap[const static 1])
{
    return heap->size;
}

bool heap_is_empty(const heap_t heap[const static 1])
{
    return heap->size == 0;
}

void heap_print(const heap_t heap[const static 1])
{
    const size_t size = heap->size;
    if (size == 0) {
        printw("[]\n");
        return;
    }
    heap_key_t* const keys = heap->keys;
    printw("[%d", keys[0].value);
    for (size_t i = 1; i < size; i++) {
        printw(", %d", keys[i].value);
    }
    printw("]\n");
}

static inline size_t heap_get_parent(const size_t idx)
{
    return (idx - 1) / 2;
}

static inline size_t heap_get_left_child(const size_t idx)
{
    return (idx * 2) + 1;
}

static inline size_t heap_get_right_child(const size_t idx)
{
    return (idx * 2) + 2;
}

void heap_send_up(heap_t heap[const static 1], size_t idx)
{
    if ((idx == 0) || (idx >= heap->size)) {
        return;
    }

    size_t i_parent = heap_get_parent(idx);
    heap_key_t* const keys = heap->keys;

    while ((idx > 0) && (keys[i_parent].value > keys[idx].value)) {
        const heap_key_t parent = keys[i_parent];
        keys[i_parent] = keys[idx];
        keys[idx] = parent;
        idx = i_parent;
        i_parent = heap_get_parent(idx);
    }
}

void heap_insert(heap_t heap[const static 1], const heap_key_t key[const static 1])
{
    const size_t i_new = heap->size;

    // First, if necessary, dynamically resize array
    if (i_new >= heap->capacity) {
        const size_t new_capacity = (heap->capacity * 2) + 1;
        heap->keys = realloc(heap->keys, new_capacity * sizeof(heap_key_t));
        if (heap->keys == NULL) {
            fprintf(stderr, "%s: ERROR: Failed to resize the heap.\n", __func__);
            exit(1);
        }
        heap->capacity = new_capacity;
    }

    heap->keys[i_new] = *key;
    heap->size++;
    heap_send_up(heap, i_new);
}

void heap_send_down(heap_t heap[const static 1], const size_t idx)
{
    const size_t size = heap->size;
    if (idx >= size) {
        return;
    }

    const size_t i_left = heap_get_left_child(idx);
    const size_t i_right = heap_get_right_child(idx);

    if (i_left >= size) {
        return;
    }

    heap_key_t* const keys = heap->keys;
    size_t i_next;

    if (((i_right >= size) || (keys[i_left].value < keys[i_right].value)) && (keys[i_left].value < keys[idx].value)) {
        i_next = i_left;
    } else if ((keys[i_right].value < keys[i_left].value) && (keys[i_right].value < keys[idx].value)) {
        i_next = i_right;
    } else {
        return;
    }

    const heap_key_t next = keys[i_next];
    keys[i_next] = keys[idx];
    keys[idx] = next;
    heap_send_down(heap, i_next);
}

void heap_pop(heap_t heap[const static 1])
{
    if (heap->size == 0) {
        return;
    }

    const size_t i_last = heap->size - 1;
    if (i_last == 0) {
        heap->size = 0;
        return;
    }

    heap->size--;

    heap_key_t* const keys = heap->keys;
    const heap_key_t last = keys[i_last];
    keys[i_last] = keys[0];
    keys[0] = last;
    heap_send_down(heap, 0);
}

heap_key_t heap_get_min(const heap_t heap[const static 1])
{
    if (heap->size == 0) {
        //fprintf(stderr, "%s: ERROR: The heap is empty.\n", __func__);
        printw("%s: ERROR: The heap is empty.\n", __func__);
        return (heap_key_t){.value = -1};
    }
    return heap->keys[0];
}

// O(n/2)
heap_key_t heap_get_max(const heap_t heap[const static 1])
{
    const size_t size = heap->size;
    if (size == 0) {
        //fprintf(stderr, "%s: ERROR: The heap is empty.\n", __func__);
        printw("%s: ERROR: The heap is empty.\n", __func__);
        return (heap_key_t){.value = -1};
    }

    size_t i = size / 2;
    heap_key_t* const keys = heap->keys;
    heap_key_t max = keys[i++];
    for (; i < size; i++) {
        if (keys[i].value > max.value) {
            max = keys[i];
        }
    }
    return max;
}

heap_key_t heap_get_idx(const heap_t heap[const static 1], const size_t idx)
{
    if (idx >= heap->size) {
        //fprintf(stderr, "%s: ERROR: Index %zu is out of bounds.\n", __func__, idx);
        printw("%s: ERROR: Index %zu is out of bounds.\n", __func__, idx);
        return (heap_key_t){.value = -1};
    }
    return heap->keys[idx];
}

#if 0
void heapsort()
{

}
#endif

