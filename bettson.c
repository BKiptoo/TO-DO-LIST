#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

int tLength = 0;
FILE *fp;

struct Todo
{
    char title[50];
    char createdAt[50];
    _Bool isCompleted;
} todos[20];

void saveToFile()
{
    // Open "todos.bin" in binary write mode ("w"), which overwrites the file
    fp = fopen("todos.bin", "w");
    if (!fp)  // Check if file opening failed (e.g., due to permissions or disk issues)
    {
        printf("Can't save your todo\n");  // Notify user if the file cannot be opened
        return;  // Exit the function to avoid further operations
    }
    else
    {
        for (size_t i = 0; i < tLength; i++)
        {
            fwrite(&todos[i], sizeof(struct Todo), 1, fp);
        }
        fclose(fp);
    }
}

void getFileSize()
{
    fseek(fp, 0L, SEEK_END);
    
    // Get the file size in bytes by retrieving the current position of the file pointer
    unsigned long size = ftell(fp);
    
    // Move the file pointer back to the start for subsequent reading operations
    fseek(fp, 0L, SEEK_SET);
    
    // Calculate the number of todos by dividing the total file size by the size of one Todo structure
    tLength = size / sizeof(struct Todo);  // Updates global tLength with the count of todos
}

void readFromFile()
{
    fp = fopen("todos.bin", "r");
    if (!fp)
    {
        printf("We are not able to find any todos file\n");
    }
    else
    {
        getFileSize();
        for (size_t i = 0; i < tLength; i++)
        {
            fread(&todos[i], sizeof(struct Todo), 1, fp);
        }
        fclose(fp);
    }
}