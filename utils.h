#ifndef UTILS_H
#define UTILS_H
#include <sys/time.h>

int randomNum(int a, int b);
void printIntArray(int* array, int arraySize);
void printIntArrayCurses(int *array, int arraySize);
int* copyIntArray(int* oldArray, int arraySize);
int timeDiff(struct timeval start, struct timeval stop);
void waitForEnter();

#endif