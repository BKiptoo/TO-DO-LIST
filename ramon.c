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

// Function to add a new todo to the list
void addTodo()
{
    char userInput[50];   // Buffer to store the user's input for the todo title
    printf("Type your todo \n>> ");   // Prompt user to enter the todo title
    scanf("%[^\n]s", userInput);      // Read input until newline (allows spaces in title)
    // Copy the input to the todo's title field, ensuring it doesn't exceed 50 characters
    strncpy(todos[tLength].title, userInput, 50);

    char todoTime[50];    // Buffer to store the formatted timestamp
    struct tm cTime;      // Structure to hold the broken-down local time
    time_t timeS = time(NULL);   // Get the current time in seconds since epoch
    localtime_r(&timeS, &cTime); // Convert to local time, storing in cTime
    // Format the timestamp as "day/month hour:minute" (e.g., "24/4 14:30")
    snprintf(todoTime, 50, "%i/%i %i:%i", cTime.tm_mday, cTime.tm_mon + 1, cTime.tm_hour, cTime.tm_min);
    // Copy the formatted timestamp to the todo's createdAt field
    strcpy(todos[tLength].createdAt, todoTime);

    todos[tLength].isCompleted = false;   // Initialize the todo as not completed
    tLength++;                            // Increment the todo count
}

// Function to mark a todo as completed
void markAsComplete()
{
    int todoId;   // Variable to store the user-specified todo ID
    printf("Enter the ID of todo \n>>");   // Prompt user to enter the todo ID
    scanf("%d", &todoId);                  // Read the ID from user input
    todoId--;                              // Adjust ID to 0-based index (user enters 1-based)
    // Check if the ID is valid (within bounds of existing todos)
    if (todoId < 0 || todoId >= tLength)
    {
        printf("Invalid todo id 😑\n");    // Inform user of invalid ID
    }
    else
    {
        // Mark the specified todo as completed
        todos[todoId].isCompleted = true;
        printf("Todo marked as completed \n");   // Confirm the action
    }
}

// Function to delete a todo from the list
void deleteTodo()
{
    int todoId;   // Variable to store the user-specified todo ID
    printf("Enter the ID of todo \n>>");   // Prompt user to enter the todo ID
    scanf("%d", &todoId);                  // Read the ID from user input
    // Check if the ID is valid (within bounds of existing todos)
    if (todoId <= 0 || todoId > tLength)
    {
        printf("Invalid todo id 😑\n");    // Inform user of invalid ID
    }
    else
    {
        todoId--;   // Adjust ID to 0-based index (user enters 1-based)
        // Shift all todos after the deleted one to fill the gap
        memmove(todos + todoId, todos + todoId + 1, (tLength - todoId - 1) * sizeof(*todos));
        tLength--;  // Decrement the todo count
        printf("Your todo has been deleted 😵\n");   // Confirm the deletion
    }
}