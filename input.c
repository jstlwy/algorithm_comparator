#include "input.h"
#include <stdio.h>
#include <stdbool.h>

/*
 * Keep the input retrieval process safe and robust
 * by using fgets, flushing the buffer to prevent overflow,
 * and checking whether the user entered anything other
 * than integers into the input field.
 * Return -1 for invalid input.
 */
int get_int_input(int num_digits)
{
	if(num_digits <= 0)
	{
		return -1;
	}
	num_digits++;

	// Get user input
	char user_input[num_digits];
	fgets(user_input, num_digits, stdin);

	// Flush the buffer if the user entered too many characters.
	// First, check whether user_input contains newline char.
	bool newline_was_found = false;
	int terminus = 0;
	for(int i = 0; i < num_digits; i++)
	{	
		if(user_input[i] == '\n')
		{
			newline_was_found = true;
			terminus = i;
		}
	}

	// If no newline char found, input was too long.
	// Still, fgets automatically puts null char as last char in user_input.
	// Set terminus to last char, clear input.
	if(newline_was_found == false)
	{
		terminus = num_digits - 1;
		int c = getchar();
		while (c != '\n' && c != EOF)
		{
			c = getchar();
		}
	}

	// Now check whether all chars are numbers and return input
	int user_int = 0;
	if(terminus == 0)
	{
		return -1;
	}
	else
	{
		int num = 0;
		char num_char;

		for(int i = 0; i < terminus; i++)
		{
			num_char = user_input[i];
			// Check that each char represents a number
			if(num_char < 48 || num_char > 57)
			{
				return -1;
			}
			// If it is a number, convert
			else
			{
				switch(num_char)
				{
				case '0' :
					num = 0;
					break;
				case '1' :
					num = 1;
					break;
				case '2' :
					num = 2;
					break;
				case '3' :
					num = 3;
					break;
				case '4' :
					num = 4;
					break;
				case '5' :
					num = 5;
					break;
				case '6' :
					num = 6;
					break;
				case '7' :
					num = 7;
					break;
				case '8' :
					num = 8;
					break;
				case '9':
					num = 9;
					break;
				default:
					break;
				}
				
				int power = terminus - 1 - i;
				while(power > 0)
				{
					num *= 10;
					power--;
				}
				user_int += num;
			}
		}

		return user_int;
	}
}

