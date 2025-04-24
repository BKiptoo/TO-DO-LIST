
# Todo List Application

## Overview

This is a console-based Todo List application written in C. It allows users to manage their tasks by adding, deleting, marking as complete, and displaying todos. The application persists todo data in a binary file (`todos.bin`) to retain tasks between sessions. The program features a simple text-based interface with a formatted table display and supports up to 20 todos.

## Features

- **Add Todos**: Create new todos with a title and automatic timestamp.
- **Mark as Complete**: Toggle the completion status of a todo.
- **Delete Todos**: Remove todos from the list.
- **Display Todos**: View all todos in a formatted table showing ID, title, creation time, and completion status.
- **Persistent Storage**: Todos are saved to and loaded from a binary file (`todos.bin`).
- **Interactive Menu**: User-friendly menu for selecting actions (Add, Delete, Complete, Quit).
- **First-Time Setup**: Welcomes new users and prompts for the first todo if no data exists.

## Prerequisites

To compile and run this application, you need:

- A C compiler (e.g., `gcc`).
- A Unix-like system (Linux, macOS) or Windows with a compatible terminal (e.g., MSYS2, WSL).
- Standard C libraries (included with most compilers).

## Compilation and Running

1. **Save the Code**:
   Save the provided C code as `todo_app.c`.

2. **Compile the Program**:
   Use a C compiler like `gcc` to compile the code:
   ```bash
    gcc -o todo_app bettson.c yego.c ian.c ramon.c 
   ```

3. **Run the Program**:
   Execute the compiled binary:
   ```bash
   ./todo_app
   ```

   On Windows, use:
   ```bash
   todo_app.exe
   ```

## File Structure

- `todo_app.c`: The main C source file containing all functionality.
- `todos.bin`: A binary file (created automatically) to store todo data persistently.

## Usage

1. **Starting the Application**:
   - On first run, the program checks for `todos.bin`. If it doesn't exist, it displays a welcome message and prompts for a new todo.
   - If `todos.bin` exists, it loads existing todos and displays them.

2. **Main Menu**:
   After displaying the todo list, the program presents a menu:
   ```
   Type 'A' to add, 'D' to delete & 'C' to mark complete or 'Q' to quit
   >>
   ```
   - Press `A` to add a new todo.
   - Press `D` to delete a todo by ID.
   - Press `C` to mark a todo as complete by ID.
   - Press `Q` to quit the program.
   - Invalid inputs prompt an error and redisplay the menu.

3. **Adding a Todo**:
   - Enter a title (up to 49 characters, including spaces).
   - The program automatically records the current date and time (format: `day/month hour:minute`).

4. **Marking as Complete**:
   - Enter the ID of the todo (shown in the table, starting from 1).
   - Invalid IDs display an error message.

 jogos de casino para celular5. **Deleting a Todo**:
   - Enter the ID of the todo to delete.
   - Invalid IDs display an error message.

6. **Viewing Todos**:
   - Todos are displayed in a table with columns for ID, Title, Created at, and Completed status.
   - Completed todos are shown in normal text, while incomplete ones are bolded.
   - The Completed column shows `✅ Yes` or `❌ No`.

## Example Output

```
+----+-------------------------------------+--------------+-------------+
| ID |            Todo Title               |  Created at  |  Completed  |
+----+-------------------------------------+--------------+-------------+
|  1 | Buy groceries                       | 24/4 14:30   | ❌  No      |
|  2 | Finish homework                     | 24/4 15:00   | ✅  Yes     |
+----+-------------------------------------+--------------+-------------+
Type 'A' to add, 'D' to delete & 'C' to mark complete or 'Q' to quit
>>
```

## Notes for Developers

- **Code Structure**:
  - The program uses a `struct Todo` to store each todo's title, creation timestamp, and completion status.
  - The `todos` array holds up to 20 todos, tracked by the global `tLength` variable.
  - Functions are modular, handling specific tasks like file I/O, user input, and display.

- **File Handling**:
  - Todos are stored in `todos.bin` as binary data, with each todo occupying `sizeof(struct Todo)` bytes.
  - The `saveToFile` function overwrites the file with the current `todos` array.
  - The `readFromFile` function loads todos by calculating the file size and reading structures.

- **Improvements**:
  - Add input validation for todo titles (e.g., prevent empty titles).
  - Support editing existing todos.
  - Increase the maximum number of todos or make it dynamic.
  - Add error handling for file corruption or incomplete reads.

