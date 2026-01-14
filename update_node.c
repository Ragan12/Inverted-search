
#include<stdio.h>      // Standard input/output functions
#include<stdlib.h>     // malloc, atoi
#include<string.h>     // string handling functions
#include "struct.h"    // Structure definitions and hash table
#define HASH_SIZE 26   // Number of hash table indexes (a–z)

// Function to update the inverted index from a saved file
void update_node()
{
    char filename[50];

    // Ask user for the saved index file name
    printf("enter the file name\n");
    scanf("%49s", filename);

    // Open the file in read mode
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("file not opened\n");
        return;
    }

    char index_str[50];
    char file_count_str[50];
    char word[50];

    // Read each word entry from the saved file
    while(fscanf(fp, "#%[^;];%[^;];%[^;];",
                 index_str, word, file_count_str) == 3)
    {
        // Create a new word node
        word_node *new = malloc(sizeof(word_node));
        if(new == NULL)
        {
            printf("update_node not created\n");
            fclose(fp);
            return;
        }

        // Initialize word node pointers
        new->next = NULL;
        new->fhead = NULL;

        // Convert index and file count from string to integer
        int index = atoi(index_str);
        int file_count = atoi(file_count_str);

        // Validate index range
        if(index < 0 || index >= HASH_SIZE)
        {
            printf("invalid index\n");
            free(new);
            fclose(fp);
            return;
        }

        // Validate file count
        if(file_count <= 0)
        {
            printf("invalid file count\n");
            free(new);
            fclose(fp);
            return;
        }

        // Store word and number of files
        strcpy(new->word, word);
        new->file_count = file_count;

        // Insert the word node into the hash table
        if(hash_table[index] == NULL)
        {
            hash_table[index] = new;
        }
        else
        {
            word_node *temp = hash_table[index];
            while(temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = new;
        }

        // Read file-wise data for this word
        for(int i = 0; i < file_count; i++)
        {
            char file_name_str[50];
            char freq_str[50];

            // Read file name and frequency
            if(fscanf(fp, " %[^;];%[^;];",
                      file_name_str, freq_str) != 2)
            {
                printf("file entry read error\n");

                // Free allocated file nodes
                file_node *t = new->fhead;
                while(t != NULL)
                {
                    file_node *next = t->next;
                    free(t);
                    t = next;
                }
                free(new);
                fclose(fp);
                return;
            }

            // Create a new file node
            file_node *fnew = malloc(sizeof(file_node));
            if(fnew == NULL)
            {
                printf("file_node not created\n");

                file_node *t = new->fhead;
                while(t != NULL)
                {
                    file_node *next = t->next;
                    free(t);
                    t = next;
                }
                free(new);
                fclose(fp);
                return;
            }

            // Initialize file node
            fnew->next = NULL;
            fnew->count = atoi(freq_str);
            strcpy(fnew->filename, file_name_str);

            // Attach file node to the word node
            if(new->fhead == NULL)
            {
                new->fhead = fnew;
            }
            else
            {
                file_node *temp = new->fhead;
                while(temp->next != NULL)
                {
                    temp = temp->next;
                }
            }
        }
    }
}

