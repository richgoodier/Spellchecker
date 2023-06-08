// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <cs50.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
// DONE!!!
const unsigned int N = 1000;
unsigned int word_count = 0;

// Hash table
node *table[N];


// Returns true if word is in dictionary, else false
// DONE!!!
bool check(const char *word)
{
    // TODO
    if (strlen(word) > LENGTH)
    {
        return true;
    }

    // Hash
    int word_hash = hash(word);
    node *current = table[word_hash];
    while (current != NULL)
    {
        if (strcasecmp(current->word, word) == 0)
        {
            return true;
        }
        current = current->next;
    }

    return false;
}




// Hashes word to a number
// DONE!!!
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int x = 0;
    for (int i = 0; i < LENGTH + 1; i++)
    {
        if (word[i] == '\0')
        {
            return (x % N);
        }
        else
        {
            x = 23 * tolower(word[i]) + x;
        }
    }
    printf("Error\n");
    return false;
}




// Loads dictionary into memory, returning true if successful, else false
// DONE!!!
bool load(const char *dictionary)
{
    // TODO
    // Try to open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open dictionary.\n");
        return false;
    }

    // Prepare to search for words
    int index = 0, ascii_value = 0;
    char word_search[LENGTH + 1];

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Find each word in text
    char c;
    while (fread(&c, sizeof(char), 1, file))
    {
        // Allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // Append character to word
            word_search[index] = c;

            // Hashing
            ascii_value = 23 * c + ascii_value;

            index++;
        }

        // We must have found a whole word
        else if (index > 0)
        {
            // Terminate current word
            word_search[index] = '\0';

            // Track the number of words found
            word_count++;

            // Mod the Hash
            int hash_number = (ascii_value % N);

            //create node with malloc
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                printf("Could not allocate memory.\n");
                return false;
            }
            //fill node with word and NULL pointer
            strcpy(n->word, word_search);
            n->next = NULL;

            //Link node
            if (table[hash_number] == NULL)
            {
                table[hash_number] = n;
            }
            else
            {
                n->next = table[hash_number];
                table[hash_number] = n;
            }

            // Prepare for next word
            index = 0;
            ascii_value = 0;
        }
    }

    // Check whether there was an error
    if (ferror(file))
    {
        fclose(file);
        printf("Error reading dictionary.\n");
        return false;
    }

    // Close text
    fclose(file);
    return true;
}




// Returns number of words in dictionary if loaded, else 0 if not yet loaded
// DONE!!!
unsigned int size(void)
{
    return word_count;
}



// Unloads dictionary from memory, returning true if successful, else false
// DONE!!!
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *temp = table[i];
        node *cursor = table[i];
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(temp);
            temp = cursor;
        }
    }
    return true;
}