// Create Mario type pyramids of blocks
// #
// req: allow the user to decide just how tall the pyramids should be by first prompting them for a positive integer between, say, 1 and 8, inclusive

#include <cs50.h>
#include <stdio.h>

int ask2(string question, int min_allowed, int max_allowed);

int main(void)
{
    // Prompt for pyramid height
    int pyramid_height = ask2("Height: ", 1, 8);
    int adj_pyramid = pyramid_height * 2 + 2;       // adjacent pyramid + 2 gap spaces between

    // draw one side of the pyramid
    for (int i = 0; i < pyramid_height; i++)
    {
        for (int j = 0; j < pyramid_height; j++)
        {
            if (j < (pyramid_height - 1) - i)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }

        }

        // draw adj pyramid
        for (int k = pyramid_height - 1; k < pyramid_height + 2 + i; k++)
        {
            if (k >= pyramid_height + 1)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }

        printf("\n");
    }

}


// promt function
int ask2(string question, int min_allowed, int max_allowed)
{
    int n;
    do
    {
        n = get_int("%s", question);
    }
    while (n < min_allowed || n > max_allowed);

    return n;
}