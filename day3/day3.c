#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#ifdef  DEBUG_FILE
#define FILEPATH "C:\\Users\\ann\\source\\repos\\AdventOfCode\\Day3\\debug_input.txt"
#else
#define FILEPATH "C:\\Users\\ann\\source\\repos\\AdventOfCode\\Day3\\input.txt"
#endif //  DEBUG_FILE

#define OR ||
#define AND &&
#define NOT !

int main()
{
	FILE* input = fopen(FILEPATH, "r");
	assert(input);

	char* mulStart = "mul(";
	int mulStartIndex = 0;
	const int mulStartLength = 4;
	int multiply1 = 0;
	bool inMulPart1 = false;
	int multiply2 = 0;
	bool inMulPart2 = false;
	int mulTotal = 0;

	bool mulEnabled = true;
	char* instStart = "do";
	const int instStartLength = 2;
	int instStartIndex = 0;
	bool inInstStart = false;
	char* doInst = "()";
	const int doInstLength = 2;
	int doInstIndex = 0;
	char* dontInst = "n't()";
	const int dontInstLength = 5;
	int dontInstIndex = 0;
	bool inDontInst = false;

	while (1)
	{
		char c = fgetc(input);
		if (c == EOF)
		{
			break;
		}
		else if (c == instStart[instStartIndex])
		{
			instStartIndex += 1;
			if (instStartIndex >= instStartLength)
			{
				inInstStart = true;
			}
			continue;
		}
		else if (c == doInst[doInstIndex] AND
			inInstStart AND
			(inDontInst == false))
		{
			doInstIndex += 1;
			if (doInstIndex >= doInstLength)
			{
				mulEnabled = true;
			}
			continue;
		}
		else if (c == dontInst[dontInstIndex] AND
			inInstStart)
		{
			inDontInst = true;
			dontInstIndex += 1;
			if (dontInstIndex >= dontInstLength)
			{
				mulEnabled = false;
			}
			continue;
		}
		else if (c == mulStart[mulStartIndex] AND
			mulEnabled)
		{
			mulStartIndex += 1;
			if (mulStartIndex >= mulStartLength)
			{
				inMulPart1 = true;
			}
			continue;
		}
		else if ('0' <= c AND
			c <= '9' AND
			mulEnabled)
		{
			if (inMulPart1)
			{
				multiply1 = (multiply1 * 10) + (c - '0');
			}
			else if (inMulPart2)
			{
				multiply2 = (multiply2 * 10) + (c - '0');
			}
			continue;
		}
		else if (c == ',' AND
			multiply1 > 0)
		{
			inMulPart2 = true;
			inMulPart1 = false;
			continue;
		}
		else if (c == ')' AND
			multiply2 > 0)
		{
			mulTotal += (multiply1 * multiply2);
		}
		mulStartIndex = 0;
		inMulPart1 = false;
		inMulPart2 = false;
		multiply1 = 0;
		multiply2 = 0;
		inInstStart = false;
		dontInstIndex = 0;
		doInstIndex = 0;
		instStartIndex = 0;
		inDontInst = false;
	}

	printf("Mul total: %d\n", mulTotal);

	int result = fclose(input);
	assert(result == 0);
}