#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

// Global variable to track the number of todos in the array
int tLength = 0;  // Initialized to 0, incremented as todos are added, updated when reading from file

// Global file pointer for handling the todos.bin file
FILE *fp;  // Used for reading from and writing to the binary file "todos.bin"

// Define a structure to represent a single todo item
struct Todo
{
    char title[50];      // Stores the todo title, up to 49 characters plus null terminator
    char createdAt[50];  // Stores the creation timestamp, formatted as a string
    _Bool isCompleted;   // Boolean flag indicating whether the todo is marked as completed
} todos[20];             // Array to store up to 20 todo items

// Function to save all todos from the array to a binary file
void saveToFile()
{
    // Open "todos.bin" in binary write mode ("w"), which overwrites the file
    fp = fopen("todos.bin", "w");
    if (!fp)  // Check if file opening failed (e.g., due to permissions or disk issues)
    {
        printf("Can't save your todo\n");  // Notify user if the file cannot be opened
        return;  // Exit the function to avoid further operations
    }
    
    // Iterate through all todos in the array (up to tLength)
    for (size_t i = 0; i < tLength; i++)
    {
        // Write the current todo structure to the file as binary data
        // Each todo is written as a single block of sizeof(struct Todo) bytes
        fwrite(&todos[i], sizeof(struct Todo), 1, fp);
    }
    
    // Close the file to ensure data is flushed and resources are freed
    fclose(fp);
}

// Helper function to calculate the number of todos stored in the file
void getFileSize()
{
    // Move the file pointer to the end of the file to determine its size
    fseek(fp, 0L, SEEK_END);
    
    // Get the file size in bytes by retrieving the current position of the file pointer
    unsigned long size = ftell(fp);
    
    // Move the file pointer back to the start for subsequent reading operations
    fseek(fp, 0L, SEEK_SET);
    
    // Calculate the number of todos by dividing the total file size by the size of one Todo structure
    tLength = size / sizeof(struct Todo);  // Updates global tLength with the count of todos
}

// Function to read todos from the binary file into the todos array
void readFromFile()
{
    // Open "todos.bin" in binary read mode ("r")
    fp = fopen("todos.bin", "r");
    if (!fp)  // Check if file opening failed (e.g., file doesn't exist)
    {
        printf("We are not able to find any todos file\n");  // Notify user of the issue
        return;  // Exit the function to avoid further operations
    }
    
    // Calculate the number of todos in the file by analyzing its size
    getFileSize();
    
    // Iterate through the number of todos (as determined by tLength)
    for (size_t i = 0; i < tLength; i++)
    {
        // Read one todo structure from the file into the todos array at index i
        // Each read operation retrieves sizeof(struct Todo) bytes
        fread(&todos[i], sizeof(struct Todo), 1, fp);
    }
    
    // Close the file to free resources
    fclose(fp);
}