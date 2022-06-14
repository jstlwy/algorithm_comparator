#include "utils.h"
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

int get_random_num(const int a, const int b)
{
	int low, high;
	if (a < b) {
		low = a;
		high = b;
	} else if (a > b) {
		low = b;
		high = a;
	} else {
		return a;
	}
	int difference = high - low;
	return (rand() % difference) + low;
}


long get_time_diff(struct timespec start, struct timespec stop)
{
	long start_nsec = start.tv_nsec + (start.tv_sec * 1000000000);
	long stop_nsec = stop.tv_nsec + (stop.tv_sec * 1000000000);
	long diff_nsec = stop_nsec - start_nsec;
	return diff_nsec;
}


void wait_for_enter()
{
	printw("Press the enter key to continue.");
	refresh();
	int key_input = 0;
	while (key_input != KEY_ENTER && key_input != 10) {
		key_input = getch();
	}
}

