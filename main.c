
/*
NAME : Ragan P
DATE : 15:12:2025
TOPIC : INVERTED SEARCH PROJECT
DESCRIPTION : This project implements an inverted search system in C that indexes words 
              from multiple text files using a hash table.It allows efficient word searching,
              file-wise frequency counting, and supports saving and updating the index.
*/
#include<stdio.h>      // Standard input/output functions
#include<string.h>     // String handling functions
#include <stdlib.h>    // malloc, free
#include"struct.h"     // User-defined structures and function declarations

// Global hash table (auto-initialized to NULL)
word_node *hash_table[26];

int main(int argc,char *argv[])
{
    int option;                 // Menu option chosen by user
    char find_word[50];          // Word to search

    // Check if input files are provided from command line
    if(argc < 2)
    {
        printf("invalid command\n");
        return 1;
    }

    int index_created = 0;   // Flag to check whether index is created
    int saved = 0;           // Flag to check whether index is saved

    // Infinite loop for menu-driven program
    while(1)
    {
        printf("1.Create node\n2.Search\n3.Display\n4.Update node\n5.Save\n6.EXIT\n");
        scanf("%d",&option);

        switch(option)
        {
            case 1:
                // Create a linked list of input file names
                main_file *head = NULL;
                main_file *temp;

                // Read all filenames passed through command line
                for(int i = 1; i < argc; i++)
                {
                    char *ext = strrchr(argv[i], '.');

                    // Consider only .txt files
                    if(ext && strcmp(ext, ".txt") == 0)
                    {
                        main_file *new = malloc(sizeof(main_file));
                        strcpy(new->filename, argv[i]);
                        new->next = NULL;

                        // Insert file node into linked list
                        if(head == NULL)
                        {
                            head = new;
                            temp = new;
                        }
                        else
                        {
                            temp->next = new;
                            temp = new;
                        }
                    }
                }

                // Read each file and create inverted index
                main_file *curr = head;
                while(curr != NULL)
                {
                    insert_node_data(curr->filename);
                    curr = curr->next;
                }

                index_created = 1;   // Mark index as created
                printf("Index created successfully\n");
                break;

            case 2:
                // Search operation allowed only after index creation
                if(index_created == 0)
                {
                    printf("Please create index first (Option 1)\n");
                    break;
                }
                printf("enter the word to search\n");
                scanf("%s", find_word);
                search_word(find_word);
                break;

            case 3:
                // Display operation allowed only after index creation
                if(index_created == 0)
                {
                    printf("Please create index first (Option 1)\n");
                    break;
                }
                display();
                break;

            case 4:
                // Update operation allowed only after index creation
                if(index_created == 0)
                {
                    printf("Please create index first (Option 1)\n");
                    break;
                }
                // Update allowed only after saving index
                if(saved == 0)
                {
                    printf("Please first save the file and update\n");
                    break;
                }
                update_node();
                break;

            case 5:
                // Save operation allowed only after index creation
                if(index_created == 0)
                {
                    printf("Please create index first (Option 1)\n");
                    break;
                }
                save_function();
                saved = 1;   // Mark index as saved
                break;

            case 6:
                // Exit the program
                printf("Exiting Succssfully\n");
                return 0;
            default:
                printf("Invalid choice option\n");
                return 0;
        }
    }
}
