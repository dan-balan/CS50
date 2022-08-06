//Determine how long it takes for a population to reach a particular size.
//Say we have a population of n llamas. Each year, n / 3 new llamas are born, and n / 4 llamas pass away.
//If we start with fewer than 9 llamas, the population of llamas will quickly become stagnant!

#include <cs50.h>
#include <stdio.h>

int ask(string question, int min_allowed);

int main(void)
{

    // Prompt for start size
    int start_size = ask("Start size: ", 9);

    // Prompt for end size
    int threshold_size = ask("End size: ", start_size);

    // Calculate number of years until we reach threshold
    int years = 0;
    while (start_size < threshold_size)
    {
        start_size = start_size + (start_size / 3)  - (start_size / 4);
        years++;
    }

    // Print number of years
    printf("Years: %i\n", years);
}


//promt function
int ask(string question, int min_allowed)
{
    int n;
    do
    {
        n = get_int("%s", question);
    }
    while (n < min_allowed);

    return n;
}

