/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    int beg = 0;
    int end = n;
    while( end - beg >= 1)
    {
        int mid = (beg + end) / 2;
        if(value == values[mid])
        {
           return true;
        }
        else if(value < values[mid])
        {
            end = mid;
        }
        else if (value > values[mid])
        {
            beg = mid;
        }
        
    }
    return false;
}


/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    int temp;
    int swaps = 1;
    while(swaps!=0)
    {
        swaps = 0;
        for (int i = 0;i < n-1; i++)
            {
                if(values[i]>values[i+1])
                {
                    temp = values[i];
                    values[i] = values[i+1];
                    values[i+1] = temp;
                    swaps++;
                }
            }
    }
}