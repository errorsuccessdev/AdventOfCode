#include <stdio.h>
#include <assert.h>
#include "day1inputs.h"
#include "day1answers.h"

void sortSmallestToLargest(int* array,int arrayStart, int arrayEnd)
{
    int smallest = array[arrayStart];
    int smallestLocation = arrayStart;
    for (int i = (arrayStart + 1); i < arrayEnd; i++)
    {
        if (smallest > array[i])
        {
            smallest = array[i];
            smallestLocation = i;
        }
    }
    array[smallestLocation] = array[arrayStart];
    array[arrayStart] = smallest;
    arrayStart += 1;
    if (arrayStart < arrayEnd)
    {
        // RESEARCH: Is recursion in C undesirable?
        // Not bad generally, but lower performance
        sortSmallestToLargest(array, arrayStart, arrayEnd);
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

int main()
{
    sortSmallestToLargest(array1, 0, ARRAYSIZE);
    sortSmallestToLargest(array2, 0, ARRAYSIZE);
    int totalDifference = 0;
    for (int i = 0; i < ARRAYSIZE; i++)
    {
        totalDifference += absoluteValue(array1[i] - array2[i]);
    }
    assert(totalDifference == ANSWER);
    printf("Total difference %d\n", totalDifference);
}
