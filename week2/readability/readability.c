#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// function prototyping
float colLiIndex(int letters, int sentences, int words);
int nbofwords(string giventext);
int nbofsentences(string giventext);
int nbofletters(string giventext);


int main(void)
{

    // Get input words
    string giventext = get_string("Text: ");

    // count number of letters
    int letters = nbofletters(giventext);

    // count number of letters
    int words = nbofwords(giventext);

    // count the number of sentences
    int sentences = nbofsentences(giventext);

    // Coleman-Liau index calculation
    float clIndex = colLiIndex(letters, sentences, words);

    // round to the nearest integer ~ Grade Level
    int trunIndex = round(clIndex);
    //printf("%i letter(s)\n", letters);
    //printf("%i word(s)\n", words);
    //printf("%i sentence(s)\n", sentences);

    // print grade
    if (trunIndex >= 1 && trunIndex < 16)
    {
        printf("Grade %i\n", trunIndex);
    }

    if (trunIndex < 1) 
    {
        printf("Before Grade 1\n");
        
    }
    if (trunIndex >= 16) 
    {
        printf("Grade 16+\n");
        
    }

    return 0;

}

// number of words
int nbofletters(string giventext)
{
    int totalletters = 0;
    for (int i = 0, n = strlen(giventext) ; i < n ; i++)
    {
        if ((giventext[i] >= 'A' && giventext[i] <= 'Z') || (giventext[i] >= 'a' && giventext[i] <= 'z')) 
        {
            totalletters++;
            
        }
    }
    return totalletters;
}

// number of words
int nbofwords(string giventext)
{
    int totalwords = 1;
    for (int i = 0, n = strlen(giventext) ; i < n ; i++)
    {
        if (giventext[i] == ' ') 
        {
            totalwords++;
            
        }
    }
    return totalwords;
}

// number of sentences
int nbofsentences(string giventext)
{
    int totalsentences = 0;
    for (int i = 0, n = strlen(giventext) ; i < n ; i++)
    {
        if (giventext[i] == '.' || giventext[i] == '!' || giventext[i] == '?') 
        {
            totalsentences++;
            
        }
    }
    return totalsentences;
}

// Coleman-Liau index calculation function
float colLiIndex(int letters, int sentences, int words)
{
    // average number of letters
    float L = (letters * 100.0) / words;
    float S = (sentences * 100.0) / words;

    float index = 0.0588 * L - 0.296 * S - 15.8;
    return index;
}

