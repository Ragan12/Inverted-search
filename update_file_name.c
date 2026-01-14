
#include"struct.h"     // Structure definitions
#include<stdlib.h>     // malloc
#include<string.h>     // string handling functions

// Function to update file-wise information for a given word
void update_file_name(word_node *wnode, char *filename)
{
    // Get the head of the file list for the word
    file_node *temp = wnode->fhead;

    // If no file nodes exist, create the first file node
    if(temp == NULL)
    {
        file_node *new = malloc(sizeof(file_node));
        strcpy(new->filename, filename);
        new->count = 1;          // First occurrence in this file
        new->next = NULL;

        // Attach the new file node to the word node
        wnode->fhead = new;
        return;
    }

    file_node *prev = NULL;

    // Traverse the file list to check if file already exists
    while(temp != NULL)
    {
        // If the file name matches, increment frequency
        if(strcmp(temp->filename, filename) == 0)
        {
            temp->count++;
            return;
        }

        // Move to next node
        prev = temp;
        temp = temp->next;
    }

    // If file not found, create a new file node at the end
    file_node *new = malloc(sizeof(file_node));
    strcpy(new->filename, filename);
    new->count = 1;          // First occurrence in this file
    new->next = NULL;

    // Link the new file node to the list
    prev->next = new;
}