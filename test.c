#include <ncurses.h>
#include <curses.h>
#include <ncurses/curses.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>

// Define map dimensions
#define MAP_WIDTH 10
#define MAP_HEIGHT 10

int main()
{
    // Initialize ncurses and set up wide character support
    setlocale(LC_ALL, "");
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    // Define map with Unicode characters
    wchar_t map[MAP_HEIGHT][MAP_WIDTH] = 
    {
        {L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0'},
        {L'\u25A0', L'.', L'.', L'.', L'.', L'.', L'.', L'.', L'.', L'\u25A0'},
        {L'\u25A0', L'.', L'\u25A1', L'\u25A1', L'\u25A1', L'\u25A1', L'.', L'\u25A0', L'.', L'\u25A0'},
        {L'\u25A0', L'.', L'.', L'.', L'.', L'\u25A1', L'.', L'.', L'.', L'\u25A0'},
        {L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0'},
        {L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0'},
        {L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0'},
        {L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0'},
        {L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0'},
        {L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0', L'\u25A0'}
    };

    // Display map using mvaddwstr for wide characters
    for (int i = 0; i < MAP_HEIGHT; i++) 
    {
        for (int j = 0; j < MAP_WIDTH; j++) 
        {
            // Create a wide string for each map character
            wchar_t str[2] = {map[i][j], L'\0'};  // Null-terminated wide string
            mvaddwstr(i, j, str);  // Use mvaddwstr to display the wide string
        }
    }

    // Refresh to show the output
    refresh();

    // Wait for user input before exiting
    getch();

    // Clean up ncurses
    endwin();
    return 0;
}
