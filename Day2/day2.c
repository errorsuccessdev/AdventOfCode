// TODO: Fix algorithm so that we can remove the first number in the 
//			array and recheck it
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "day2answer.h"

//#define DEBUG_OUTPUT
//#define DEBUG_FILE

#ifdef  DEBUG_FILE
#define FILEPATH "C:\\Users\\ann\\source\\repos\\AdventOfCode\\Day2\\debug_input.txt"
#elif defined(DEBUG_EXCLUDE_KNOWN_CORRECT)
#define FILEPATH "C:\\Users\\ann\\source\\repos\\AdventOfCode\\Day2\\input_exclude_known_correct.txt"
#else
#define FILEPATH "C:\\Users\\ann\\source\\repos\\AdventOfCode\\Day2\\input.txt"
#endif //  DEBUG_FILE

#define ARRAYSIZE 1024
#define OR ||
#define AND &&

int absoluteValue(int number)
{
	if (number < 0)
	{
		number *= -1;
	}
	return number;
}

//	The levels are either all increasing or all decreasing.
// Any two adjacent levels differ by at least one and at most three.
bool isSeriesSafe(int* array, int startIndex, int endIndex)
{
	int direction = 0; // 1 is increasing, -1 is decreasing
	for (int i = (startIndex + 1); i < endIndex; i++)
	{
		int priorNumber = array[i - 1]; // This is seems weird
		int difference = absoluteValue(array[i] - priorNumber);
		if ((difference == 0) OR(difference > 3))
		{
			return false;
		}
		if (direction == 0)
		{
			if (array[i] > priorNumber)
			{
				direction = 1;
			}
			else if (array[i] < priorNumber)
			{
				direction = -1;
			}
		}
		else if (direction == 1) // Positive
		{
			if (array[i] < priorNumber)
			{
				return false;
			}
		}
		else if (direction == -1) // Negative
		{
			if (array[i] > priorNumber)
			{
				return false;
			}
		}
	}
	return true;
}

void uglyDebugOutputManager(bool isSafe)
{
	if (isSafe)
	{
#ifdef DEBUG_OUTPUT
		printf("Series is safe\n");
#endif // DEBUG_OUTPUT
	}
	else
	{
#ifdef DEBUG_OUTPUT
		printf("Series is unsafe\n");
#endif // DEBUG_OUTPUT
	}
}

void copyOneArrayIntoAnotherButSkipOneElement(
	int* copyFrom, int* copyTo, int size, int skipMe
)
{
	int copyFromIndex = 0;
	int copyToIndex = 0;
	int numLeftToCopy = size;
	while (numLeftToCopy > 0)
	{
		if (copyFromIndex == skipMe)
		{
			copyFromIndex += 1;
			numLeftToCopy -= 1;
		}
		copyTo[copyToIndex] = copyFrom[copyFromIndex];
		copyToIndex += 1;
		copyFromIndex += 1;
		numLeftToCopy -= 1;
	}
}

bool bruteForceSeries(int* series, int size)
{
	bool isSafe = isSeriesSafe(series, 0, size);
	if (isSafe)
	{
		return true;
	}
	int tempSeries[ARRAYSIZE]; // Ugh, C sucks!
	for (int i = 0; i < size; i++)
	{
		copyOneArrayIntoAnotherButSkipOneElement(
			series, tempSeries, size, i
		);
		isSafe = isSeriesSafe(tempSeries, 0, size - 1);
		if (isSafe)
		{
			return true;
		}
	}
	return false;
}

int main()
{
	FILE* input = fopen(FILEPATH, "r");
	assert(input);

	int array[ARRAYSIZE] = { 0 };
	int count = 0;
	int numSafe = 0;
	int tempValue = 0;
	while (1)
	{
		char c = fgetc(input);
#ifdef DEBUG_OUTPUT
		putchar(c);
#endif // DEBUG_OUTPUT
		if (c >= '0' && c <= '9')
		{
			tempValue = (tempValue * 10) + (c - '0');
		}
		else if (c == ' ' || c == '\n')
		{
			array[count] = tempValue;
			count += 1;
			tempValue = 0;
		}
		if (c == '\n')
		{
			bool isSafe = bruteForceSeries(array, count);
			if (isSafe)
			{
				numSafe += 1;
			}
			uglyDebugOutputManager(isSafe);
			count = 0;
		}
		else if (c == EOF)
		{
			break;
		}
	}
	printf("There were %d safe reports\n", numSafe);

	int result = fclose(input);
	assert(result == 0);
}