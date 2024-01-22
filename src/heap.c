#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

heap_t heap_init(void)
{
    heap_key_t* const key_array = malloc(HEAP_INIT_SIZE * sizeof(heap_key_t));
    if (key_array == NULL) {
        fprintf(stderr, "%s: ERROR: Failed to initialize heap.\n", __func__);
        exit(1);
    }
    for (size_t i = 0; i < HEAP_INIT_SIZE; i++) {
        key_array[i] = NULL;
    }
    return (heap_t) {.capacity = HEAP_INIT_SIZE, .size = 0, .keys = key_array};
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

void heap_insert(heap_t heap[const static 1], const heap_key_t key[const static 1])
{
    int n = pq->num_items + 1;

    // If necessary, dynamically resize array
    if (pq->array_size == pq->num_items) {
        size_t const new_array_size = (pq->array_size * 2) + 1;
        pq->array_size = new_array_size;
        struct key** new_array = malloc(new_array_size * sizeof(struct key));
        new_array[0] = NULL;
        for (size_t i = 1; i <= pq->array_size; i++) {
            new_array[i] = pq->keys[i];
        }
        // Make sure to free the old array
        int* old_array = pq->keys;
        pq->keys = new_array;
        free(old_array);
    }

    pq->keys[n] = key;
    swim_up_pqueue(pq->keys, n);
    pq->num_items = n;
}

heap_key_t* heap_get_min(heap_t heap[const static 1])
{
    if (heap->size == 0) {
        return NULL;
    }
    return heap->keys[0];
}

heap_key_t* heap_get_max(heap_t heap[const static 1])
{
    if (heap->size == 0) {
        return NULL;
    }

}

heap_key_t* heap_get_idx(heap_t heap[const static 1], const size_t idx)
{
    if (idx >= heap->size) {
        return NULL;
    }
    return heap->keys[idx];
}

void insert_into_pqueue(struct max_pqueue* pq, struct key* key)
{
    
}

struct key* get_max_in_pqueue(struct max_pqueue* pq)
{
    
}

void delete_max_in_pqueue(struct max_pqueue* pq)
{
    struct key* max = pq->keys[1];
    free(max);
    pq->keys[1] = pq->keys[pq->num_items];
    pq->num_items -= 1;
    sink_down_pqueue(pq->keys, pq->num_items, 1);
    // Shrink the array if necessary to save memory
    if (pq->num_items <= (pq->array_size / 4)) {
        size_t const new_array_size = (pq->array_size / 2) + 1;
        pq->array_size = new_array_size;
        int* new_array = malloc(new_array_size * sizeof(struct key));
        for (size_t i = 1; i <= pq->array_size; i++) {
            new_array[i] = pq->keys[i];
        }
        // Free the old array
        int* old_array = pq->keys;
        pq->keys = new_array;
        free(old_array);        
    }
}

void swim_up_pqueue(struct key** array, size_t k)
{
    while ((k > 1) && (array[k/2]->value < array[k]->value)) {
        struct key* temp = array[k/2];
        array[k/2] = array[k];
        array[k] = temp;
        k = k/2;
    }
}

void sink_down_pqueue(struct key** array, size_t size, size_t k)
{
    while (2*k <= size) {
        size_t j = 2 * k;
        if ((j < size) && (array[j]->value < array[j+1]->value)) {
            j++;
        }
        if (array[k]->value >= array[j]->value) {
            break;
        }
        struct key* temp = array[k];
        array[k] = array[j];
        array[j] = temp;
        k = j;
    }
}

void heapsort(size_t n, struct key* array[n])
{
    for (size_t k = n / 2; k >= 1; k--)
    {

    }

    // TODO
    /*
    while (n > 1)
    {

    }
    */
}
