"""
text complexity using Coleman-Liau index
Coleman-Liau index is computed as 0.0588 * L - 0.296 * S - 15.8, where:
L is the average number of letters per 100 words in the text,
S is the average number of sentences per 100 words in the text;

"""

import re
from cs50 import get_string


def main():
    # ask user for a text
    answer = get_string('Text: ')

    # letters/sentences/word number
    lettersnbr = count_letters(answer)
    wordsnbr = len(answer.split())
    sentencesnbr = len(re.split('[.!?] ', answer))

    gradeIndex = col_index(lettersnbr, sentencesnbr, wordsnbr)

    # print grade
    if gradeIndex >= 1 and gradeIndex < 16:
        print(f'Grade {gradeIndex}')
    elif gradeIndex < 1:
        print('Before Grade 1')
    elif gradeIndex >= 16:
        print('Grade 16+')


def count_letters(text):
    """ count only alpha chars """
    letters_nbr = 0
    for char in text:
        if char.isalpha():
            letters_nbr += 1
    return letters_nbr


def col_index(letters, sentences, words):
    """ calculate Coleman-Liau index """
    L = (letters * 100.0) / words
    S = (sentences * 100.0) / words
    index = 0.0588 * L - 0.296 * S - 15.8
    return round(index)


if __name__ == "__main__":
    main()