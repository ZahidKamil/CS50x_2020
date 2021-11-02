from cs50 import get_int

while(True):
    number = get_int("Height: ")
    if(number >=1 and number <=8):
        break


for i in range(number):
    # Printing right pyramid
    for j in range(number):
        if(j < number - i - 1):
            print(" ", end ="")
        else:
            print("#", end="")

    print(" ", end="")

    # Printing left pyramid
    for k in range(i+1): # k runs from 0 to i-1
        print("#", end="")

    print()