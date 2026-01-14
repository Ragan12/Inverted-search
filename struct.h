
// Structure to store file information for each word
typedef struct file_node
{
    char filename[50];          // Name of the file
    int count;                  // Number of times the word appears in this file
    struct file_node *next;     // Pointer to next file node
} file_node;

// Structure to store list of input files (used during index creation)
typedef struct main_file
{
    char filename[50];          // Input file name
    struct main_file *next;     // Pointer to next file in the list
} main_file;

// Structure to store word information in the inverted index
typedef struct word_node
{
    char word[30];              // Word stored in the index
    int file_count;             // Number of files containing this word
    file_node *fhead;           // Pointer to linked list of file nodes
    struct word_node *next;     // Pointer to next word node
} word_node;

// Global hash table to store word nodes (26 indexes for a–z)
extern word_node *hash_table[26];

// Function declarations used across the project
void insert_node_data(char *filename);                  // Create index from input files
void update_file_name(word_node *wnode, char *filename);// Update file-wise frequency
void search_word(char *word);                            // Search a word in the index
void display();                                          // Display entire index
void save_function();                                    // Save index to file
void update_node();                                      // Update index from saved file

