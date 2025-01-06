// bug in score table
// bug in login

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <time.h>
#include <locale.h>
#include <wchar.h>
#include "menus.h"


typedef struct {
    int x;
    int y;
} pair;

pair windows[10];
pair doors[10];
pair pillars[10]; 
int window_index = 0, door_index = 0, pillar_index = 0;

typedef struct {
    int y;
    int x;
    int width;
    int height;
} room;

typedef struct {
    int x;
    int y;
    int health;
} character;

character main_char;

room rooms[10];



void initializeRandom();
void create_rooms();
int get_rand_x();
int get_rand_y();
int get_rand_width();
int get_rand_height();
int check_overlapping();
void display_rooms();
int new_game();
void start_game();
int possible(int c);
void connect_rooms(room room1, room room2);
void create_paths();
void display_text(const char *text);
void display_door_window();
void create_door_window();
void create_things();
void display_things();
void edit();
int init_audio();
void close_audio();


int main() 
{
    start_color();
    if (has_colors() == 0) 
    {
        endwin();
        printf("Your terminal does not support color\n");
    }
    setlocale(LC_ALL, "");
    initializeRandom();
    initscr();             
    keypad(stdscr, TRUE);    
    noecho();                
    curs_set(0); 

    if (!init_audio()) 
    {
        printf("Failed to initialize audio!\n");
    }

    Mix_Music *menu_music = Mix_LoadMUS("musics/menu_music.mp3");
    Mix_PlayMusic(menu_music, -1);

    start_menu();
    if (game_menu())
    {
        clear();
        Mix_FreeMusic(menu_music);
        close_audio();
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
    create_rooms();
    create_door_window();
    create_things();
    start_game();
}

void start_game()
{
    int start_room = rand() % 6;
    main_char.x = rooms[start_room].x + rooms[start_room].width / 2;
    main_char.y = rooms[start_room].y + rooms[start_room].height - 2;

    while (1)
    {
        clear();
        display_rooms();
        //display_door_window();
        create_paths();
        display_things();
        edit();
        refresh();
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
            case 'e':
                if (possible(c))
                {
                    main_char.x++; main_char.y--;
                    break;
                }
            case 'q':
                if (possible(c))
                {
                    main_char.x--; main_char.y--;
                    break;
                }
            case 'x':
                if (possible(c))
                {
                    main_char.x++; main_char.y++;
                    break;
                }
            case 'z':
                if (possible(c))
                {
                    main_char.x--; main_char.y++;
                    break;
                }
        }
    }
    return;
}

