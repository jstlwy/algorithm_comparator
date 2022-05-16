#ifndef UTILS_H
#define UTILS_H
#include <sys/time.h>

int get_random_num(const int a, const int b);
void print_int_array(int* array, const int array_size);
void print_int_array_curses(int *array, const int array_size);
int* copy_int_array(int* original_array, const int original_array_size);
int time_diff(struct timeval start, struct timeval stop);
void wait_for_enter();

#endif
