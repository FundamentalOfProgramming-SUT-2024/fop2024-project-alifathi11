#include <ncursesw/ncurses.h>
#include <wchar.h>
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
#include <unistd.h>
#include "menus.h"


typedef struct {
    int x;
    int y;
} pair;

pair pillars[10]; 
int pillar_index = 0;


typedef struct {
    int y;
    int x;
    int width;
    int height;
    int theme; // 1 for normal, 2 for enchant, 3 for nightmare
} room;

room rooms[10];

typedef struct {
    int x;
    int y;
} character;

character main_char;
int health = 10;


typedef struct {
    int x;
    int y;
    int type; // 1 for normal 2 for super 3 for magical
} FOOD;

FOOD food[20];
int food_index = 0;
int inventory_food[3];


typedef struct {
    int count;
    int type;
} food_to_show;




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
void update_health();
void spawn_food();
void create_food();
void check_collect_food();
void clear_text();
int inventory();
int show_food();


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
    curs_set(0);  
    create_rooms();
    //create_door_window();
    create_things();
    create_food();
    start_game();
}

void start_game()
{
    for (int i = 0; i < 3; i++) inventory_food[i] = 0;
    int start_room = rand() % 6;
    main_char.x = rooms[start_room].x + rooms[start_room].width / 2;
    main_char.y = rooms[start_room].y + rooms[start_room].height - 2;
    timeout(5000);
    time_t start_time, current_time;
    time(&start_time);
    while (1)
    {
        clear();
        time(&current_time);
        if (difftime(current_time, start_time) >= 5) 
        {
            if (health > 0) 
            {
                health--;
            }
            time(&start_time);
        }
        display_rooms();
        //display_door_window();
        create_paths();
        display_things();
        spawn_food();
        edit();
        update_health();
        check_collect_food();
        refresh();
        mvprintw(main_char.y, main_char.x, "a");
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
            case 'i':
                if (c == 'i') 
                if (inventory()) break;
                
        }
    }
    return;
}

int possible(int c)
{
    if (c == 'w' && ((mvinch(main_char.y - 1, main_char.x) & A_CHARTEXT) == '_' || 
                     (mvinch(main_char.y - 1, main_char.x) & A_CHARTEXT) == '|' || 
                     (mvinch(main_char.y - 1, main_char.x) & A_CHARTEXT) == ' ' || 
                     (mvinch(main_char.y - 1, main_char.x) & A_CHARTEXT) == 'o'))
        return 0;

    if (c == 'a' && ((mvinch(main_char.y, main_char.x - 1) & A_CHARTEXT) == '|' || 
                     (mvinch(main_char.y, main_char.x - 1) & A_CHARTEXT) == '_' || 
                     (mvinch(main_char.y, main_char.x - 1) & A_CHARTEXT) == ' ' || 
                     (mvinch(main_char.y, main_char.x - 1) & A_CHARTEXT) == 'o'))
        return 0;

    if (c == 'd' && ((mvinch(main_char.y, main_char.x + 1) & A_CHARTEXT) == '|' || 
                     (mvinch(main_char.y, main_char.x + 1) & A_CHARTEXT) == '_' || 
                     (mvinch(main_char.y, main_char.x + 1) & A_CHARTEXT) == ' ' || 
                     (mvinch(main_char.y, main_char.x + 1) & A_CHARTEXT) == 'o'))
        return 0;

    if (c == 's' && ((mvinch(main_char.y + 1, main_char.x) & A_CHARTEXT) == '_' || 
                     (mvinch(main_char.y + 1, main_char.x) & A_CHARTEXT) == '|' || 
                     (mvinch(main_char.y + 1, main_char.x) & A_CHARTEXT) == ' ' || 
                     (mvinch(main_char.y + 1, main_char.x) & A_CHARTEXT) == 'o'))
        return 0;

    if (c == 'e' && ((mvinch(main_char.y - 1, main_char.x + 1) & A_CHARTEXT) == '_' || 
                     (mvinch(main_char.y - 1, main_char.x + 1) & A_CHARTEXT) == '|' || 
                     (mvinch(main_char.y - 1, main_char.x + 1) & A_CHARTEXT) == ' ' || 
                     (mvinch(main_char.y - 1, main_char.x + 1) & A_CHARTEXT) == 'o'))
        return 0;

    if (c == 'q' && ((mvinch(main_char.y - 1, main_char.x - 1) & A_CHARTEXT) == '_' || 
                     (mvinch(main_char.y - 1, main_char.x - 1) & A_CHARTEXT) == '|' || 
                     (mvinch(main_char.y - 1, main_char.x - 1) & A_CHARTEXT) == ' ' || 
                     (mvinch(main_char.y - 1, main_char.x - 1) & A_CHARTEXT) == 'o'))
        return 0;

    if (c == 'x' && ((mvinch(main_char.y + 1, main_char.x + 1) & A_CHARTEXT) == '_' || 
                     (mvinch(main_char.y + 1, main_char.x + 1) & A_CHARTEXT) == '|' || 
                     (mvinch(main_char.y + 1, main_char.x + 1) & A_CHARTEXT) == ' ' || 
                     (mvinch(main_char.y + 1, main_char.x + 1) & A_CHARTEXT) == 'o'))
        return 0;

    if (c == 'z' && ((mvinch(main_char.y + 1, main_char.x - 1) & A_CHARTEXT) == '_' || 
                     (mvinch(main_char.y + 1, main_char.x - 1) & A_CHARTEXT) == '|' || 
                     (mvinch(main_char.y + 1, main_char.x - 1) & A_CHARTEXT) == ' ' || 
                     (mvinch(main_char.y + 1, main_char.x - 1) & A_CHARTEXT) == 'o'))
        return 0;

    return 1;
}


