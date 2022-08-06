// promt for input
// calculate checksum
// check for card length and starting digits
// print AMEX\n, MASTERCARD\n, VISA\n, or INVALID\n

#include <cs50.h>
#include <stdio.h>
#include <math.h>

long ask3(string question, long min_allowed);
int numberlength(long number);
int first2digits(long number, int len, int combien);
bool checksum(long number);

int main(void)
{
    // Prompt for card number
    long cardnumber = ask3("Number: ", 0);

    // length of the card number1
    int length = numberlength(cardnumber);

    // check Luhm's sum
    int checkvalid = checksum(cardnumber);

    // fisrt 2 digits - for AMEX & Mastercard type
    int f2digs = first2digits(cardnumber, length, 2);
    // first digit - for VISA type
    int f1digs = first2digits(cardnumber, length, 1);

    // check the validity of card number
    if ((length == 15 || length == 13 || length == 16) && (checkvalid))
    {
        if (length == 15)
        {
            if (f2digs == 34 || f2digs == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        if (length == 16 || length == 13)
        {
            if (f1digs == 4)
            {
                printf("VISA\n");
            }
            else if (length == 16 && (f2digs == 51 || f2digs == 52 || f2digs == 53 || f2digs == 54 || f2digs == 55))
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

    }
    else
    {
        printf("INVALID\n");
    }

}

// calculate the first two digits of the number
int first2digits(long number, int len, int combien)
{
    int f2digs = number / pow(10, (len - combien));
    return f2digs;
}


// checksum verification Luhn’s Algorithm
bool checksum(long number)
{
    int counter = 0;
    int luhnsum = 0;
    int one_digit = 0;
    while (number > 0)
    {
        one_digit = number % 10;
        if (counter % 2 != 0)
        {
            int doubledigits = one_digit * 2;
            // double of second-to-last digit - multiply every other digit by 2
            if (doubledigits > 9)
            {
                luhnsum = luhnsum + (doubledigits - 9);
            }
            else
            {
                luhnsum = luhnsum + doubledigits;
            }
        }
        if (counter % 2 == 0)
        {
            luhnsum = luhnsum + one_digit;
        }
        number = (number - one_digit) / 10;
        counter++;
    }
    // check if the total modulo 10 is congruent to 0
    if (luhnsum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// calculate the card number length
int numberlength(long number)
{
    int counter = 0;
    int one_digit = 0;
    while (number > 0)
    {
        one_digit = number % 10;
        number = (number - one_digit) / 10;
        counter++;
    }
    return counter;
}

// promt function
long ask3(string question, long min_allowed)
{
    long n;
    do
    {
        n = get_long("%s", question);
    }
    while (n < min_allowed);

    return n;
}