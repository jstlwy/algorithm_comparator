#include "wqunion.h"
#include <stdlib.h>

struct wqunion* init_wqunion_of_size(const size_t n)
{
    struct wqunion* new_wqu = malloc(sizeof(struct wqunion));
    int* id_array = malloc(n * sizeof(int));
    int* sz_array = malloc(n * sizeof(int));
    for (size_t i = 0; i < n; i++) {
        id_array[i] = i;
        sz_array[i] = 1;
    }
    new_wqu->id = id_array;
    new_wqu->sz = sz_array;
    new_wqu->count = n;
    return new_wqu;
}

int get_node_root(struct wqunion* wqu, int p)
{
    while (p != wqu->id[p]) {
        p = wqu->id[p];
    }
    return p;
}

bool pair_is_connected(struct wqunion* wqu, int p, int q)
{
    int i = get_node_root(wqu, p);
    int j = get_node_root(wqu, q);
    return i == j;
}

void unify_nodes(struct wqunion* wqu, int p, int q)
{
    int i = get_node_root(wqu, p);
    int j = get_node_root(wqu, q);
    if (i != j) {
        if (wqu->sz[i] < wqu->sz[j]) {
            wqu->id[i] = j;
            wqu->sz[j] += wqu->sz[i];
        } else {
            wqu->id[j] = i;
            wqu->sz[i] += wqu->sz[j];
        }
        wqu->count -= 1;
    }
}

void delete_wqunion(struct wqunion* wqu)
{
    free(wqu->id);
    free(wqu->sz);
    free(wqu);
}

