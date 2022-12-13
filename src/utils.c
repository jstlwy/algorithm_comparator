#include "utils.h"
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

int get_random_num(int const a, int const b)
{
	int low;
	int high;
	if (a < b)
	{
		low = a;
		high = b;
	}
	else if (a > b)
	{
		low = b;
		high = a;
	}
	else
	{
		return a;
	}
	int const difference = high - low;
	return (rand() % difference) + low;
}


unsigned long const ns_per_s = 1000000000;
unsigned long get_time_diff(struct timespec start, struct timespec stop)
{
	unsigned long const start_nsec = start.tv_nsec + (start.tv_sec * ns_per_s);
	unsigned long const stop_nsec = stop.tv_nsec + (stop.tv_sec * ns_per_s);
	return stop_nsec - start_nsec;
}


void wait_for_enter()
{
	printw("Press the enter key to continue.");
	refresh();
	int key_input = 0;
	while (key_input != KEY_ENTER && key_input != 10)
	{
		key_input = getch();
	}
}

