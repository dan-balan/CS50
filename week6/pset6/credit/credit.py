# promt for input
# calculate checksum
# check for card length and starting digits
# print AMEX\n, MASTERCARD\n, VISA\n, or INVALID\n#


from cs50 import get_int
from cs50 import get_string


def main():
    """ """
    answer = get_card()
    cardcheck = checksum(answer)

    if cardcheck and len(answer) in {13, 15, 16}:
        if len(answer) in {15}:
            if answer[:2] in {'34', '37'}:
                print("AMEX\n")
            else:
                print('INVALID')
        if len(answer) in {13, 16}:
            if answer[:1] in {'4'}:
                print("VISA")
            elif len(answer) == 16 and answer[:2] in {'51', '52', '53', '54', '55'}:
                print("MASTERCARD")
            else:
                print('INVALID')
    else:
        print('INVALID')
    # print(cardcheck)


def get_card():
    """ ask the user to input a card number """
    while True:
        n = get_string("Number: ")
        # if len(n) in {13, 15, 16}:
        if n.isdigit():
            break
    return n


def checksum(cardnumber):
    """ checksum verification Luhn’s Algorithm  """
    even_digits = cardnumber[-2::-2]
    sq_even = [int(x)*2 for x in even_digits]
    odd_digits = cardnumber[-1::-2]
    sumofdig = 0

    for nbr in sq_even:
        if nbr > 9:
            sumofdig = sumofdig + (nbr - 9)
        else:
            sumofdig = sumofdig + nbr

    for nbr in odd_digits:
        sumofdig += int(nbr)

    reminder = sumofdig % 10

    if reminder == 0:
        return True
    else:
        return False


if __name__ == "__main__":
    main()