- **Known Limitations**:
  - The program assumes valid user input for most operations (e.g., no buffer overflow checks for `scanf`).
  - ANSI escape codes (`\033[1m`, `\033[10m`) for text styling may not work on all terminals (e.g., Windows CMD).
  - The binary file format is not portable across systems with different endianness or struct padding.


## Full Code in one Snippet
```bash
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
    fp = fopen("todos.bin", "w");
    if (!fp)
    {
        printf("Can't save your todo\n");
        return;
    }
    
    for (size_t i = 0; i < tLength; i++)
    {
        fwrite(&todos[i], sizeof(struct Todo), 1, fp);
    }
    
    fclose(fp);
}

void getFileSize()
{
    fseek(fp, 0L, SEEK_END);
    unsigned long size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    tLength = size / sizeof(struct Todo);
}

void readFromFile()
{
    fp = fopen("todos.bin", "r");
    if (!fp)
    {
        printf("We are not able to find any todos file\n");
        return;
    }
    
    getFileSize();
    
    for (size_t i = 0; i < tLength; i++)
    {
        fread(&todos[i], sizeof(struct Todo), 1, fp);
    }
    
    fclose(fp);
}

void addTodo()
{
    char userInput[50];
    printf("Type your todo \n>> ");
    scanf(" %[^\n]s", userInput);
    strncpy(todos[tLength].title, userInput, 50);

    char todoTime[50];
    struct tm cTime;
    time_t timeS = time(NULL);
    localtime_r(&timeS, &cTime);
    snprintf(todoTime, 50, "%i/%i %i:%i", cTime.tm_mday, cTime.tm_mon + 1, cTime.tm_hour, cTime.tm_min);
    strcpy(todos[tLength].createdAt, todoTime);

    todos[tLength].isCompleted = false;
    tLength++;
}

void markAsComplete()
{
    int todoId;
    printf("Enter the ID of todo \n>>");
    scanf("%d", &todoId);
    todoId--;
    if (todoId < 0 || todoId >= tLength)
    {
        printf("Invalid todo id 😑\n");
    }
    else
    {
        todos[todoId].isCompleted = true;
        printf("Todo marked as completed \n");
    }
}

void deleteTodo()
{
    int todoId;
    printf("Enter the ID of todo \n>>");
    scanf("%d", &todoId);
    if (todoId <= 0 || todoId > tLength)
    {
        printf("Invalid todo id 😑\n");
    }
    else
    {
        todoId--;
        memmove(todos + todoId, todos + todoId + 1, (tLength - todoId - 1) * sizeof(*todos));
        tLength--;
        printf("Your todo has been deleted 😵\n");
    }
}

void printAllTodo()
{
    printf("+----+-------------------------------------+--------------+-------------+\n");
    printf("| ID |            Todo Title               |  Created at  |  Completed  |\n");
    printf("+----+-------------------------------------+--------------+-------------+\n");

    for (int i = 0; i < tLength; i++)
    {
        if (todos[i].isCompleted)
        {
            printf("\033[10m");
        }
        else
        {
            printf("\033[1m");
        }

        printf("|%3d | %-35s | %-12s | %-13s |\n", 
               i + 1, 
               todos[i].title, 
               todos[i].createdAt, 
               (!todos[i].isCompleted) ? " ❌  No  " : " ✅  Yes ");
        
        printf("+----+-------------------------------------+--------------+-------------+\n");
    }
}

void ShowOptions()
{
    char userChoice;
    printf("Type 'A' to add, 'D' to delete & 'C' to mark complete or 'Q' to quit\n>>");
    userChoice = getchar();
    userChoice = toupper(userChoice);
    getchar();
    switch (userChoice)
    {
    case 'A':
        addTodo();
        break;
    case 'D':
        deleteTodo();
        break;
    case 'C':
        markAsComplete();
        break;
    case 'Q':
        exit(0);
        break;
    default:
        printf("Command not found 😓\n");
        ShowOptions();
        break;
    }
    saveToFile();
    printAllTodo();
    getchar();
    ShowOptions();
}

void isThisFirstTime()
{
    if (access("todos.bin", F_OK) != -1)
    {
        readFromFile();
        printAllTodo();
        ShowOptions();
    }
    else
    {
        printf("Welcome to the Great Todo App\n");
        addTodo();
        saveToFile();
        printAllTodo();
        ShowOptions();
    }
}

int main()
{
    system("clear||@cls");
    printf("\033[32;1m");
    isThisFirstTime();
    return 0;
}
```
## License

This project is provided as-is for educational purposes. Feel free to modify and distribute it as needed.