#ifndef PQUEUE_H
#define PQUEUE_H
#include <stdbool.h>

struct key {
    int value;
};

struct max_pqueue {
    int array_size;
    int num_items;
    key** keys;
};

struct max_pqueue* init_max_pqueue_of_size(int size);
void insert_into_pqueue(struct max_pqueue* pq, key* k);
key* get_max_in_pqueue(struct max_pqueue* pq);
void delete_max_in_pqueue(struct max_pqueue* pq);
void swim_up_pqueue(key* array, int k);
void sink_down_pqueue(key* array, int size, int k);
bool is_empty_pqueue(struct max_pqueue* pq);
int size_of_pqueue(struct max_pqueue* pq);
void heapsort(key* array, int size);

#endif
