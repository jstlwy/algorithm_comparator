#include "input.h"

/*
 * Keep the input retrieval process safe and robust
 * by using fgets, flushing the buffer to prevent overflow,
 * and checking whether the user entered anything other
 * than integers into the input field.
 */
int getIntInput(int lowerBound, int upperBound)
{
	int userInt;
	bool newlineWasFound;
	int terminus;
	char userInput[INPUT_LENGTH];
	bool isValidInput = false;

	while(isValidInput == false)
	{
		userInt = 0;
		newlineWasFound = false;
		terminus = 0;
		isValidInput = false;

		// Get user input
		fgets(userInput, INPUT_LENGTH, stdin);
		// Flush the buffer if the user entered too many characters.
		// First, check whether userInput contains newline char.
		for(int i = 0; i < INPUT_LENGTH; i = i + 1)
		{	
			if(*(userInput + i) == '\n')
			{
				newlineWasFound = true;
				terminus = i;
			}
		}
		// If no newline char found, input was too long.
		// Still, fgets automatically pulls NULL char as last char in userInput.
		// Set terminus to last char, clear input.
		if(newlineWasFound == false)
		{
			terminus = INPUT_LENGTH - 1;
			int c = getchar();
			while (c != '\n' && c != EOF)
			{
				c = getchar();
			}
		}

		if(terminus != 0)
		{
			isValidInput = true;
			char numChar;
			int num = 0;
			for(int i = 0; i < terminus; i = i + 1)
			{
				numChar = *(userInput + i);
				// Check that each char represents a number
				if(numChar < 48 || numChar > 57)
				{
					isValidInput = false;
					break;
				}
				// If it is a number, convert
				else
				{
					switch(numChar)
					{
						case '0' :
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
					}
					userInt = userInt + num * (int)pow(10, (double)(terminus - 1 - i));
				}
			}
		}

		if(isValidInput == true)
		{
			if(userInt < lowerBound || userInt > upperBound)
			{
				isValidInput = false;
			}
		}

		if(isValidInput == false)
		{
			printf("Invalid input.  Please try again.\n");
		}
	}

	return userInt;
}