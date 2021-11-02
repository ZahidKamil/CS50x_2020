#include<stdio.h>
#include<cs50.h>
#include<math.h>

int checksum(long credit_card);
void check_type_card(long credit_card, int total_digits);

int main(void)
{

    long credit_card;
    credit_card = get_long("Number: ");
    int valid_digits = credit_card / 1e12; //since credit cards have atleast 13 digits or more


    if (valid_digits > 1)
    {
        int total_digits = checksum(credit_card);
        if (total_digits != -1)
        {
            check_type_card(credit_card, total_digits);
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}

int checksum(long credit_card)
{
    int count_odd_digits = 0;
    int even_digit = 0;
    int count_even_digits = 0;
    int total_digits = 0;
    int last_digit;
    for (int i = 1; credit_card > 0; i++)
    {
        last_digit = credit_card % 10; //getting the last digit

        if (i % 2 == 0) //this is for every other number from the second last
        {
            even_digit = (last_digit) * 2; //multiplying by 2
         //the lowest possible number when multiplied by 2 is 8, so if greater than 10 then we need to separate the digits. The highest possible is 18.
            if (even_digit > 9)
            {
                count_even_digits += even_digit % 10; //this obtains the singles digits ex: if 18 then 8
                count_even_digits += 1; //no need to do a modulo since we know that this is going to be 1
            }
            else
            {
                count_even_digits += even_digit; //adding to the even digit total
            }

        }
        else
        {
            count_odd_digits += last_digit; //these are the odd digits that will be added
        }
        credit_card /= 10; //dividing the number by 10 to ensure we cget the recent last digit.
        total_digits += 1;
    }
    printf("count_odd_digits: %i\n", count_odd_digits);
    printf("count_even_digits: %i\n", count_even_digits);

    int sum = count_odd_digits + count_even_digits;

    // printf("final sum: %i\n", sum);
    // printf("no. of digits: %i\n",total_digits);

    if (sum % 10 == 0)
    {
        return total_digits;
    }
    else
    {
        return -1;
    }

}

void check_type_card(long credit_card, int total_digits)
{

    int double_digit = credit_card / pow(10, total_digits - 2); //obtaining the first two digits.

    printf("double_digit: %i\n", double_digit);

    if (total_digits == 15 && (double_digit == 34 || double_digit == 37))
    {
        printf("AMEX\n");
    }
    else if (total_digits == 16 && (double_digit % 50 <= 5)) // Mastercards start from 50-55
    {
        printf("MASTERCARD\n");
    }
    else if ((total_digits == 13 || total_digits == 16) && (int) double_digit / 10 == 4) //Visa cards start with digit 4
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

}