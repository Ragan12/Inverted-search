
#include<stdio.h>      // Standard input/output functions
#include<string.h>     // String comparison functions
#include <ctype.h>     // tolower function
#include"struct.h"     // Structure definitions and hash table

// Function to search a word in the inverted index
void search_word(char *word)
{
    // Convert first character of word to lowercase
    char ch = tolower(word[0]);

    // Validate that the word starts with an alphabet
    if (ch < 'a' || ch > 'z')
    {
        printf("Invalid word\n");
        return;
    }

    // Calculate hash table index
    int index = ch - 'a';

    // Get the word list at the calculated index
    word_node *temp = hash_table[index];

    // If no words are present at this index
    if(temp == NULL)
    {
        printf("No data found\n");
        return;
    }

    // Traverse the linked list to search the word
    while(temp != NULL)
    {
        // Compare stored word with input word
        if(strcmp(temp->word, word) == 0)
        {
            printf("DATA found\n");
            return;
        }
        temp = temp->next;
    }

    // If word is not found in the list
    printf("data no found\n");
}

