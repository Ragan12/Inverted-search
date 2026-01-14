
#include <stdlib.h>    // malloc, free
#include <ctype.h>     // tolower
#include <string.h>    // string functions
#include <stdio.h>     // file operations
#include "struct.h"    // user-defined structures and prototypes

// Function to read a file and insert words into the inverted index
void insert_node_data(char *filename)
{
    // Open the input file in read mode
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("File not found: %s\n", filename);
        return;
    }

    char word[50];   // Buffer to store each word from file

    // Read words one by one from the file
    while(fscanf(fp, "%s", word) != EOF)
    {
        // Convert first character to lowercase
        char ch = tolower(word[0]);

        // Ignore words that do not start with alphabets
        if(ch < 'a' || ch > 'z')
            continue;

        // Calculate hash index (0–25)
        int index = ch - 'a';

        // Traverse the linked list at this index
        word_node *temp = hash_table[index];
        int found = 0;

        // Check if the word already exists
        while(temp != NULL)
        {
            if(strcmp(temp->word, word) == 0)
            {
                // Word found: increment file count
                temp->file_count++;

                // Update file-wise frequency
                update_file_name(temp, filename);

                found = 1;
                break;
            }
            temp = temp->next;
        }

        // If word not found, create a new word node
        if(!found)
        {
            word_node *new = malloc(sizeof(word_node));

            // Store the word
            strcpy(new->word, word);

            // Initialize word count
            new->file_count = 1;

            // Initialize file list and link pointers
            new->fhead = NULL;
            new->next = hash_table[index];

            // Insert at beginning of hash table list
            hash_table[index] = new;

            // Add file information for this word
            update_file_name(new, filename);
        }
    }

    // Close the file after processing
    fclose(fp);
}
