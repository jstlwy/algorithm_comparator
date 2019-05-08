#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include <math.h>

#define INPUT_LENGTH 3

void printArray(int*, int);
void insertionSort(int*, int);
void mergeSort(int*, int, int);
void merge();
int getIntInput(int, int);

int main()
{
	srand(time(NULL));
	const int ARRAY_LENGTH = 1000;
	int array[ARRAY_LENGTH];
	int choice;
	struct timespec start, stop;

	do
	{
		printf("Choose your sorting method:\n");
		printf("1. Insertion Sort\n");
		printf("2. Merge Sort\n");
		printf("0. Quit\n");

		choice = getIntInput(0, 2);

		if(choice == 0)
		{
			printf("\nGoodbye.\n\n");
		}
		else
		{
			printf("\n");

			// Insert random numbers into array
			for(int i = 0; i < ARRAY_LENGTH; i = i + 1)
			{
				array[i] = rand() % 1000;
			}
			//printArray(array, ARRAY_LENGTH);

			switch(choice)
			{
				case 1:
					clock_gettime(CLOCK_MONOTONIC, &start);
					insertionSort(array, ARRAY_LENGTH);
					clock_gettime(CLOCK_MONOTONIC, &stop);
					break;
				case 2:
					clock_gettime(CLOCK_MONOTONIC, &start);
					mergeSort(array, 0, ARRAY_LENGTH - 1);
					clock_gettime(CLOCK_MONOTONIC, &stop);
					break;
			}
			//printArray(array, ARRAY_LENGTH);
			printf("\n");
			printf("Time elapsed: %ld (ns)\n", stop.tv_nsec - start.tv_nsec);
		}
	}
	while(choice != 0);

	return 0;
}

void printArray(int *array, int arraySize)
{
	for(int i = 0; i < arraySize; i = i + 1)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}

void insertionSort(int *array, int arraySize)
{
	int j;
	for(int i = 1; i < arraySize; i = i + 1)
	{
		int key = array[i];
		j = i - 1;
		while(j >= 0 && array[j] > key)
		{
			array[j + 1] = array[j];
			j = j - 1;
		}
		array[j + 1] = key;	
	}
}

void mergeSort(int *array, int l, int r)
{
	int median;
	if(l < r)
	{
		median = l + ((r - l) / 2);
		mergeSort(array, l, median);
		mergeSort(array, median + 1, r);
		merge(array, l, median, r);
	}
}

void merge(int *arr, int l, int m, int r)
{
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 

    // create temp arrays
    int L[n1], R[n2]; 

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i = i + 1) 
	{
        L[i] = arr[l + i]; 
	}
    for (j = 0; j < n2; j = j + 1) 
	{
        R[j] = arr[m + 1 + j]; 
	}

    // Merge the temp arrays back into arr[l..r]
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
		// Note: i or j only incremented
		// when their values are placed in k
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i = i + 1; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j = j + 1; 
        } 
        k = k + 1; 
    }

    // Copy any remaining elements of L[]
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i = i + 1; 
        k = k + 1; 
    } 
  
    // Copy any remaining elements of R[]
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j = j + 1; 
        k = k + 1; 
    } 
}

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
	bool isValidInput;

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