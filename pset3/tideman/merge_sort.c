#include <stdio.h>


void merge_sort(int array[], int left, int right);
void merge_both(int array[], int left, int middle, int right);
void printArray(int array[], int size);

int main(void)
{
    int array[6] = {5,2,1,3,6,4};
    int size = sizeof(array) / sizeof(array[0]);


    merge_sort(array, 0, size-1);
    printArray(array, size);

}

void merge_sort(int array[], int left, int right)
{
    if(left < right)
    {
        int middle = left + (right - left) / 2; // finds the middle point of an array

        merge_sort(array, left, middle); //recursively calling until left > right from [l....m]
        merge_sort(array, middle + 1, right); //recursively calling from [m+1...r]

        merge_both(array, left, middle, right); // Once sorted then this is called.
    }

}

//When two arrays need to be merged. Create three pointers i,j,k
// i-> pointer of the first subarray i.e. subarray1
// j -> pointer of the second subarray i.e subarray2
// k -> pointer of the original array
void merge_both(int array[], int left, int middle, int right) //0,2,5
{
    int left_bound = middle - left + 1; //[left...middle] Number of elements for the first subarray
    int right_bound = right - middle; // [middle + 1...right] No. of elements for the second subarray

    //creating temporary arrays to store the elements of the first and second subarrays.
    int sub_array1[left_bound], sub_array2[right_bound];

    // copying the elements from the array's left point to and including the middle element
    for (int i = 0; i < left_bound; i++)
    {
        sub_array1[i] = array[left + i];
    }

    //copying the elements from the array's middle + 1 's element to the right
    for (int j = 0; j < right_bound; j++)
    {
        sub_array2[j] = array[middle + 1 + j];
    }

    //Creating the 3 pointers.
    int i,j,k;
    i = 0;
    j = 0;
    k = left;

    //Merging the two arrays and comparing which is lesser/greater and placing it in the left position of the original array
    while(i < left_bound && j < right_bound)
    {
        if(sub_array1[i] >= sub_array2[j])
        {
            array[k] = sub_array1[i];
            i++;
        }
        else
        {
            array[k] = sub_array2[j];
            j++;
        }

        k++;
    }

    //Since EITHER one of the subarrays might be larger we have to include the rest of the elements.
    // Notice that we exited the previous while loop because either i or j has reached the end of its respective subarray.

    while(i < left_bound)
    {
        array[k] = sub_array1[i];
        i++;
        k++;
    }

    while(j < right_bound)
    {
        array[k] = sub_array2[j];
        j++;
        k++;
    }

}

void printArray(int array[], int size)
{
    printf("Sorted Array.......\n");
    for(int i = 0; i < size; i++)
    {
        printf("%i ", array[i]);
    }
    printf("\n");
}

