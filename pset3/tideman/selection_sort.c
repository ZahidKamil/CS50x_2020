
/*
SELECTION SORT

Repeat until no unsorted elements remain:
    Search the unsorted part of the data to find the smallest value
    Swap the smallest found value with the first element of the unsorted part

*/

#include<stdio.h>


void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}


int main(void)
{
    int array[] = {5,2,1,3,8,7,10,35,22,76,89,69,27,55,90,34,6,4};
    int len = sizeof(array) / sizeof(array[0]);

    int i = 0;
    int smallest = array[0];
    int k = 0;
    while(i != len -1)
    {
        for (int j = i; j < len; j++)
        {
              if(smallest > array[j])
              {
                  smallest = array[j];
                  k = j;
              }
        }

        swap(&array[i], &array[k]);
        i++;
        smallest = array[i];
        k = i;
    }

    printf("Sorted Array........\n");
    for(int j = 0; j < len; j++)
    {
        printf("%i ", array[j]);
    }
    printf("\n");
}