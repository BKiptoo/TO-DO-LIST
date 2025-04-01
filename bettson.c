#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

// Global variable to keep track of number of todos
int tLength = 0;
// Global file pointer for file operations
FILE *fp;

// Structure definition for a Todo item
struct Todo
{
    char title[50];        /**Todo title with max length of 50 characters**/
    char createdAt[50];    // Creation timestamp with max length of 50 characters
    _Bool isCompleted;     // Boolean flag to mark todo completion status
} todos[20];              // Array to store up to 20 todo items

// Function to save todos to a binary file
void saveToFile()
{
    fp = fopen("todos.bin", "w");
    if (!fp)
    {
        printf("Can't save your todo\n");
    }
    else
    {
        // Loop through all todos in the array
        for (size_t i = 0; i < tLength; i++)
        {
            // Write each todo structure to the file
            // fwrite takes: pointer to data, size of each element, number of elements, file pointer
            fwrite(&todos[i], sizeof(struct Todo), 1, fp);
        }
        fclose(fp);
    }
}

// Function to calculate the number of todos in the file
void getFileSize()
{
    // Move file pointer to end of file
    fseek(fp, 0L, SEEK_END);
    unsigned int long size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    tLength = size / sizeof(struct Todo);
}

// Function to read todos from a binary file
void readFromFile()
{
    // Open file in read mode (binary)
    fp = fopen("todos.bin", "r");
    // Check if file opening was successful
    if (!fp)
    {
        // Print error message if file can't be found/opened
        printf("We are not able to find any todos file\n");
    }
    else
    {
        // Calculate the number of todos in the file
        getFileSize();
        // Loop through all todos based on calculated length
        for (size_t i = 0; i < tLength; i++)
        {
            // Read each todo structure from the file into the todos array
            // fread takes: pointer to storage, size of each element, number of elements, file pointer
            fread(&todos[i], sizeof(struct Todo), 1, fp);
        }
        // Close the file after reading is complete
        fclose(fp);
    }
}