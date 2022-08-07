// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// 26 letters >> next phase 26*26 // hash function to be adjusted
// impact on check time performance
const unsigned int N = 677;

// Hash table
node *table[N];

// dictionary word counter
unsigned int DICTSIZE = 0;

bool DICTLOADED = false;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // go trough lincked lists to find the word
    // go trough table[hcode] linked list
    unsigned hcode = hash(word);
    if (table[hcode] != NULL)
    {
        node *cursor = table[hcode];
        while (cursor != NULL)
        {
            if (strcasecmp(word, cursor->word) == 0)
            {
                return true;
            }
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // inspired from Doug Lloyyd lecture on Hash Tables;
    // case-insensitive adaptation;
    // hash code based on division method - modular arithmetic
    // use of a prime number table size;
    int sum = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (isupper(word[i]) == 0)
        {
            sum += word[i];
        }
        else
        {
            sum += word[i] + 32;
        }
    }
    return sum % N;
    //return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    // Open dict file
    FILE *fileDict = fopen(dictionary, "r");
    // check if fileDict is open
    if (fileDict == NULL)
    {
        printf("Could not open dict file.\n");
        return false;
    }

    // fulfill the table pointer with NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // word buffer
    char word[LENGTH + 1];

    while (fscanf(fileDict, "%s", word) != EOF) // will return EOF??
    {
        node *n = malloc(sizeof(node));
        // node check
        if (n == NULL)
        {
            fclose(fileDict);
            printf("Not enough memmory???\n");
            return false;
        }

        // node init
        strcpy(n->word, word);
        n->next = NULL;

        // hash code
        unsigned hcode = hash(word);
        if (table[hcode] == NULL)
        {
            table[hcode] = n;
            DICTSIZE ++;
        }
        else
        {
            n->next = table[hcode];
            table[hcode] = n;
            DICTSIZE++;
        }
        // word buffer reset
        memset(word, 0, LENGTH + 1);

    }
    fclose(fileDict);
    DICTLOADED = true;
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // return DICTSIZE if file dictionary is open
    if (DICTLOADED)
    {
        return DICTSIZE;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // unload dictionary from heap
    if (DICTLOADED)
    {
        for (int i = 0; i < N; i++)
        {
            if (table[i] != NULL)
            {
                node *cursor = table[i];
                while (cursor != NULL)
                {
                    node *tmp = cursor->next;
                    free(cursor);
                    cursor = tmp;
                }
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}
