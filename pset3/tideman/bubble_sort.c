/*
BUBBLE SORT
1. Set a variable swap counter to a non-zero value

2. Repeat until swap counter is 0:
        Reset swap_counter to 0
        Look at adjacent pair:
            IF two adjacent members are not in order, swap them and add to the swap counter
 
The large value are bubble to the right
*/


#include<stdio.h>

int main(void)
{
    int array[] = {5,2,1,3,8,7,10,35,22,76,89,69,27,55,90,34,6,4};
    int len = sizeof(array) / sizeof(array[0]);
    int size = len;
    int swap_counter = -1;
    int temp;
    while (swap_counter != 0)
    {
        swap_counter = 0;
        for(int i = 0; i < len - 1; i++)
        {
            if (array[i] > array[i+1])
            {
                temp = array[i];
                array[i] = array[i+1];
                array[i+1] = temp;
                swap_counter++;
            }
        }
        len = len - 1;
    }

    printf("Sorted Array........\n");
    for(int j = 0; j < size; j++)
    {
        printf("%i ", array[j]);
    }
    printf("\n");
}