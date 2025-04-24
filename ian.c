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

// Function prototypes for todo management (implemented elsewhere)
void saveToFile();        // Saves todos to a file
void readFromFile();      // Reads todos from a file
void addTodo();           // Adds a new todo to the list
void printAllTodo();      // Prints all todos
void markAsComplete();    // Marks a todo as completed
void deleteTodo();        // Deletes a todo from the list

// Function to display menu options and handle user input
void ShowOptions()
{
    char userChoice;      // Variable to store the user's menu choice
    // Prompt user to select an action
    printf("Type 'A' to add, 'D' to delete & 'C' to mark complete or 'Q' to quit\n>>");
    userChoice = getchar();              // Read the user's input
    userChoice = toupper(userChoice);    // Convert input to uppercase for case-insensitive comparison
    getchar();                           // Consume the newline character left in the input buffer
    // Switch based on user choice
    switch (userChoice)
    {
    case 'A':
        addTodo();    // Call function to add a new todo
        break;
    case 'D':
        deleteTodo(); // Call function to delete a todo
        break;
    case 'C':
        markAsComplete(); // Call function to mark a todo as complete
        break;
    case 'Q':
        exit(0);      // Exit the program
        break;
    default:
        // Handle invalid input and prompt again
        printf("Command not found 😓\n");
        ShowOptions(); // Recursive call to show options again
        break;
    }
    saveToFile();      // Save the updated todos to the file
    printAllTodo();    // Display all todos
    getchar();         // Wait for user to press Enter before showing options again
    ShowOptions();     // Show the menu again for further actions
}

// Function to check if the app is running for the first time
void isThisFirstTime()
{
    // Check if the todos.bin file exists (indicating previous usage)
    if (access("todos.bin", F_OK) != -1)
    {
        readFromFile();    // Load existing todos from file
        printAllTodo();    // Display all todos
        ShowOptions();     // Show the menu for user interaction
    }
    else
    {
        // If file doesn't exist, it's the first run
        printf("Welcome to the Great Todo App\n");
        addTodo();         // Prompt user to add the first todo
        saveToFile();      // Save the todo to the file
        printAllTodo();    // Display all todos
        ShowOptions();     // Show the menu for further actions
    }
}

// Main function - entry point of the program
int main()
{
    system("clear||@cls");    // Clear the terminal screen (works on Unix or Windows)
    printf("\033[32;1m");     // Set terminal text color to green (ANSI escape code)
    isThisFirstTime();        // Start the app by checking if it's the first run
    return 0;                 // Exit the program (though not reached due to ShowOptions loop)
}