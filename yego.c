#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

// Declare global variable for the number of todos
extern int tLength;

// Define a Todo structure to hold todo details
extern struct Todo
{
    char title[50];       // Stores the title of the todo (up to 50 characters)
    char createdAt[50];   // Stores the creation timestamp of the todo
    _Bool isCompleted;    // Boolean flag to indicate if the todo is completed
} todos[20];              // Array to store up to 20 todos

// Function to print all todos in a formatted table
void printAllTodo()
{
    // Print the table header with borders
    printf("+----+-------------------------------------+--------------+-------------+\n");
    printf("| ID |            Todo Title               |  Created at  |  Completed  |\n");
    printf("+----+-------------------------------------+--------------+-------------+\n");

    // Loop through all todos (up to tLength)
    for (int i = 0; i < tLength; i++)
    {
        // Set text style based on completion status
        if (todos[i].isCompleted)
        {
            printf("\033[10m");   // Use normal text for completed todos
        }
        else
        {
            printf("\033[1m");    // Use bold text for incomplete todos
        }

        // Print a row for the current todo
        // %3d: ID (1-based, padded to 3 characters)
        // %-35s: Title (left-aligned, 35 characters wide)
        // %-12s: Created at (left-aligned, 12 characters wide)
        // Conditional for Completed column: shows "❌ No" or "✅ Yes"
        printf("|%3d | %-35s | %-12s | %-13s |\n", 
               i + 1, 
               todos[i].title, 
               todos[i].createdAt, 
               (!todos[i].isCompleted) ? " ❌  No  " : " ✅  Yes ");
        
        // Print the table row separator
        printf("+----+-------------------------------------+--------------+-------------+\n");
    }
}