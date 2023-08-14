import cs50

# Prompt user for pyramid's height
while True:
    height = cs50.get_int("Height: ")

    # Handle EOF
    if height is None:
        print()
        exit(0)

    # Validate height
    elif height >= 1 and height <= 8:
        break

# Iterate over pyramid's rows
for i in range(height):

    # Print spaces
    print(" " * (height - i - 1), end="")

    # print hashes
    print("#" * (i + 1))