void create_rooms()
{
    for (int i = 0; i < 6; i++)
    {
        int x, y, width, height, theme;
        do 
        {
            x = get_rand_x();
            y = get_rand_y();
            width = get_rand_width();
            height = get_rand_height();
            theme = rand() % 100;
        } while (check_overlapping(x, y, width, height, i) == 0);

        rooms[i].x = x;
        rooms[i].y = y;
        rooms[i].width = width;
        rooms[i].height = height;
        if (theme < 30) rooms[i].theme = 2;
        else if (theme >= 30 && theme < 50) rooms[i].theme = 3;
        else rooms[i].theme = 1;
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
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); 
    init_pair(3, COLOR_RED, COLOR_BLACK);    
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    for (int i = 0; i < 6; i++)
    {
        if (rooms[i].theme == 2) attron(COLOR_PAIR(1));
        else if (rooms[i].theme == 3) attron(COLOR_PAIR(2));
        for (int j = rooms[i].x; j < rooms[i].x + rooms[i].width; j++)
        {
            mvprintw(rooms[i].y, j, "_");
        }
        for (int j = rooms[i].x; j < rooms[i].x + rooms[i].width; j++)
        {
            mvprintw(rooms[i].y + rooms[i].height - 1, j, "_");
        }
        for (int j = rooms[i].y; j < rooms[i].y + rooms[i].height; j++)
        {
            mvprintw(j, rooms[i].x, "|");
        }
        for (int j = rooms[i].y; j < rooms[i].y + rooms[i].height; j++)
        {
            mvprintw(j, rooms[i].x + rooms[i].width, "|");
        }
        if (rooms[i].theme == 2) attroff(COLOR_PAIR(1));
        else if (rooms[i].theme == 3) attroff(COLOR_PAIR(2));
        refresh();
        if (rooms[i].theme == 2) attron(COLOR_PAIR(3));
        else if (rooms[i].theme == 3) attron(COLOR_PAIR(4));

        for (int j = rooms[i].y + 1; j < rooms[i].y + rooms[i].height - 1; j++) 
        {
            for (int k = rooms[i].x + 1; k < rooms[i].x + rooms[i].width; k++) 
            {
                mvaddch(j, k, '.');
            }
        }
        if (rooms[i].theme == 2) attroff(COLOR_PAIR(3));
        else if (rooms[i].theme == 3) attroff(COLOR_PAIR(4));
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
        char ch = mvinch(y1, x) & A_CHARTEXT;
        if (ch != '.' && ch != '|' && ch != '_' && ch != '+') 
            mvaddch(y1, x, '#');
        else if (ch == '|' || ch == '_') 
            mvaddch(y1, x, '+');
    }
    refresh();

    for (y = (y1 < y2 ? y1 : y2); y <= (y1 > y2 ? y1 : y2); y++) 
    {
        char ch = mvinch(y, x2) & A_CHARTEXT;
        if (ch != '.' && ch != '|' && ch != '_' && ch != '+') 
            mvaddch(y, x2, '#');
        else if (ch == '|' || ch == '_') 
            mvaddch(y, x2, '+');
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
    // init_pair(10 ,COLOR_YELLOW, COLOR_BLACK);
    // attron(COLOR_PAIR(10));
    // for (int i = 0; i < pillar_index; i++)
    // {
    //     mvprintw(pillars[i].y, pillars[i].x, "o");
    // }
    // attroff(COLOR_PAIR(10));
}


void display_text(const char *text) // must be changed
{
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(0));
    mvprintw(2, 160, "%s", text);
    attroff(COLOR_PAIR(0));
    refresh();
}

void clear_text()
{
    mvprintw(2, 160, "                             ");
    refresh();
}

void update_health()
{
    mvprintw(1, 3, "HEALTH: ");
    init_pair(7, COLOR_GREEN, COLOR_BLACK);
    init_pair(8, COLOR_RED, COLOR_BLACK);
    if (health >= 5) attron(COLOR_PAIR(7));
    else attron(COLOR_PAIR(8));
    int x = 11;
    for (int i = 0; i < health; i++)
    {
       mvprintw(1, x++ ,"🎔 ");
    }
    if (health >= 5) attroff(COLOR_PAIR(7));
    else attroff(COLOR_PAIR(8));
}




