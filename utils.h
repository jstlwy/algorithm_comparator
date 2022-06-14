#ifndef UTILS_H
#define UTILS_H
#include <sys/time.h>

int get_random_num(const int a, const int b);
int get_time_diff(struct timeval start, struct timeval stop);
void wait_for_enter();

#endif
