/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    int beg = 0;
    int end = n;
    while( beg <= end)
    {
        int mid = (beg + end) / 2;
        printf("beg = %i\nend = %i\nmid = %i\n",beg,end,mid);
        if(value == values[mid])
        {
           return true;
        }
        else if(value < values[mid])
        {
            end = mid - 1;
        }
        else if (value > values[mid])
        {
            beg = mid + 1;
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
int main()
{
    int a[10];
    int i = 0;
    for (i = 0; i < 10; i++)
    {
        printf("enter the %i element : ",i + 1);
        a[i] = GetInt();
        printf("\n");
    }
    sort(a,10);
    printf("after sorting : \n");
    for (i = 0; i < 10; i++)
    {
        printf("%i\n",a[i]);
    }
    printf("things go right till this line \n");
    if(search(2,a,10))
    {
        printf("2 is in the list\n");
    }
    else
    {
        printf("2 is not in the list\n");
    }
    return 0;
    
}