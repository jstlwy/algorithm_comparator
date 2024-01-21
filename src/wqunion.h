#ifndef WQUNION_H
#define WQUNION_H
#include <stdbool.h>
#include <stddef.h>

// Weighted quick union

struct wqunion {
    int* id;
    int* sz;
    size_t count;
};

struct wqunion* init_wqunion_of_size(const size_t n);
int get_node_root(struct wqunion* wqu, int p);
bool pair_is_connected(struct wqunion* wqu, int p, int q);
void unify_nodes(struct wqunion* wqu, int p, int q);
void delete_wqunion(struct wqunion* wqu);

#endif
