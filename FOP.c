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

void initializeRandom();
void create_rooms();
int get_rand_x();
int get_rand_y();
int get_rand_width();
int get_rand_height();
int check_overlapping();
void display_rooms();
int new_game();
void create_doors();
void display_doors();
void start_game();
int possible(int c);
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
    pair door[3];
    int door_count;
} room;

typedef struct {
    int x;
    int y;
    int health;
} character;

character main_char;

room rooms[10];

int main() 
{
    initscr();             
    keypad(stdscr, TRUE);    
    noecho();                
    curs_set(0); 
    load_players();
    signup();

    initializeRandom();
    if (game_menu())
    {
        clear();
        new_game();
    }
    else 
    {
        //saved_game();
    }

    endwin();


}

void initializeRandom() 
{
    srand(time(NULL));
}

int new_game()
{
    for (int i; i < 10; i++)
        rooms[i].door_count = 0;  
    create_rooms();
    display_rooms();
    create_doors();
    display_doors();
    // create_paths();
    // display_paths();
    start_game();
}

void start_game()
{
    int start_room = rand() % 6;
    main_char.x = rooms[start_room].x + rooms[start_room].width / 2;
    main_char.y = rooms[start_room].y + rooms[start_room].height - 1;

    while (1)
    {
        clear();
        display_rooms();
        display_doors();
        // display_things();
        // display_paths();
        mvaddch(main_char.y, main_char.x, 'a');
        int c = getch();
        switch (c)
        {
            case 'w':
                if (possible(c))
                {
                    main_char.y--;
                    break;
                }
                
            case 's':
                if (possible(c))
                {
                    main_char.y++;
                    break;
                }
            case 'a':
                if (possible(c))
                {
                    main_char.x--;
                    break;
                }
            case 'd':
                if (possible(c))
                {
                    main_char.x++;
                    break;
                }
            //other cases
            // handle simultenous keys
        }
    }
    return;
}

int possible(int c)
{
    if (c == 'w' && (mvinch(main_char.y - 1, main_char.x) == '_' || mvinch(main_char.y - 1, main_char.x) == '|'))
        return 0;
    if (c == 'a' && (mvinch(main_char.y, main_char.x - 1) == '|' || mvinch(main_char.y, main_char.x - 1) == '_'))
        return 0;
    if (c == 'd' && (mvinch(main_char.y, main_char.x + 1) == '|' || mvinch(main_char.y, main_char.x + 1) == '_'))
        return 0;
    if (c == 's' && (mvinch(main_char.y + 1, main_char.x) == '_' || mvinch(main_char.y + 1, main_char.x) == '|' ))
        return 0;
    return 1;
}

void create_rooms()
{
    for (int i = 0; i < 6; i++)
    {
        int x, y, width, height;
        do 
        {
            x = get_rand_x();
            y = get_rand_y();
            width = get_rand_width();
            height = get_rand_height();
        } while (check_overlapping(x, y, width, height, i) == 0);

        rooms[i].x = x;
        rooms[i].y = y;
        rooms[i].width = width;
        rooms[i].height = height;
    }

    return;
}

int get_rand_x() { return 10 + rand() % 150; } 
int get_rand_y() { return 5 + rand() % 15; } 
int get_rand_width() { return 8 + rand() % 10; } 
int get_rand_height() { return 4 + rand() % 10; }

int check_overlapping(int x, int y, int width, int height, int n)
{
    if (n == 0)
    {
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        int x1 = rooms[i].x, y1 = rooms[i].y;
        int x2 = x1 + rooms[i].width, y2 = y1 + rooms[i].height;
        if (!(x + width < x1 - 10 || x > x2 + 10 || y + height < y1 - 5 || y > y2 + 5)) 
        {
            return 0;
        }
    }
    return 1; 
}

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
            mvaddch(rooms[i].y + rooms[i].height - 1, j, '_');
        }
        for (int j = rooms[i].y; j < rooms[i].y + rooms[i].height; j++)
        {
            mvaddch(j, rooms[i].x, '|');
        }
        for (int j = rooms[i].y; j < rooms[i].y + rooms[i].height; j++)
        {
            mvaddch(j, rooms[i].x + rooms[i].width, '|');
        }

        refresh();

        for (int j = rooms[i].y + 1; j < rooms[i].y + rooms[i].height - 1; j++) 
        {
            for (int k = rooms[i].x + 1; k < rooms[i].x + rooms[i].width; k++) 
            {
                mvaddch(j, k, '.');
            }
        }

        refresh();
    }

    refresh();
    return;
}


void create_doors()
{
    for (int i = 0; i < 6; i++)
    {
        int n = rand() % 3 + 1; 
        for (int j = 0; j < n; j++) 
        {
            int p = rand() % 2;
            int q = rand() % 2;

            if (p == 0) 
            {  
                int y_door = rooms[i].y + 1 + (rand() % (rooms[i].height - 2)); 
                if (q == 0)
                {
                    (rooms[i].door[j]).y = y_door;
                    (rooms[i].door[j]).x = rooms[i].x;
                    rooms[i].door_count++;
                }
                else
                {
                    (rooms[i].door[j]).y = y_door;
                    (rooms[i].door[j]).x = rooms[i].x + rooms[i].width; 
                    rooms[i].door_count++;
                }
            }
            else
            {
                int x_door = rooms[i].x + 1 + (rand() % (rooms[i].width - 2)); 
                if (q == 0)
                {
                    (rooms[i].door[j]).y = rooms[i].y;
                    (rooms[i].door[j]).x = x_door;
                    rooms[i].door_count++;
                }
                else
                {
                    (rooms[i].door[j]).y = rooms[i].y + rooms[i].height - 1;
                    (rooms[i].door[j]).x = x_door;
                    rooms[i].door_count++;
                }
            }
        }
    }
    refresh();
}

void display_doors()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < rooms[i].door_count; j++)
        {
            mvaddch((rooms[i].door[j]).y, (rooms[i].door[j]).x, '+');
        }
    }
    return;
}


// void create_paths()
// {

// }

// void display_paths()
// {

// }




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