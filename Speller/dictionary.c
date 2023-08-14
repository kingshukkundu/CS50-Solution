#include <stdbool.h>

#include "dictionary.h"

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

node *table[SIZE];

// Global count of words inserted
unsigned int dsize;

void vacate_list(node *head);

// Returns true if word is in dictionary else false.
bool check(const char *word)
{
    // Hash the word received
    unsigned int hcode = hash(word);

    // Search through the hash table to find it
    node *trav = table[hcode];
    while (trav != NULL)
    {
        // Case-insensitive comparison
        if (strcasecmp(trav->word, word) == 0)
        {
            return true;
        }

        // Advance the traversal pointer
        trav = trav->next;
    }

    // Must not have found anything
    return false;
}

// Hash function, adapted from djb2 http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    unsigned int hash = 5381;
    int c;
    while ((c = (tolower(*word++))))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % SIZE;
}

// Loads dictionary into memory. Returns true if successful else false.
bool load(const char *dictionary)
{
    // Initialize dictionary size to 0
    dsize = 0;

    // attempt to open our file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }

    // Iterate through our file, one word at a time
    while (true)
    {
        // Create space for a new hash table node
        node *newnode = malloc(sizeof(node));
        if (newnode == NULL)
        {
            return false;
        }

        // Read the next string from the source dictionary into the new node
        if (fscanf(source, "%s", newnode->word) == EOF)
        {
            // If we've reached the end of the file, break out
            free(newnode);
            break;
        }

        // Hash that string to obtain a hash value
        unsigned int hcode = hash(newnode->word);

        // Insert into the hash table at that location, at the front of the chain
        newnode->next = table[hcode];
        table[hcode] = newnode;

        // Increment our word counter
        dsize++;
    }

    // Close the dictionary file, success!
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded.
unsigned int size(void)
{
    return dsize;
}

// Unloads dictionary from memory. Returns true if successful else false.
bool unload(void)
{
    // Iterate over every element of our hash table, freeing its list
    for (int i = 0; i < SIZE; i++)
        vacate_list(table[i]);

    // Barring a fail of the free() function, no possible way to return false
    return true;
}

// Recursively deletes a linked list
void vacate_list(node *head)
{
    // If the list is empty, nothing else to do
    if (head == NULL)
    {
        return;
    }

    // Free the next element in the chain, then free this one
    vacate_list(head->next);
    free(head);
}
