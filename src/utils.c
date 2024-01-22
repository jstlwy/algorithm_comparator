#include "utils.h"
#include <ncurses.h>
#include <stdlib.h>
#ifdef __linux__
#include <bsd/stdlib.h>
#endif
#include <time.h>

int get_random_num(const int a, const int b)
{
    if (a == b) {
        return a;
    }

    if (a > b) {
        return b + arc4random_uniform(a + 1);
    }

    return a + arc4random_uniform(b + 1);
}

#define NS_PER_S (1000000000L)

unsigned long get_time_diff(const struct timespec start, const struct timespec stop)
{
    const unsigned long start_nsec = start.tv_nsec + (start.tv_sec * NS_PER_S);
    const unsigned long stop_nsec = stop.tv_nsec + (stop.tv_sec * NS_PER_S);
    return stop_nsec - start_nsec;
}

void wait_for_enter(void)
{
    printw("Press the enter key to continue.");
    refresh();
    int key_input = 0;
    while ((key_input != KEY_ENTER) && (key_input != 10)) {
        key_input = getch();
    }
}
