#ifndef HEAP_H
#define HEAP_H
#include <stddef.h>
#include <stdbool.h>

// Priority queue
#define HEAP_INIT_SIZE (15)

typedef struct heap_key heap_key_t;
struct heap_key {
    int value;
};

typedef struct heap heap_t;
struct heap {
    size_t capacity;
    size_t size;
    heap_key_t** keys;
};

heap_t heap_init(void);
void heap_free(heap_t heap[const static 1]);

size_t heap_get_size(const heap_t heap[const static 1]);
bool heap_is_empty(const heap_t heap[const static 1]);

void heap_insert(heap_t heap[const static 1], const heap_key_t key[const static 1]);

void heap_delete(heap_t heap[const static 1]);
void heap_delete_min(heap_t heap[const static 1]);
void heap_delete_max(heap_t heap[const static 1]);

heap_key_t* heap_get_min(heap_t heap[const static 1]);
heap_key_t* heap_get_max(heap_t heap[const static 1]);
heap_key_t* heap_get_idx(heap_t heap[const static 1], const size_t idx);

void heapsort(size_t n, struct key* array[n]);

#endif
