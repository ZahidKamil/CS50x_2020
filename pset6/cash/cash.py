from cs50 import get_float



while(True):
    change = get_float("Change owed: ")
    if(change > 0.0):
        break

change = change * 100

coins = 0

No25 = (int) (change/25)
change -= No25*25
No10 = (int) (change/10)
change -= No10*10
No5 = (int) (change/5)
change -= No5*5
No1 = (int) (change/1)
change -= No1*1

coins = No25 + No10 + No5 + No1
print(f"coins: {coins}, change: {change}")

