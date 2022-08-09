#include "input.h"
#include <ncurses.h>
#include <limits.h>
#include <stdlib.h>


int get_int_input()
{
	// Get user input
	const int n = 7;
	char user_input[n+1];
	echo();
	getnstr(user_input, n);
	noecho();

	// Check whether all of the chars are numbers
	for (int i = 0; user_input[i] != '\0'; i++)
	{
		if (user_input[i] < 48 || user_input[i] > 57)
		{
			return INT_MIN;
		}
	}

	return atoi(user_input);
}


/*
 * Keep the input retrieval process safe and robust
 * by using fgets, flushing the buffer to prevent overflow,
 * and checking whether the user entered anything other
 * than integers into the input field.
 * Return -1 for invalid input.
 *
 * No reason to use this function anymore.
 * I'm just leaving it here just for reference.
 */
/*
int get_int_input(int num_digits)
{
	if (num_digits <= 0)
		return INT_MIN;

	// Add one to account for the newline char
	num_digits++;

	// Get user input
	char user_input[num_digits];
	echo();
	getnstr(user_input, num_digits-1);
	noecho();

	// The buffer must be flushed if the user entered too many characters.
	// First, check whether user_input contains a newline char.
	int terminus = -1;
	for (int i = 0; i < num_digits; i++) {	
		if (user_input[i] == '\n') {
			terminus = i;
			break;
		}
	}

	if (terminus < 0) {
		// If no newline char found, input was too long.
		// Set terminus to last char and clear input buffer.
		terminus = num_digits - 1;
		int c = getchar();
		while (c != '\n' && c != EOF) {
			c = getchar();
		}
	} else if (terminus == 0) {
		// Return -1 if the user just hit enter
		return INT_MIN;
	}

	int user_int = -1;
	for (int i = 0; i < terminus; i++) {
		char num_char = user_input[i];
		// Make sure that each char is a number
		if (num_char < 48 || num_char > 57) {
			return INT_MIN;
		}
		int num = num_char - '0';
		int power = terminus - 1 - i;
		while (power > 0) {
			num *= 10;
			power--;
		}
		user_int += num;
	}

	return user_int;
}
*/

