// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// // Represents a node in a hash table
// typedef struct node
// {
//     char word[LENGTH + 1];
//     struct node *next;
// }
// node;

// // TODO: Choose number of buckets in hash table
// const unsigned int N = 26;

// // Hash table
// node *table[N];

// // Returns true if word is in dictionary, else false
// bool check(const char *word)
// {
//     unsigned int location = hash(word);

//     node *temp = table[location];

//     while (temp != NULL)
//     {
//         if (strcasecmp(word, temp->word) == 0)
//             return true;

//         temp = temp->next;
//     }

//     return false;
// }

// // Hashes word to a number
// unsigned int hash(const char *word)
// {
//     // TODO: Improve this hash function
//     return toupper(word[0]) - 'A';
// }

// // Loads dictionary into memory, returning true if successful, else false
// bool load(const char *dictionary)
// {
//     for (int i = 0; i < N; i++)
//     {
//         table[i] = NULL; // initialize pointers to null
//     }

//     FILE *fp = fopen(dictionary, "r");

//     if (fp == NULL)
//     {
//         printf("Unable to open dictionary with name: %s\n", dictionary);
//         return false;
//     }

//     char buffer[LENGTH + 2];

//     while(fgets(buffer, LENGTH + 2, fp) != NULL)
//     {
//         int length = strlen(buffer);
//         if (buffer[length - 1] == '\n')
//             buffer[length - 1] = '\0';


//         unsigned int location = hash(buffer);

//         node *new_node = malloc(sizeof(node));
//         strcpy(new_node->word, buffer);
//         new_node->next = table[location];
//         table[location] = new_node;
//     }

//     return true;
// }

// // Returns number of words in dictionary if loaded, else 0 if not yet loaded
// unsigned int size(void)
// {
//     int word_count = 0;

//     for (int i = 0; i < N; i++)
//     {
//         node *tmp = table[i];

//         while (tmp != NULL)
//         {
//             word_count++;
//             tmp = tmp->next;
//         }
//     }

//     printf("Word Count: %i\n", word_count);
//     return word_count;
// }

// void free_node(node *p)
// {
//     if (p == NULL)
//         return;

//     free_node(p->next);
//     free(p);
// }

// // Unloads dictionary from memory, returning true if successful, else false
// bool unload(void)
// {
//     for (int i = 0; i < N; i++)
//     {
//         free_node(table[i]);
//     }
//     return true;
// }

#define NUMBER_OF_CHARACTERS 26

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[NUMBER_OF_CHARACTERS];
}
node;

// Trie root
node *root = NULL;

node *create_node()
{
    node *new_node = malloc(sizeof(node));
    new_node->is_word = false;

    for (int i = 0; i < NUMBER_OF_CHARACTERS; i++)
    {
        new_node->children[i] = NULL;
    }

    return new_node;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *temp = root;

    if (temp == NULL)
        return false;

    for (const char *copy = word; *copy != '\0'; copy++)
    {
        unsigned int location = hash(copy);

        if (temp->children[location] == NULL)
            return false;

        temp = temp->children[location];
    }

    return temp->is_word;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return *word == '\'' ? 26 : toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *fp = fopen(dictionary, "r");

    if (fp == NULL)
    {
        printf("Unable to open dictionary with name: %s\n", dictionary);
        return false;
    }

    root = create_node();

    char buffer[LENGTH + 2];

    while(fgets(buffer, LENGTH + 2, fp) != NULL)
    {
        node *temp = root;
    
        int length = strlen(buffer);
        
        if (buffer[length - 1] == '\n')
            buffer[length - 1] = '\0';

        for (char *copy = buffer; *copy != '\0'; copy++)
        {
            unsigned int location = hash(copy);

            if (temp->children[location] == NULL)
            {
                node *new_node = create_node();
                temp->children[location] = new_node;
            }

            temp = temp->children[location];
        }

        temp->is_word = true;
    }

    return true;
}

void check_is_word(node *current, int *word_count)
{
    if (current == NULL)
        return;

    if (current->is_word)
        (*word_count)++;

    for (int i = 0; i < NUMBER_OF_CHARACTERS; i++)
    {
        check_is_word(current->children[i], word_count);
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int word_count = 0;
    check_is_word(root, &word_count);
    return word_count;
}

void free_node(node *p)
{
    if (p == NULL)
        return;

    for (int i = 0; i < NUMBER_OF_CHARACTERS; i++)
    {
        free_node(p->children[i]);
    }
    free(p);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    free_node(root);
    return true;
}
