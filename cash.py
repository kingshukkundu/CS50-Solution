import cs50

# prompt user for change owed
while True:
    dollars = cs50.get_float("Change: ")
    if dollars >= 0.0:
        break

# convert dollars to cents to avoid floating-point imprecision
cents = round(dollars * 100)

# initialize counter for coins
coins = 0

# take as many 25-cent bites out of problem as possible, relying on integer division for whole number
coins += cents // 25

# amount of changed owed now equals remainder after dividing by 25
cents = cents % 25

# repeat for dimes
coins += cents // 10
cents = cents % 10

# repeat for nickels
coins += cents // 5
cents = cents % 5

# remainder is now < 5, so handle with pennies
coins += cents

# print counter
print(coins)
