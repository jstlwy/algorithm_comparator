#include "unionfind.h"
#include <stdlib.h>

WQuickUnion* initWQuickUnionOfSize(int n)
{
	WQuickUnion* newWQU = malloc(sizeof(WQuickUnion));
	int* idArray = malloc(n * sizeof(int));
	int* szArray = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		idArray[i] = i;
		szArray[i] = 1;
	}
	newWQU->id = idArray;
	newWQU->sz = szArray;
	newWQU->count = n;
	return newWQU;
}

int findRootOfNode(WQuickUnion* wqu, int p)
{
	while (p != wqu->id[p])
		p = wqu->id[p];

	return p;
}

bool pairIsConnected(WQuickUnion* wqu, int p, int q)
{
	int i = findRootOfNode(wqu, p);
	int j = findRootOfNode(wqu, q);
	return i == j;
}

void unionNodes(WQuickUnion* wqu, int p, int q)
{
	int i = findRootOfNode(wqu, p);
	int j = findRootOfNode(wqu, q);
	if (i != j) {
		if (wqu->sz[i] < wqu->sz[j]) {
			wqu->id[i] = j;
			wqu->sz[j] += wqu->sz[i];
		}
		else {
			wqu->id[j] = i;
			wqu->sz[i] += wqu->sz[j];
		}
		wqu->count -= 1;
	}
}

void deleteWQuickUnion(WQuickUnion* wqu)
{
	free(wqu->id);
	free(wqu->sz);
	free(wqu);
}

