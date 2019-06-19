#ifndef INPUT_H
#define INPUT_H

/*
 * Keep the input retrieval process safe and robust
 * by using fgets, flushing the buffer to prevent overflow,
 * and checking whether the user entered anything other
 * than integers into the input field.
 */
int getIntInput(int numDigits);

#endif