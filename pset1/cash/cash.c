#include<stdio.h>
#include<cs50.h>
#include<math.h>

void number_of_coins(int change);

int main(void)
{

    float change;

    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0.00);

    printf("changed owed: %.2f\n", change);

    int cents = round(change * 100);
    printf("cents: %i\n", cents);
    number_of_coins(cents);

}

void number_of_coins(int change)
{
    int no25 = change / 25;
    // printf("no25: %i\n",no25);
    change = change - no25 * 25;
    int no10 = change / 10;
    // printf("no10: %i\n",no10);
    change = change - no10 * 10;
    int no5 = change / 5;
    // printf("no5: %i\n",no5);
    change = change - no5 * 5;
    int no1 = change;
    // printf("no1: %i\n",no1);

    printf("Greedy Algorithm coins: %i\n", no25 + no10 + no5 + no1);
}
