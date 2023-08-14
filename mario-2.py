import cs50

while True:
    height = cs50.get_int("Height: ")
    if height is None:
        print()
        exit(0)
    elif (height >= 1 and height <= 8):
        break

for i in range(height):
    print(" " * (height - i - 1), end="")
    print("#" * (i + 1), end="")
    print("  ", end="")
    print("#" * (i + 1))
