from cs50 import get_int

while(True):
    number = get_int("Height: ")
    if(number >=1 and number <=8):
        break
j = 0
for i in range(number):
    for j in range(number):
        if(j < number - i - 1):
            print(" ", end ="")
        else:
            print("#", end="")
    print()
