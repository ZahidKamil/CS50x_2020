#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



const unsigned int N = 51;

unsigned int hash(const char *word)
{


  // TODO
    long sum = 0, mul = 1;
    for (int i = 0; word[i] != '\0'; i++)
    {
        //Hashing 2 bytes at a time.
        mul = (i % 2 == 0) ? 1 : mul * 256;
        sum += word[i] * mul;
    }
    return (int)(labs(sum) % N);
}

int main(void)
{
    char word[10] = "brother";
    int val = hash(word);
    printf("Value is: %i\n", val);
}



        // Initialising the array to NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    //opening the file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char wordlen[LENGTH + 1];
    //scaning the current buffer
    while (fscanf(file, "%s", wordlen) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
        //storing the word in the node
        strcpy(new_node->word, wordlen);
        new_node->next = NULL;

        //some hash function which gives out value
        unsigned long index = hash(wordlen);

        if (table[index] != NULL)
        {
            //the new node's next is pointing to the element node present in on the hash
            new_node->next = table[index];
        }
        //the new starting element on the hash table is the new node
        table[index] = new_node;
        word_count++;
    }
    fclose(file);
    return true;