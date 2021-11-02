#include <stdio.h>
#include <cs50.h>


void print_adjacent_pyramid(int height);

int main(void)
{
    int height;

    //OBtaining the height input
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8); //Cannot accept any height lesss than 1 or greater than 8.

    print_adjacent_pyramid(height);
}


void print_adjacent_pyramid(int height)
{
    int n = 1; //this var is for the left-aligned pyramid
    while (n <= height)
    {
        //For each row in the pyramid
        for (int i = 0; i < height; i++)
        {

            //Right-aligned Pyramid
            for (int j = 0; j < height; j++)
            {
                if (j < (height - i - 1)) //As j increases then there's less no. of times the " " will be printed. var i increases each row
                {
                    printf(" ");
                }
                else
                {
                    printf("#");
                }
            }

            printf("  ");

            // Left-aligned pyramid
            for (int j = 0; j < n; j++)
            {
                printf("#");
            }

            //new line and incrementing n
            printf("\n");
            n += 1;
        }

    }
}