///////////////////////////// edit
void edit()
{
    // edit pillars
    for (int i = 0; i < 34; i++)
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


void create_food()
{
    for (int i = 0; i < 6; i++)
    {
        int p = rand() % 7;
        if (p == 0 || p == 1 || p == 2 || p == 3)
        {
            int y = rooms[i].y + 1 + (rand() % (rooms[i].height - 3));
            int x = rooms[i].x + 1 + (rand() % (rooms[i].width - 3));
            food[food_index].y = y; food[food_index].x = x;
            if (p == 0 || p == 1) food[food_index++].type = 1;
            else if (p == 2) food[food_index++].type = 2;
            else food[food_index++].type = 3;
        }
    }
}


void spawn_food()
{
    const char *food1 = "🥫"; //normal and bad food 
    const char *food2 = "🍥"; // super food!
    const char *food3 = "🏺"; //magic food
    for (int i = 0; i < food_index; i++)
    {
        if (food[i].x != 0)
        {
            if (food[i].type == 1) mvprintw(food[i].y, food[i].x, "🥫");
            else if (food[i].type == 2) mvprintw(food[i].y, food[i].x, "🍥");
            else mvprintw(food[i].y, food[i].x, "🏺");
        }
    }
}


void check_collect_food()
{
    for (int i = 0; i < food_index; i++)
    {
        if (main_char.y == food[i].y && (main_char.x == food[i].x || main_char.x == food[i].x + 1))
        {
            display_text("PRESS C TO COLLECT THE FOOD");
            int c = getch();
            if (c == 'c')
            {
                inventory_food[food[i].type - 1]++;
                food[i].y = 0; food[i].x = 0;
                clear_text();
                display_text("             COLLECTED!");
                refresh();
                napms(750);
                display_text("PRESS I TO SEE YOUR INVENTORY");
                refresh();
                int v = getch();
                if (v == 'i')
                {
                    clear_text();
                    inventory();
                }
            }
        }
    }
}

int inventory() 
{
    int startx, starty, width, height;
    WINDOW *inv_win;
    
    height = LINES - 2;
    width = COLS - 4;   
    starty = 1;           
    startx = 2;           

    inv_win = newwin(height, width, starty, startx);

    box(inv_win, 0, 0);

    mvwprintw(inv_win, 0, (width - 10) / 2, " INVENTORY ");

    mvwprintw(inv_win, 2, 2, "1. FOOD");
    mvwprintw(inv_win, 3, 2, "2. WEAPONS");
    mvwprintw(inv_win, 4, 2, "3. ENCHANTS");
    mvwprintw(inv_win, 5, 2, "4. KEYS");


    wrefresh(inv_win);

    refresh();
    int c = getch();
    switch(c)
    {
        case '1':
            wclear(inv_win);
            wrefresh(inv_win);
            return show_food();
            break;
        default:
            return 1;
            break;
        // case '2':
        //     //show_weapon();
        //     break;
        // case '3':
        //     //show_keys();
        //     break;
        // default:
        //     break;
    }

    delwin(inv_win);

}


int show_food()
{
    int startx, starty, width, height;
    WINDOW *food_win;
    
    height = LINES - 2;
    width = COLS - 4;   
    starty = 1;           
    startx = 2;           

    food_win = newwin(height, width, starty, startx);

    box(food_win, 0, 0);

    mvwprintw(food_win, 0, (width - 8) / 2, " FOOD ");
    wrefresh(food_win);

    food_to_show fts[3];
    for (int i = 0; i < 3; i++) fts[i].count = 0;

    init_pair(20, COLOR_RED, COLOR_BLACK);

    int current = 0;

    while (1)
    {
        wclear(food_win);
        box(food_win, 0, 0);
        mvwprintw(food_win, 0, (width - 8) / 2, " FOOD ");
        wrefresh(food_win);
        if (inventory_food[0] + inventory_food[1] + inventory_food[2] == 0)
        {
            mvwprintw(food_win, 2, 4, "YOU DON'T HAVE ANY FOOD!");
            wrefresh(food_win);
            int c = getch();
            wclear(food_win);
            return inventory();
        }

        int index = 0;
        for (int i = 0; i < 3; i++)
        {
            if (inventory_food[i] != 0)
            {
                fts[index].count = inventory_food[i];
                fts[index++].type = i + 1;
            }
        }

        int y = 2;
        for (int i = 0; i < index; i++)
        {
            if (current == i) wattron(food_win, COLOR_PAIR(20));
            mvwprintw(food_win, y++, 2, "%s\t%d", fts[i].type == 1 ? "NORMAL FOOD" : (fts[i].type == 2 ? "SUPER FOOD" : "MAGICAL FOOD"), fts[i].count);
            if (current == i) wattroff(food_win, COLOR_PAIR(20));
        }
        wrefresh(food_win);
        int used_index = -1;
        int c = getch();
        switch (c)
        {
            case KEY_UP:
                current = current - 1 >= 0 ? current - 1 : index - 1;
                break;
            case KEY_DOWN:
                current = current + 1 < index ? current + 1 : 0;
                break;
            case '\n':
                used_index = current;
                break;
            default:
                return inventory();
                break;
        }
        if (used_index != -1)
        {
            int type = fts[used_index].type;
            inventory_food[type - 1]--;
            if (inventory_food[type - 1] == 0) current = 0;
            // add food effect!
        }
    }

    wrefresh(food_win);
}
