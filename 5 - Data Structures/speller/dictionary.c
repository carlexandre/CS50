// Implements a dictionary's functionality

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 5000;

// Hash table
node *table[N];

// Word's counter
int counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int ind = hash(word);

    node *head = table[ind];

    for(node *ptr = head; ptr != NULL; ptr = ptr->next)
    {
        if (strcasecmp(ptr->word,word) == 0)
            return true;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int sum = 0;
    int i = 0;

    while (strcmp(&word[i], "\0") != 0)
    {
        sum += tolower(word[i]);
        i++;
    }

    return sum;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
        return false;

    char w[LENGTH+1];

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    while (fscanf(source, "%s", w) != EOF)
    {
        counter++;

        node *n = malloc(sizeof(node));
        if (n == NULL)
            return 1;

        int ind = hash(w);

        strcpy(n->word, w);
        n->next = table[ind];
        table[ind] = n;
    }

    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *htable = table[i];

        while (htable != NULL)
        {
            node *ptr = htable;
            htable = htable->next;
            free(ptr);
        }
    }
    return true;
}
