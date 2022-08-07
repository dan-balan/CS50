# Create Mario type pyramids of blocks
# using hashes (x) for bricks

from cs50 import get_int


def main():
    """ """
    height = get_int_limit()
    for i in range(height):
        # left side pyramid
        for j in range(height):
            if j < (height - 1) - i:
                print(" ", end="")
            else:
                print("#", end="")

        # right side pyramid
        for k in range(height - 1, height + 2 + i):
            if k >= height + 1:
                print("#", end="")
            else:
                print(" ", end="")
        print()


def get_int_limit():
    """ ask the user ro input a valid number """
    while True:
        n = int(get_int("Height: "))
        if n >= 1 and n <= 8:
            break
    return n


if __name__ == "__main__":
    main()