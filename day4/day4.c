#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

//#define DEBUG_INPUT

#ifdef  DEBUG_INPUT
#define FILEPATH "C:\\Users\\ann\\source\\repos\\AdventOfCode\\Day4\\debug_input.txt"
#else
#define FILEPATH "C:\\Users\\ann\\source\\repos\\AdventOfCode\\Day4\\input.txt"
#endif //  DEBUG_INPUT

#define OR ||
#define AND &&
#define NOT !

int getPattern(char* array, int count,
	char* pattern, int patternCount, 
	int jumpBy)
{
	int patternIndex = 0;
	int totalMatches = 0;
	for (int i = 0; i < count; i++)
	{
		if (array[i] == pattern[patternIndex])
		{
			patternIndex += 1;
			for (int offset = 1; offset < patternCount; offset++)
			{
				int jumpTo = (offset * jumpBy) + i;
				if (jumpTo >= count) // lol
				{
					return totalMatches;
				}
				if (array[jumpTo] ==
					pattern[patternIndex])
				{
					patternIndex += 1;
				}
				else
				{
					break;
				}
			}
			if (patternIndex == patternCount)
			{
				totalMatches += 1;
			}
		}
		patternIndex = 0;
	}
	return totalMatches;
}

int getFileLength(FILE* file)
{
	int result = fseek(file, 0, SEEK_END);
	assert(result == 0);
	int size = ftell(file); // Does include \r
	rewind(file);
	return size;
}

int getLineLength(char* array, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (array[i] == '\n') // n00b lol
		{
			return i + 1;
		}
	}
	return -1;
}

int getMatches(char* array, int count, 
	char* pattern, int patternCount,
	int lineLength)
{
	// Diagonally
	int totalMatches = getPattern(
		array,
		count,
		pattern,
		patternCount,
		lineLength + 1
	);

	// Forwards
	totalMatches += getPattern(
		array,
		count,
		pattern,
		patternCount,
		1
	);

	// Vertically
	totalMatches += getPattern(
		array,
		count,
		pattern,
		patternCount,
		lineLength
	);

	// Opposite diagonally
	totalMatches += getPattern(
		array,
		count,
		pattern,
		patternCount,
		lineLength - 1
	);
	return totalMatches;
}

int main()
{
	FILE* input = fopen(FILEPATH, "r");
	assert(input);
	int fileLength = getFileLength(input);
	char* data = malloc(fileLength);
	assert(data);
	int dataCount = (int) fread(data, sizeof(char), fileLength, input);
	assert(dataCount > 0); // fread gets rid of \r

	int lineLength = getLineLength(data, dataCount);
	assert(lineLength > 0);

	int totalMatches = getMatches(
		data, dataCount, 
		"XMAS", 4, 
		lineLength
	);
	totalMatches += getMatches(
		data, dataCount, 
		"SAMX", 4,
		lineLength
	);

	printf("Total matches: %d\n", totalMatches);

	int result = fclose(input);
	assert(result == 0);
	free(data);
}