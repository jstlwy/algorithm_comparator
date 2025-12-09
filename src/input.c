#include "input.h"
//#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <ncurses.h>

#define MAX_INPUT_DIGITS (8)

long get_int_input(void)
{
    // Add 1 for newline character
    char user_input[MAX_INPUT_DIGITS+1];

    echo();
    getnstr(user_input, MAX_INPUT_DIGITS);
    noecho();

    errno = 0;
    char* endptr = NULL;
    const long value = strtol(user_input, &endptr, 10);
    if ((errno == ERANGE) || (endptr == user_input)) {
        printw("%s: ERROR: Invalid input.\n", __func__);
        return LONG_MIN;
    }
    return value;
}

#if 0
/*
 * Keep the input retrieval process safe and robust
 * by using fgets, flushing the buffer to prevent overflow,
 * and checking whether the user entered anything other
 * than integers into the input field.
 * Return -1 for invalid input.
 */
int get_int_input(int num_digits)
{
    if (num_digits <= 0) {
        return INT_MIN;
    }

    // Add one to account for the newline char
    num_digits++;

    // Get user input
    char user_input[num_digits];
    echo();
    getnstr(user_input, num_digits-1);
    noecho();

    // The buffer must be flushed if the user entered too many characters.
    // First, check whether user_input contains a newline char.
    size_t terminus = -1;
    for (size_t i = 0; i < num_digits; i++) {
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

    int user_int = 0;
    for (size_t i = 0; i < terminus; i++) {
        // Make sure that each char is a number
        const char num_char = user_input[i];
        if ((num_char < '0') || (num_char > '9')) {
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
#endif
