#ifndef UTILS_H
#define UTILS_H
#include <time.h>

#define NS_PER_S  1000000000
#define NS_PER_MS 1000000
#define NS_PER_US 1000

int get_random_num(const int a, const int b);

#ifndef __APPLE__
int get_time_diff(
    const struct timespec* const start,
    const struct timespec* const stop,
    struct timespec* const elapsed
);
#endif

void wait_for_enter(void);

#endif
