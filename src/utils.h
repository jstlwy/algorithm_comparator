#ifndef UTILS_H
#define UTILS_H
#include <sys/time.h>

int get_random_num(const int a, const int b);
unsigned long get_time_diff(const struct timespec start, const struct timespec stop);
void wait_for_enter(void);

#endif
