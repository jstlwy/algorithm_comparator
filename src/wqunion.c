#include "wqunion.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

WQUNION init_wqunion_of_size(const size_t n)
{
    assert(n <= INT_MAX);

    WQUNION_NODE* node_array = malloc(n * sizeof(WQUNION_NODE));
    if (node_array == NULL) {
        fprintf(stderr, "%s: ERROR: malloc failed.\n", __func__);
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < n; i++) {
        node_array[i].id = (int)i;
        node_array[i].size = 1;
    }

    return (WQUNION){.nodes = node_array, .count = n};
}

int get_node_root(const WQUNION* wqu, int p)
{
    while (p != wqu->nodes[p].id) {
        p = wqu->nodes[p].id;
    }
    return p;
}

bool pair_is_connected(const WQUNION* wqu, int p, int q)
{
    const int i = get_node_root(wqu, p);
    const int j = get_node_root(wqu, q);
    return i == j;
}

void unify_nodes(WQUNION* wqu, int p, int q)
{
    const int i = get_node_root(wqu, p);
    const int j = get_node_root(wqu, q);
    if (i != j) {
        if (wqu->nodes[i].size < wqu->nodes[j].size) {
            wqu->nodes[i].id = j;
            wqu->nodes[j].size += wqu->nodes[i].size;
        } else {
            wqu->nodes[j].id = i;
            wqu->nodes[i].size += wqu->nodes[j].size;
        }
        assert(wqu->count > 0);
        wqu->count -= 1;
    }
}

void delete_wqunion(WQUNION* wqu)
{
    if ((wqu != NULL) && (wqu->nodes != NULL)) {
        free(wqu->nodes);
        wqu->nodes = NULL;
        wqu->count = 0;
    }
}

