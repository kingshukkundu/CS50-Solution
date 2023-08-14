# Get card number
card = input("Number: ")
while not card.isdigit() or int(card) < 0:
    card = input("Retry: ")
length = len(card)

if (sum([int(n)*2%10+int(n)*2//10 for n in card[-2::-2]]) + sum([int(n) for n in card[-1::-2]])) % 10:
    print("INVALID")
elif length == 15 and card[0:2] == "34" or card[0:2] == "37":
    print("AMEX")
elif length == 16 and int(card[0:2]) in range(51,56):
    print("MASTERCARD")
elif length == 13 or length == 16 and card[0] == "4":
    print("VISA")
else:
    print("INVALID")