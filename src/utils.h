#ifndef UTILS_H
#define UTILS_H
#include <sys/time.h>

int get_random_num(int const a, int const b);
unsigned long get_time_diff(struct timespec start, struct timespec stop);
void wait_for_enter();

#endif
