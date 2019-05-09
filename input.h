#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define INPUT_LENGTH 3

/*
 * Keep the input retrieval process safe and robust
 * by using fgets, flushing the buffer to prevent overflow,
 * and checking whether the user entered anything other
 * than integers into the input field.
 */
int getIntInput(int lowerBound, int upperBound);

#endif