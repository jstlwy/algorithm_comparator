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


int get_time_diff(struct timeval start, struct timeval stop)
{
	int start_usec = start.tv_usec + (start.tv_sec * 1000000);
	int stop_usec = stop.tv_usec + (stop.tv_sec * 1000000); 
	int diff = stop_usec - start_usec;
	return diff;
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

