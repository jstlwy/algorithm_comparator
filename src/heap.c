#include "heap.h"
#include <stdlib.h>

struct max_pqueue* init_max_pqueue_of_size(size_t n)
{
    struct max_pqueue* pq = malloc(sizeof(struct max_pqueue));
    
    // max_pqueue array will be initialized with n slots,
    // n-1 of which can be used to hold keys.
    // First slot will always be an empty sentinel.
    struct key** new_array = malloc((n+1) * sizeof(struct key));
    for (size_t i = 0; i <= n; i++) {
        new_array[i] = NULL;
    }
    pq->keys = new_array;
    pq->num_items = 0;
    pq->array_size = n;
    return pq;
}

void insert_into_pqueue(struct max_pqueue* pq, struct key* key)
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

struct key* get_max_in_pqueue(struct max_pqueue* pq)
{
    return pq->keys[1];
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

bool is_empty_pqueue(struct max_pqueue* pq)
{
    return (pq->num_items == 0);
}

int size_of_pqueue(struct max_pqueue* pq)
{
    return pq->num_items;
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