int possible(int c)
{
    if (c == 'w' && (mvinch(main_char.y - 1, main_char.x) == '_' || mvinch(main_char.y - 1, main_char.x) == '|' || 
        mvinch(main_char.y - 1, main_char.x) == ' ' || mvinch(main_char.y - 1, main_char.x) == 'o'))
        return 0;
    if (c == 'a' && (mvinch(main_char.y, main_char.x - 1) == '|' || mvinch(main_char.y, main_char.x - 1) == '_' ||
        mvinch(main_char.y, main_char.x - 1) == ' ' || mvinch(main_char.y, main_char.x - 1) == 'o'))
        return 0;
    if (c == 'd' && (mvinch(main_char.y, main_char.x + 1) == '|' || mvinch(main_char.y, main_char.x + 1) == '_' || 
        mvinch(main_char.y, main_char.x + 1) == ' ' || mvinch(main_char.y, main_char.x + 1) == 'o'))
        return 0;
    if (c == 's' && (mvinch(main_char.y + 1, main_char.x) == '_' || mvinch(main_char.y + 1, main_char.x) == '|' ||
        mvinch(main_char.y + 1, main_char.x) == ' ' || mvinch(main_char.y + 1, main_char.x) == 'o'))
        return 0;
    if (c == 'e' && (mvinch(main_char.y - 1, main_char.x + 1) == '_' || mvinch(main_char.y - 1, main_char.x + 1) == '|' ||
        mvinch(main_char.y - 1, main_char.x + 1) == ' ' || mvinch(main_char.y - 1, main_char.x + 1) == 'o'))
        return 0;
    if (c == 'q' && (mvinch(main_char.y - 1, main_char.x - 1) == '_' || mvinch(main_char.y - 1, main_char.x - 1) == '|' ||
        mvinch(main_char.y - 1, main_char.x - 1) == ' ' || mvinch(main_char.y - 1, main_char.x - 1) == 'o'))
        return 0;
    if (c == 'x' && (mvinch(main_char.y + 1, main_char.x + 1) == '_' || mvinch(main_char.y + 1, main_char.x + 1) == '|' ||
        mvinch(main_char.y + 1, main_char.x + 1) == ' ' || mvinch(main_char.y + 1, main_char.x + 1) == 'o'))
        return 0;
    if (c == 'z' && (mvinch(main_char.y + 1, main_char.x - 1) == '_' || mvinch(main_char.y + 1, main_char.x - 1) == '|' ||
        mvinch(main_char.y + 1, main_char.x - 1) == ' ' || mvinch(main_char.y + 1, main_char.x - 1) == 'o'))
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
int get_rand_y() { return 5 + rand() % 13; } 
int get_rand_width() { return 10 + rand() % 10; } 
int get_rand_height() { return 5 + rand() % 10; }

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
        if (!(x + width <= x1 + 1 || x >= x2 - 1 || y + height <= y1 + 1 || y >= y2 - 1)) 
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

void create_paths()
{
    for (int i = 0; i < 5; i++)
    {   
        connect_rooms(rooms[i], rooms[i + 1]);
    }
    connect_rooms(rooms[5], rooms[0]);
}


void connect_rooms(room room1, room room2) 
{
    int x1 = room1.x + room1.width / 2;
    int y1 = room1.y + room1.height / 2;
    int x2 = room2.x + room2.width / 2;
    int y2 = room2.y + room2.height / 2;
    int x, y;

    for (x = (x1 < x2 ? x1 : x2); x <= (x1 > x2 ? x1 : x2); x++) 
    {
        if (mvinch(y1, x) != '.' && mvinch(y1, x) != '|' && mvinch(y1, x) != '_' && mvinch(y1, x) != '+') mvaddch(y1, x, '#');
        if (mvinch(y1, x) == '|' || mvinch(y1, x) == '_') mvaddch(y1, x, '+');
    }
    refresh();

    for (y = (y1 < y2 ? y1 : y2); y <= (y1 > y2 ? y1 : y2); y++) 
    {
        if (mvinch(y, x2) != '.' && mvinch(y, x2) != '|' && mvinch(y, x2) != '_' && mvinch(y, x2) != '+') mvaddch(y, x2, '#');
        if (mvinch(y, x2) == '|' || mvinch(y, x2) == '_') mvaddch(y, x2, '+');
    }
    refresh();
}

void create_door_window()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = rooms[i].y + 2; j < rooms[i].y + rooms[i].height - 2; j++)
        {
            if (mvinch(j, rooms[i].x + 1) == '.' && mvinch(j, rooms[i].x - 1) == '.')
            {
                int p = rand() % 2;
                if (p == 1)
                {
                    windows[window_index].y = j; windows[window_index].x = rooms[i].x; window_index++;
                    break;
                }
                // door
            }
        }

        for (int j = rooms[i].y + 2; j < rooms[i].y + rooms[i].height - 2; j++)
        {
            if (mvinch(j, rooms[i].x + rooms[i].width + 1) == '.' && mvinch(j, rooms[i].x + rooms[i].width - 1) == '.')
            {
                int p = rand() % 2;
                if (p == 1)
                {
                    windows[window_index].y = j; windows[window_index].x = rooms[i].x + rooms[i].width; window_index++;
                    break;
                }
                // door
            }
        }

        for (int j = rooms[i].x + 2; j < rooms[i].x + rooms[i].width - 2; j++)
        {
            if (mvinch(rooms[i].y - 1, j) == '.' && mvinch(rooms[i].y + 1, j) == '.')
            {
                int p = rand() % 2;
                if (p == 1)
                {
                    windows[window_index].y = rooms[i].y; windows[window_index].x = j; window_index++;
                    break;
                }
                //door
            }
        }

        for (int j = rooms[i].x + 2; j < rooms[i].x + rooms[i].width - 2; j++)
        {
            if (mvinch(rooms[i].y + rooms[i].height + 1, j) == '.' && mvinch(rooms[i].y + rooms[i].height - 1, j) == '.')
            {
                int p = rand() % 2;
                if (p == 1)
                {
                    windows[window_index].y = rooms[i].y + rooms[i].height; windows[window_index].x = j; window_index++;
                    break;
                }
                //door
            }
        }
    }
}

void display_door_window()
{
    for (int i = 0; i < window_index; i++)
    {
        mvaddch(windows[i].y, windows[i].x, '=');
    }
    refresh();
}


void create_things()
{
    //pillar
    for (int i = 0; i < 6; i++)
    {
        int p = rand() % 4;
        if (p > 1)
        {
            for (int j = 0; j < p; j++)
            {
                int x = rooms[i].x + rand() % (rooms[i].width - 3) + 2;
                int y = rooms[i].y + rand() % (rooms[i].height - 3) + 2;
                pillars[pillar_index].y = y; pillars[pillar_index].x = x;
                pillar_index++;
            }
        }
    }
}

void display_things()
{
    const char *mace = "⚒";
    const char *dagger = "🗡";
    const char * magic_wand = "🪄";
    const char *arrow = "⬻";
    const char *sword = "⚔";
    
    // pillar
    for (int i = 0; i < pillar_index; i++)
    {
        mvaddch(pillars[i].y, pillars[i].x, 'o');
    }
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





///////////////////////////// edit
void edit()
{
    // edit pillars
    for (int i = 1; i < 34; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            if (mvinch(i, j) == 'o' && (mvinch(i + 1, j) != '.' && mvinch(i + 1, j) != '_' && mvinch(i + 1, j) != '|') &&
                (mvinch(i, j + 1) != '.' && mvinch(i, j + 1) != '_' && mvinch(i, j + 1) != '|') &&
                (mvinch(i, j - 1) != '.' && mvinch(i, j - 1) != '_' && mvinch(i, j - 1) != '|') &&
                (mvinch(i - 1, j) != '.' && mvinch(i - 1, j) != '_' && mvinch(i - 1, j) != '|'))
                {
                    mvaddch(i, j, ' ');
                }
        }
    }

    // edit doors
}





///////////////////////////////// music
////////////////////////////////////////