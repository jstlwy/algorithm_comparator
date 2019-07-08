#ifndef UNIONFIND_H
#define UNIONFIND_H
#include <stdbool.h>

typedef struct WQuickUnion {
    int* id;
    int* sz;
    int count;
} WQuickUnion;

WQuickUnion* initWQuickUnionOfSize(int n);
int findRootOfNode(WQuickUnion* wqu, int p);
bool pairIsConnected(WQuickUnion* wqu, int p, int q);
void unionNodes(WQuickUnion* wqu, int p, int q);
void deleteWQuickUnion(WQuickUnion* wqu);

#endif