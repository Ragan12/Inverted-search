
#include<stdio.h>      // Standard input/output functions
#include"struct.h"     // Structure definitions and global hash table

// Function to save the inverted index into a file
void save_function()
{
    // Ask user for output file name
    printf("Enter the output file name\n");
    char store_file[100];
    scanf("%s", store_file);

    // Open file in write mode
    FILE *fp = fopen(store_file, "w");
    if(fp == NULL)
    {
        printf("save_file not opened\n");
        return;
    }

    // Traverse all hash table indices (0–25)
    for(int i = 0; i < 26; i++)
    {
        // Get the word list at current index
        word_node *temp = hash_table[i];

        // Skip if no words at this index
        if(temp == NULL)
            continue;

        // Traverse word nodes at this index
        while(temp != NULL)
        {
            // Write index, word, and number of files
            fprintf(fp, "#%d;", i);
            fprintf(fp, "%s;", temp->word);
            fprintf(fp, "%d;", temp->file_count);

            // Traverse file list for this word
            file_node *temp1 = temp->fhead;
            while(temp1 != NULL)
            {
                // Write file name and word frequency
                fprintf(fp, "%s;", temp1->filename);
                fprintf(fp, "%d;", temp1->count);
                temp1 = temp1->next;
            }

            // Mark end of one word entry
            fprintf(fp, "#\n");

            // Move to next word node
            temp = temp->next;
        }
    }

    // Close the file after saving
    fclose(fp);
}
