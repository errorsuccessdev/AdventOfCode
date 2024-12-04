// TODO: Would like to remove recursion in sortSmallestToLargest

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

int main()
{
    sortSmallestToLargest(array1, ARRAYSIZE);
    sortSmallestToLargest(array2, ARRAYSIZE);
    int totalDifference = 0;
    for (int i = 0; i < ARRAYSIZE; i++)
    {
        totalDifference += absoluteValue(array1[i] - array2[i]);
    }
    assert(totalDifference == ANSWER);
    printf("Total difference %d\n", totalDifference);
}
