#include "utils.h"
#include <ncurses.h>
#ifdef __APPLE__
#include <stdlib.h>
#elif defined(__linux__)
#include <bsd/stdlib.h>
#endif
#include <assert.h>

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

#ifndef __APPLE__
int get_time_diff(
    const struct timespec* const start,
    const struct timespec* const stop,
    struct timespec* const elapsed
) {
    if ((start == NULL) || (stop == NULL) || (elapsed == NULL)) {
        fprintf(stderr, "%s: ERROR: Null pointer.\n", __func__);
        return -1;
    }
    if ((start == stop) || (start == elapsed) || (stop == elapsed)) {
        fprintf(stderr, "%s: ERROR: Pointers must be unique.\n", __func__);
        return -1;
    }
    if ((start->tv_sec > stop->tv_sec) || ((start->tv_sec == stop->tv_sec) && (start->tv_nsec > stop->tv_nsec))) {
        fprintf(stderr, "%s: ERROR: Start time is later than stop time.\n", __func__);
        return -1;
    }

    elapsed->tv_sec = stop->tv_sec - start->tv_sec;
    elapsed->tv_nsec = stop->tv_nsec - start->tv_nsec;

    if (elapsed->tv_sec < 0) {
        assert(elapsed->tv_nsec >= NS_PER_S);
        elapsed->tv_nsec -= NS_PER_S;
        elapsed->tv_sec += 1;
    } else if (elapsed->tv_nsec < 0) {
        assert(elapsed->tv_sec >= 1);
        elapsed->tv_sec -= 1;
        elapsed->tv_nsec += NS_PER_S;
    }

    assert(elapsed->tv_sec >= 0);
    assert(elapsed->tv_nsec >= 0);
    return 0;
}
#endif

void wait_for_enter(void)
{
    addstr("Please press Enter to continue.");
    refresh();
    int key_input = 0;
    while ((key_input != KEY_ENTER) && (key_input != 10)) {
        key_input = getch();
    }
}
