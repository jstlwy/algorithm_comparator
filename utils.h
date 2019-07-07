#ifndef UTILS_H
#define UTILS_H
#include <sys/time.h>

int randomNum(int a, int b);

void printIntArray(int*, int);
int* copyIntArray(int* oldArray, int arraySize);
int timeDiff(struct timeval start, struct timeval stop);

#endif