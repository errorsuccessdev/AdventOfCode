#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define DEBUG_INPUT

#ifdef  DEBUG_INPUT
#define FILEPATH "C:\\Users\\ann\\source\\repos\\AdventOfCode\\Day4\\debug_input.txt"
#else
#define FILEPATH "C:\\Users\\ann\\source\\repos\\AdventOfCode\\Day4\\input.txt"
#endif //  DEBUG_INPUT

#define OR ||
#define AND &&
#define NOT !

int getPatternGoingForwards(char* array, int count, 
	char* pattern, int patternCount, int jumpBy)
{
	int patternIndex = 0;
	int totalMatches = 0;
	int line = 1;
	for (int i = 0; i < count; i++)
	{
		if (array[i] == '\n')
		{
			line += 1;
		}
		if (array[i] == pattern[patternIndex])
		{
			patternIndex += 1;
			for (int offset = 1; offset < patternCount; offset++)
			{
				int jumpTo = (offset * jumpBy) + i;
				if (jumpTo > count)
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

int main()
{
	FILE* input = fopen(FILEPATH, "r");
	assert(input);
	int fileLength = getFileLength(input);
	char* data = malloc(fileLength);
	assert(data);
	int dataCount = (int) fread(data, sizeof(char), fileLength, input);
	assert(dataCount > 0); // fread gets rid of \r

	// Diagonally forwards
	int totalMatches = getPatternGoingForwards(
		data,
		dataCount,
		"XMAS",
		4,
		12
	);

	// Forwards
	totalMatches += getPatternGoingForwards(
		data,
		dataCount,
		"XMAS",
		4,
		1
	);

	// Vertically forwards
	totalMatches += getPatternGoingForwards(
		data,
		dataCount,
		"XMAS",
		4,
		11
	);

	printf("Total matches: %d\n", totalMatches);

	int result = fclose(input);
	assert(result == 0);
	free(data);
}