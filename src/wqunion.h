#ifndef WQUNION_H
#define WQUNION_H
#include <stdbool.h>

// Weighted quick union

struct wqunion {
    int *id;
    int *sz;
    int count;
};

struct wqunion* init_wqunion_of_size(const int n);
int get_node_root(struct wqunion *wqu, int p);
bool pair_is_connected(struct wqunion *wqu, int p, int q);
void unify_nodes(struct wqunion *wqu, int p, int q);
void delete_wqunion(struct wqunion *wqu);

#endif
