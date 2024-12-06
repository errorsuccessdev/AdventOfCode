// TODO: Simplify code by removing the need for convertToBigNumber
//		(ret * 10 + array[i])
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "day2answer.h"

#define FILEPATH "C:\\Users\\ann\\source\\repos\\AdventOfCode\\Day2\\input.txt"
#define ARRAYSIZE 1024
#define OR ||

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
		if ((difference == 0) OR (difference > 3))
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
			bool isSafe = isSeriesSafe(array, 0, count);
			if (isSafe)
			{
				numSafe += 1;
			}
			count = 0;
		}
		else if (c == EOF)
		{
			break;
		}
	}
	printf("There were %d safe reports\n", numSafe);
	assert(numSafe == ANSWER);

	int result = fclose(input);
	assert(result == 0);
}