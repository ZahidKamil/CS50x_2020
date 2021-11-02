from cs50 import get_int


def checksum(credit):
    i = 1
    count_odd_digits = even_digit = count_even_digits = total_digits = last_digit = 0

    while (credit > 0):
        last_digit = credit % 10

        if (i % 2 == 0):
            even_digit = last_digit * 2

            if (even_digit > 9):
                count_even_digits += even_digit % 10
                count_even_digits += 1

            else:
                count_even_digits += (int) (even_digit)

        else:
            count_odd_digits += (int) (last_digit)

        credit = (int) (credit / 10)
        total_digits += 1
        i += 1

    print("count_odd_digits: ", count_odd_digits)
    print("count_even_digits: ", count_even_digits)

    sum_digits = count_odd_digits + count_even_digits

    if(sum_digits % 10 == 0):
        return total_digits

    else:
        return -1


def check_type_card(credit, total_digits):
    double_digit = (int) (credit / 10 ** (total_digits - 2))
    print("double_digit: ", double_digit)

    if (total_digits == 15 and (double_digit == 34 or double_digit == 37)):
        print("AMEX")

    elif (total_digits == 16 and (double_digit % 50 <= 5)):
        print("MASTERCARD")

    elif ((total_digits == 13 or total_digits == 16) and ((int) (double_digit / 10) == 4)):
        print("VISA")

    else:
        print("INVALID")


def main():

    while(True):
        credit = get_int("Number: ")
        valid_digits = (int) (credit/10 ** 12)
        print(valid_digits)

        if (valid_digits > 1):
            total_digits = checksum(credit)

            if (total_digits != -1):
                check_type_card(credit,total_digits)
                break

            else:
                print("INVALID")
                break

        else:
            print("INVALID\n")
            break

main()