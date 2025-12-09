#ifndef WQUNION_H
#define WQUNION_H
#include <stdbool.h>
#include <stddef.h>

// Weighted quick union

typedef struct wqunion_node {
    int id;
    int size;
} WQUNION_NODE;

typedef struct wqunion {
    size_t count;
    WQUNION_NODE* nodes;
} WQUNION;

WQUNION init_wqunion_of_size(const size_t n);
int get_node_root(const WQUNION* wqu, int p);
bool pair_is_connected(const WQUNION* wqu, int p, int q);
void unify_nodes(WQUNION* wqu, int p, int q);
void delete_wqunion(WQUNION* wqu);

#endif
