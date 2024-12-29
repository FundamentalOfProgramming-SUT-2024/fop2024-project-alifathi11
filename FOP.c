// bug in score table
// bug in login

#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "menus.h"
#include <time.h>

void initializeRandom() 
{
    srand(time(NULL));
}

void display_text(const char *text);

typedef struct {
    int x;
    int y;
} pair;
typedef struct {
    int y;
    int x;
    int width;
    int height;
    pair door;
} room;

room rooms[6];
int rooms_count = 0;

int main() 
{
    initscr();             
    keypad(stdscr, TRUE);    
    noecho();                
    curs_set(0); 
    load_players();
    signup();
    if (game_menu())
    {
        //new_game();
    }
    else 
    {
        //saved_game();
    }

    endwin();


}

int new_game()
{
    create_rooms();
    display_rooms();
}

void create_rooms()
{
    for (int i = 0; i < 6; i++)
    {
        int x, y, width, height;
        while (check_overlapping() == 0)
        {
            x = get_rand_x();
            y = get_rand_y();
            width = get_rand_width();
            height = get_rand_height();
        }

        rooms[rooms_count].x = x;
        rooms[rooms_count].y = y;
        rooms[rooms_count].width = width;
        rooms[rooms_count].height = height;

        rooms_count++;
    }

    return;
}

// check_overlapping()
// get_rand_x()
// get_rand_y()
// get_rand_width()
// get_rand_height()

void display_rooms()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = rooms[i].x; j < rooms[i].x + rooms[i].width; j++)
        {
            mvaddch(rooms[i].y, j, '_');
        }
        for (int j = rooms[i].x; j < rooms[i].x + rooms[i].width; j++)
        {
            mvaddch(rooms[i].y + rooms[i].height, j, '_');
        }
        for (int j = rooms[i].y; j < rooms[i].y + rooms[i].height; j++)
        {
            mvaddch(j, rooms[i].x, '|');
        }
        for (int j = rooms[i].y; j < rooms[i].y + rooms[i].height; j++)
        {
            mvaddch(j, rooms[i].x + rooms[i].width, '|');
        }

        mvaddch(rooms[i].y, rooms[i].x, '+');

        for (int i = rooms[i].y + 1; i < rooms[i].y - 1; i++)
        {
            for (int j = rooms[i].x + 1; j < rooms[i].x - 1; j++)
            {
                mvaddch(i, j, '.');
            }
        }
    }
    return;
}

void display_text(const char *text) // must be changed
{
    // Initialize ncurses mode
    initscr();
    noecho();
    cbreak();

    // Get screen dimensions
    int screen_height, screen_width;
    getmaxyx(stdscr, screen_height, screen_width);

    // Create a new window covering the entire screen
    WINDOW *win = newwin(screen_height, screen_width, 0, 0);
    box(win, 0, 0); // Add a border around the window

    // Display the text in the top-left corner of the window
    mvwprintw(win, 1, 1, "%s", text);

    // Refresh the window to show the content
    wrefresh(win);

    // Wait for user input before exiting
    getch();

    // Clean up
    delwin(win);
    endwin();
}