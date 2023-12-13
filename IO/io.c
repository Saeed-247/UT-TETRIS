#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "../settings.h"
#include "io.h"

#define IO_INPUT_BUFFER_SIZE 1000

int escaped;
static char IO_inputBuffer[IO_INPUT_BUFFER_SIZE];
static int IO_inputBufferIndex = 0;
static int IO_windowHeght, IO_windowWidth;
static HANDLE hOut;

void IO_init() {
    // Get the Win32 handle representing standard output.
    // This generally only has to be done once, so we make it static.
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    
    escaped = 0;

    // making stdout buffer bigger
    int new_size = 64 * 4096;
    setvbuf(stdout, NULL, _IOFBF, new_size);
}

/*
    Reading all user inputs to IO buffer
*/
void IO_updateInput() {
    if (kbhit()) {
        IO_inputBuffer[++IO_inputBufferIndex] = getch();
    }
}

/*
    This function returns the last available character in IO buffer
    If the IO buffer is empty '-' will be returned
*/
char IO_getInput() {
    char ret = '-';
    if (IO_inputBufferIndex) 
        ret = IO_inputBuffer[IO_inputBufferIndex];
    IO_inputBufferIndex = 0;
    return ret;
}


/*
    This function clears the console screen using WIN32 functions
*/
void cls()
{   
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD topLeft = { 0, 0 };

    /*
    stdout uses a buffer to batch writes to the underlying console.
    We need to flush that to the console because we're circumventing
    stdout entirely; after we clear the console, we don't want
    stale buffered text to randomly be written out.
    */
    fflush(stdout);

    // Figure out the current width and height of the console window
    if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
        // Handle failure!
        abort();
    }
    IO_windowHeght = csbi.dwSize.Y;
    IO_windowWidth = csbi.dwSize.X;
    DWORD length = csbi.dwSize.X * csbi.dwSize.Y;
    
    DWORD written;

    // Flood-fill the console with spaces to clear it
    FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

    // Reset the attributes of every character to the default.
    // This clears all background colour formatting, if any.
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

    // Move the cursor back to the top left for the next sequence of writes
    SetConsoleCursorPosition(hOut, topLeft);
}

/*
    This function gets a 2D char array prints it in the center of console screen
*/
void IO_render(char frame[FRAME_HEIGHT][FRAME_WIDTH]) {
    // clear the console
    cls();

    int topMargin = max(0, (IO_windowHeght - FRAME_HEIGHT) / 2);
    int leftMargin = max(0, (IO_windowWidth - FRAME_WIDTH) / 2);
    for (int i = 0; i < topMargin; i++) {
        printf("\n");
    }
    for (int i = 0; i < FRAME_HEIGHT; i++) {
        for (int i = 0; i < leftMargin; i++) {
            printf(" ");
        }
        printf("%.*s\n", FRAME_WIDTH, frame[i]);
    }
    fflush(stdout);
}