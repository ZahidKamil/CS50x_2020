/*
INSERTION SORT - Sorting an array in ascending order

1. Iterate from arr[1] to arr[n] over the array
2. Compare the current element(index) to its predecessor
3. If the index is smaller than its predecessor, compare it to the elements before. Move the greater elements one position up to make space for the swapped element.

*/


#include<stdio.h>

int main(void)
{
    int array[] = {5,2,1,3,8,7,10,35,22,76,89,69,27,55,90,34,6,4};
    int len = sizeof(array) / sizeof(array[0]);
    int index,j;
    for (int i = 1; i < len; i++)
    {
        index = array[i];
        j = i -1;

        while(j >= 0 && array[j] > index)
        {
            array[j+1] = array[j];
            j = j -1;
        }
        array[j+1] = index;
    }

    printf("Sorted Array........\n");
    for(int i = 0; i < len; i++)
    {
        printf("%i ", array[i]);
    }
    printf("\n");

}