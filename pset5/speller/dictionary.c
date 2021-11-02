 // Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
const unsigned int N = 101;

unsigned int hash_code;

unsigned int word_count = 0;
// Hash table - array of node pointers
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // obtainins the hash value to find the bucket in the array of pointers table
    hash_code = hash(word);
    // setting the node n pointer to the address of the bucket at table[hash_value]
    node *n = table[hash_code];
    // As we traverse through that linked list the end is signified but the next pointer of the node being NULL
    while(n != NULL)
    {
        // Comparing words regardless of case
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }
        // If the word was not found then we move on to the next word in the linked list. Sets the current address of n to whatever address next pointing to
        n = n -> next;
    }
    return false;

}

// Hashes word to a number
//source: http://www.cse.yorku.ca/~oz/hash.html
//sdbm this algorithm was created for sdbm (a public-domain reimplementation of ndbm)
unsigned int hash(const char *word)
{


  // TODO
    unsigned long hash = 5381;
    int c;

    while ((c = tolower(*word++))) //setting c to lowercase and THEN pointer at char word is iterated.
    {
        // << means left shifting meaning that the bit value is increasing by the power of 2
        // hash << 6 = hash * 2^6
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    return hash % N;

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO

    //opening a file and creating File pointer
    FILE* dict = fopen(dictionary, "r");
    if(dict == NULL)
    {
        return false;
    }

    //Creating a char array to store the word where we assume the maximum length is LENGTH
    char value[LENGTH + 1];

    while(fscanf(dict, "%s", value) != EOF)
    {
        //creating a node pointer to hold the word and its next pointer for the creation of the linked list
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        //obtaining the hash number from the hash function
        hash_code = hash(value);

        //copying the characters in value to char array in the node n pointer member word
        strcpy(n -> word, value);

        //Setting the next pointer in n to be the head pointer of table
        n -> next = table[hash_code];

        //Setting the head pointer to now point to n.
        table[hash_code] = n;

        word_count++;

        // free(n);
    }
    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if(word_count > 0)
    {
        return word_count;
    }
    return 0;

}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Iterating through each of the table head pointers
    for (int i = 0; i < N; i++)
    {
        //Setting the cursor to the table head pointer at table[i]
        node *cursor = table[i];

        //cursor -> next could be null so when the address of cursor becomes NULL i.e. 0x00 then we exit the loop
        while (cursor != NULL)
        {
            //tmp now points to where cursor is pointing to the node.
            node *tmp = cursor;
            //cursor now moves to point to the next element
            cursor = cursor -> next;
            // Since tmp is pointing to the previous node it frees that node.
            free(tmp);
        }
        free(cursor);
        //When i =  N-1 that means it is at the last table head pointer and cursor is at the end of the linked list at that last table head pointer.
        if (i == N-1 && cursor == NULL)
        {
            return true;
        }
    }

    return false;
}
