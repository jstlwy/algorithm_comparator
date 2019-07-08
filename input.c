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
int getIntInput(int numDigits)
{
	if(numDigits <= 0)
	{
		return -1;
	}
	numDigits = numDigits + 1;

	// Get user input
	char userInput[numDigits];
	fgets(userInput, numDigits, stdin);

	// Flush the buffer if the user entered too many characters.
	// First, check whether userInput contains newline char.
	bool newlineWasFound = false;
	int terminus = 0;
	for(int i = 0; i < numDigits; i = i + 1)
	{	
		if(*(userInput + i) == '\n')
		{
			newlineWasFound = true;
			terminus = i;
		}
	}

	// If no newline char found, input was too long.
	// Still, fgets automatically puts null char as last char in userInput.
	// Set terminus to last char, clear input.
	if(newlineWasFound == false)
	{
		terminus = numDigits - 1;
		int c = getchar();
		while (c != '\n' && c != EOF)
		{
			c = getchar();
		}
	}

	// Now check whether all chars are numbers and return input
	int userInt = 0;
	if(terminus == 0)
	{
		return -1;
	}
	else
	{
		int num = 0;
		char numChar;

		for(int i = 0; i < terminus; i = i + 1)
		{
			numChar = *(userInput + i);
			// Check that each char represents a number
			if(numChar < 48 || numChar > 57)
			{
				return -1;
			}
			// If it is a number, convert
			else
			{
				switch(numChar)
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
					num = num * 10;
					power = power - 1;
				}
				userInt = userInt + num;
			}
		}

		return userInt;
	}
}