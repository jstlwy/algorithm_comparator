#ifndef UTILS_H
#define UTILS_H
#include <sys/time.h>

int get_random_num(const int a, const int b);
long get_time_diff(struct timespec start, struct timespec stop);
void wait_for_enter();

#endif
