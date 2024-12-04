#include <stdio.h>
#include <assert.h>
#include "day1inputs.h"
#include "day1answers.h"

void sortSmallestToLargest(int* array, int arraySize)
{
    for (int j = 0; j < arraySize; j++)
    {
        int smallest = array[j];
        int smallestLocation = j;

        for (int i = (j + 1); i < arraySize; i++)
        {
            if (smallest > array[i])
            {
                smallest = array[i];
                smallestLocation = i;
            }
        }
        array[smallestLocation] = array[j];
        array[j] = smallest;
    }
}

int absoluteValue(int number)
{
    if (number < 0)
    {
        number *= -1;
    }
    return number;
}

// Assumes array is already sorted smallest to largest
int numberOfTimesXAppearsInArray(int x, int* array, int arraySize)
{
    int numTimes = 0;
    for (int i = 0; i < arraySize; i++)
    {
        if (array[i] == x)
        {
            numTimes += 1;
        }
        else if (array[i] > x)
        {
            break;
        }
    }
    return numTimes;
}

int main()
{
    sortSmallestToLargest(array1, ARRAYSIZE);
    sortSmallestToLargest(array2, ARRAYSIZE);
    int similarity = 0;
    for (int i = 0; i < ARRAYSIZE; i++)
    {
        int x = array1[i];
        int numTimes = numberOfTimesXAppearsInArray(x, array2, ARRAYSIZE);
        similarity += (x * numTimes);
    }
    printf("Similarity score: %d\n", similarity);
}
