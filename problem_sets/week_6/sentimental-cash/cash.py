change_needed = int(float(input("How much change is owed? ")) * 100)

coin_values = [25, 10, 5, 1]

coins_needed = 0

for coin_value in coin_values:
    coins_needed += change_needed // coin_value
    change_needed = change_needed - (change_needed // coin_value) * coin_value

print(coins_needed)