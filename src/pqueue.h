#ifndef PQUEUE_H
#define PQUEUE_H
#include <stdbool.h>

// Priority queue

struct key {
    int value;
};

struct max_pqueue {
    size_t array_size;
    size_t num_items;
    struct key** keys;
};

struct max_pqueue* init_max_pqueue_of_size(size_t n);
void insert_into_pqueue(struct max_pqueue* pq, struct key* k);
struct key* get_max_in_pqueue(struct max_pqueue* pq);
void delete_max_in_pqueue(struct max_pqueue* pq);
void swim_up_pqueue(struct key** array, size_t k);
void sink_down_pqueue(struct key** array, size_t size, size_t k);
bool is_empty_pqueue(struct max_pqueue* pq);
int size_of_pqueue(struct max_pqueue* pq);
void heapsort(size_t n, struct key* array[n]);

#endif
