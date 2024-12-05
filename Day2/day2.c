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

// This is probably the worst possible way to do this ever
int convertToBigNumber(int* numbers, int numbersCount)
{
	int ret = 0;
	int multiplyBy = 1;
	for (int i = numbersCount - 1; i >= 0; i--)
	{
		ret += numbers[i] * multiplyBy;
		multiplyBy *= 10;
	}
	return ret;
}

int main()
{
	FILE* input = fopen(FILEPATH, "r");
	assert(input);

	int count = 0;
	int numbersCount = 0;
	int array[ARRAYSIZE] = { 0 };
	int numbers[ARRAYSIZE] = { 0 };
	int numSafe = 0;
	while (1) 
	{
		char c = fgetc(input);
		if (c >= '0' && c <= '9')
		{
			numbers[numbersCount] = c - '0';
			numbersCount += 1;
		}
		else if (c == ' ' || c == '\n')
		{
			array[count] = convertToBigNumber(numbers, numbersCount);
			count += 1;
			numbersCount = 0;
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