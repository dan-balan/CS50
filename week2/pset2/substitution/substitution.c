#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// function prototyping
bool ciphervalid(string plaintext);

// encrypt function
string encrypt(string plaintext, string key);


int main(int argc, string argv[])
{
    // check if argument was inputed
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
    // check length of key
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // check the calidity of key
    if (!ciphervalid(argv[1]))
    {
        printf("Non-valid key: %s\n", argv[1]);
        return 1;
    }
    
    // PROMT ask user for plaintext
    string plaintext = get_string("plaintext:  ");
    
    // encrypt plaintext
    string ciphertext = encrypt(plaintext, argv[1]);
    
    printf("ciphertext: %s\n", ciphertext);

    return 0;
}

// encrypt function
string encrypt(string plaintext, string key)
{
    string cyphertxt = NULL;
    for (int i = 0, n = strlen(plaintext) ; i < n ; i++)
    {
        if isalpha(plaintext[i])
        {
            // if islower pass through lower case keyform readaptation
            if (islower(plaintext[i]))
            {
                plaintext[i] = tolower(key[plaintext[i] - 97]);
                //strcat(cyphertxt, &ch);
            }
            if (isupper(plaintext[i]))
            {
                plaintext[i] = toupper(key[plaintext[i] - 65]);
            }
        }
    }
    return plaintext;
}


// check the integrity of cipher: alphabetic && containing each letter exactly once
bool ciphervalid(string key)
{
    int array [25] = {0};
    char ch;
    for (int i = 0, n = strlen(key) ; i < n ; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }
        //key[i]= tolower(key[i]);
        ch = key[i];
        //array[key[i] - 97] ++;
        array[tolower(ch) - 97] ++;

    }
    for (int i = 0; i <= 25; i++)
    {
        if (array[i] != 1)
        {
            return false;
        }
    }
    return true;
}
