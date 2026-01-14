
#include<stdio.h>      // Standard input/output functions
#include<string.h>     // String handling functions
#include"struct.h"     // Structure definitions and hash table

// Function to display the entire inverted index
void display()
{
    // Traverse each index of the hash table (0–25)
    for(int i = 0; i < 26; i++)
    {
        // Get the word list at the current index
        word_node *temp = hash_table[i];

        // If no words exist at this index, skip it
        if(temp == NULL)
            continue;

        // Traverse the linked list of word nodes
        while(temp != NULL)
        {
            // Print the word and number of files it appears in
            printf("%s ", temp->word);
            printf("%d ", temp->file_count);

            // Traverse the file list associated with this word
            file_node *temp1 = temp->fhead;
            while(temp1 != NULL)
            {
                // Print file name and word frequency in that file
                printf("%s ", temp1->filename);
                printf("%d ", temp1->count);
                temp1 = temp1->next;
            }

            // Move to the next line after printing one word entry
            printf("\n");

            // Move to the next word node
            temp = temp->next;
        }
    }
}
