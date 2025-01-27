#ifndef MAP_H
#define MAP_H

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

// typedef struct {
//     wchar_t ch;  // Wide character
//     int color;   // Color pair number
// } Cell;

// Cell map[34][190];
int visible_map[34][190];


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
int room_count;

typedef struct {
    int x;
    int y;
} character;

character main_char;
int health = 10;
int energy = 10;


typedef struct {
    int x;
    int y;
    int type; // 1 for normal 2 for super 3 for magical // 4 for rotten
    int lifetime;
} FOOD;

FOOD food[20];
int food_index = 0;
int inventory_food[4];

typedef struct {
    int x;
    int y;
    int type; // 1 for mace, 2 for dagger, 3 for magic wand, 4 for normal arrow, 5 for sword
} weapon;
weapon weapons[20];
int weapon_index = 0;
int inventory_weapon[5];

typedef struct {
    int x;
    int y;
    int type; // 1 for heal 2 for speed 3 for damage
} enchant;
enchant enchants[20];
int enchant_index = 0;
int inventory_enchant[3];

typedef struct {
    int count;
    int type;
} to_show;

typedef struct {
    int y;
    int x;
    int health;
    int type;
    int room;
    int active;
    int dead;
    int steps;
    int max_steps;
} monster;

monster monsters[10];
int monster_num = 0;

int current_weapon = -1;

typedef struct {
    int y;
    int x;
    int type;  // 1 for dagger 2 for magic wand 3 for arrow
} throwed_weapon;

throwed_weapon throwed_weapons[100]; 
int throwed_weapon_index = 0;

int interval_time;
int timeout_interval;
int damage_interval;


int recently_damaged = 0;
int recently_damaged_count_down;
int reach_recently_damaged_count_down;

int heal_count_down;
int count_down;
int steps_to_heal = 0;
int reach_steps_to_heal = 50;


int speed_count_down = 0;
int power_count_down = 0;

int power_index = 1;
int speed_index = 1;


int food_lifetime;

int enchant_count_down = 0;
int current_enchant = -1;


void initializeRandom();
void create_rooms();
int get_rand_x();
int get_rand_y();
int get_rand_width();
int get_rand_height();
int check_overlapping();
void display_rooms();
int new_game();
int start_game();
int possible(int y, int x);
void connect_rooms(room room1, room room2);
void create_paths();
void display_text(const char *text);
// void display_door_window();
// void create_door_window();
// void create_things();
// void display_things();
// void edit();
int init_audio();
void close_audio();
void update_health();
void spawn_food();
void create_food();
void create_weapon();
void spawn_weapon();
void check_collect();
void clear_text();
int inventory();
int show_food();
int show_weapon();
void create_enchant();
void spawn_enchant();
int show_enchant();
void select_visible_map();
void set_monsters();
void display_monsters();
void move_monsters();
void check_monsters();
int use_weapon();
void use_mace();
void use_dagger();
void throw_dagger(int dir, int y, int x);
void update_monsters_health();
void use_magic_wand();
void throw_magic_wand(int dir, int y, int x);
void use_arrow();
void throw_arrow(int dir, int y, int x);
void use_sword();
void show_current_weapon();
void update_energy();
void set_variables();
void check_damage();
void active_sleeping_monsters();
void show_current_enchant();
int gameover();


void initializeRandom() 
{
    srand(time(NULL));
}

int new_game()
{ 
    for (int i = 0; i < 34; i++)
    {
        for (int j = 0; j < 190; j++)
        {
            visible_map[i][j] = 0;
        }
    }
    curs_set(0);  
    create_rooms();
    //create_door_window();
    //create_things();
    create_weapon();
    create_food();
    create_enchant();
    set_monsters();
    set_variables();
    if (!start_game()) return 0;
}

void set_variables()
{
    close_audio();
    if (!init_audio()) 
    {
        printf("Failed to initialize audio!\n");
    }
    int music_to_be_played = PlayerSetting.music;
    int game_difficulty = PlayerSetting.difficulty;
    Mix_Music *music_1 = Mix_LoadMUS("musics/music1.mp3");
    Mix_Music *music_2 = Mix_LoadMUS("musics/music2.mp3");
    Mix_Music *music_3 = Mix_LoadMUS("musics/music3.mp3");
    Mix_Music *music_4 = Mix_LoadMUS("musics/music4.mp3");
    Mix_Music *music_5 = Mix_LoadMUS("musics/music5.mp3");
    if (music_to_be_played == 0) Mix_PlayMusic(music_1, -1);
    else if (music_to_be_played == 1) Mix_PlayMusic(music_2, -1);
    else if (music_to_be_played == 2) Mix_PlayMusic(music_3, -1);
    else if (music_to_be_played == 3) Mix_PlayMusic(music_4, -1);
    else if (music_to_be_played == 4) Mix_PlayMusic(music_5, -1);

    switch (game_difficulty)
    {
        case 0: interval_time = 15; timeout_interval = 5000; room_count = 6; damage_interval = 3; heal_count_down = 40; food_lifetime = 300; reach_recently_damaged_count_down = 20; break;
        case 1: interval_time = 10; timeout_interval = 2000; room_count = 7; damage_interval = 3; heal_count_down = 50; food_lifetime = 200; reach_recently_damaged_count_down = 15; break;
        case 2: interval_time = 10; timeout_interval = 1000; room_count = 8; damage_interval = 3; heal_count_down = 60; food_lifetime = 100; reach_recently_damaged_count_down = 10; break;
    }

    recently_damaged_count_down = reach_recently_damaged_count_down;
    count_down = heal_count_down;
    init_pair(31, COLOR_WHITE, COLOR_BLACK); init_pair(32, COLOR_RED, COLOR_BLACK); init_pair(33, COLOR_BLUE, COLOR_BLACK);
    for (int i = 0; i < 3; i++) inventory_food[i] = 0;
    inventory_weapon[0] = 1;
    for (int i = 1; i < 5; i++) inventory_weapon[i] = 0;
    for (int i = 0; i < 10; i++) monsters[i].active = 0;
    for (int i = 0; i < 10; i++) monsters[i].dead = 0;
    for (int i = 0; i < 10; i++) monsters[i].steps = 0;
    for (int i = 0; i < 20; i++) food[i].lifetime = 0;
    int start_room;
    do {
        start_room = rand() % 6;
    } while(rooms[start_room].theme != 1);
    main_char.x = rooms[start_room].x + rooms[start_room].width / 2;
    main_char.y = rooms[start_room].y + rooms[start_room].height - 2;
}

int start_game()
{
    timeout(timeout_interval);
    time_t start_time, current_time;
    time(&start_time);
    time_t heal_start_time, heal_current_time;
    time(&heal_start_time);

    select_visible_map();

    while (1)
    {
        for (int i = 0; i < monster_num; i++)
        {
            if (monsters[i].active == 0) monsters[i].steps = 0;
        }
        clear();
        time(&current_time);
        if (difftime(current_time, start_time) >= interval_time) 
        {
            if (energy > 0) 
            {
                energy--;
            }
            time(&start_time);
        }
        display_rooms();
        create_paths();
        select_visible_map();
        // display_things();
        spawn_food();
        spawn_weapon();
        spawn_enchant();
        //edit();
        update_health();
        update_energy();
        show_current_weapon();
        show_current_enchant();
        update_monsters_health();
        display_monsters();
        check_monsters();
        check_collect();
        refresh();
        switch(PlayerSetting.color)
        {
            case 0: attron(COLOR_PAIR(31)); break;
            case 1: attron(COLOR_PAIR(32)); break;
            case 2: attron(COLOR_PAIR(33)); break;
        }
        mvprintw(main_char.y, main_char.x, "a");
        attroff(COLOR_PAIR(31)); attroff(COLOR_PAIR(32)); attroff(COLOR_PAIR(33));
        check_damage();
        int c = getch();
        switch (c)
        {
            case 'w':
                if (possible(main_char.y - speed_index, main_char.x))
                {
                    main_char.y -= speed_index;
                    break;
                }
                break;
            case 's':
                if (possible(main_char.y + speed_index, main_char.x))
                {
                    main_char.y += speed_index; 
                    break;
                }
                break;
            case 'a':
                if (possible(main_char.y, main_char.x - speed_index))
                {
                    main_char.x -= speed_index;
                    break;
                }
                break;
            case 'd':
                if (possible(main_char.y, main_char.x + speed_index))
                {
                    main_char.x += speed_index;
                    break;
                }
                break;
            case 'e':
                if (possible(main_char.y - speed_index, main_char.x + speed_index))
                {
                    main_char.x += speed_index; main_char.y -= speed_index;
                    break;
                }
                break;
            case 'q':
                if (possible(main_char.y - speed_index, main_char.x - speed_index))
                {
                    main_char.x -= speed_index; main_char.y -= speed_index;
                    break;
                }
                break;
            case 'x':
                if (possible(main_char.y + speed_index, main_char.x + speed_index))
                {
                    main_char.x += speed_index; main_char.y += speed_index;
                    break;
                }
                break;
            case 'z':
                if (possible(main_char.y + speed_index, main_char.x - speed_index))
                {
                    main_char.x -= speed_index; main_char.y += speed_index;
                    break;
                }
                break;
            case 'i':
                if (c == 'i') clear();
                if (inventory()) break;

            case 32:
                if (c == 32) use_weapon();
                break;
            default: break;
        }
        check_damage();
        if (gameover()) return 0;
        move_monsters();
        active_sleeping_monsters();

        if (c = 'w' || c == 's' || c == 'a' || c == 'd' || c == 'z' || c == 'x' || c == 'q' || c == 'e')
        {
            if (count_down > 0) count_down--;
            if (speed_count_down > 0) speed_count_down--;
            if (power_count_down > 0) power_count_down--;
            if (enchant_count_down > 0) enchant_count_down--;
            if (steps_to_heal < reach_steps_to_heal) steps_to_heal++;
            if (recently_damaged_count_down > 0) recently_damaged_count_down--;
            for (int i = 0; i < food_index; i++)
            {
                food[i].lifetime++;
                if (food[i].lifetime >= food_lifetime)
                {
                    if (food[i].type == 1) 
                    {
                        food[i].type = 4;
                    }
                    else if (food[i].type == 2 || food[i].type == 3) 
                    {
                        food[i].type = 1;
                        food[i].lifetime = 0;
                    }
                }
            }
        }

        if (recently_damaged_count_down == 0)
        {
            recently_damaged = 0;
        }

        if (count_down == 0) 
        {
            if (steps_to_heal >= reach_steps_to_heal)
            {
                if (health < 10 && energy == 10) 
                {
                    health++;
                    steps_to_heal = 0;
                }
            }
        }

        if (power_count_down == 0 && current_enchant != 2) 
        {
            power_index = 1;
        }

        if (speed_count_down == 0 && current_enchant != 1)
        {
            speed_index = 1;
        }

        if (enchant_count_down == 0) 
        {
            if (current_enchant == 1)
            {
                reach_steps_to_heal = 50;
                current_enchant = -1;
            }
            else if (current_enchant == 2)
            {
                speed_index = 1;
                current_enchant = -1;
            }
            else if (current_enchant == 3)
            {
                power_index = 1;
                current_enchant = -1;
            }
        }
    }
}


int possible(int y, int x)  // have a little problem here
{
    char blocked_chars[] = {'_', '|', ' ', 'o', 'D', 'G', 'F', 'U', 'S'};
    int num_blocked = 9;

    char ch = mvinch(y, x) & A_CHARTEXT;

    for (int i = 0; i < num_blocked; i++) 
    {
            if (ch == blocked_chars[i]) 
            {
                return 0; 
            }
    }

    return 1;
}

void create_rooms()
{
    int enchant_num = 0, nightmare_num = 0;
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
        if (theme < 30 && enchant_num < 2) 
        {rooms[i].theme = 2; enchant_num++;}
        else if (theme >= 30 && theme < 50 && nightmare_num < 1) 
        {rooms[i].theme = 3; nightmare_num++;}
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
    init_pair(41, COLOR_BLACK, COLOR_BLACK);
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
            if (visible_map[rooms[i].y][j] == 0) attron(COLOR_PAIR(41));
            mvprintw(rooms[i].y, j, "_");
            if (visible_map[rooms[i].y][j] == 0) attroff(COLOR_PAIR(41));
        }
        for (int j = rooms[i].x; j < rooms[i].x + rooms[i].width; j++)
        {
            if (visible_map[rooms[i].y + rooms[i].height - 1][j] == 0) attron(COLOR_PAIR(41));
            mvprintw(rooms[i].y + rooms[i].height - 1, j, "_");
            if (visible_map[rooms[i].y + rooms[i].height - 1][j] == 0) attroff(COLOR_PAIR(41));
        }
        for (int j = rooms[i].y; j < rooms[i].y + rooms[i].height; j++)
        {
            if (visible_map[j][rooms[i].x] == 0) attron(COLOR_PAIR(41));
            mvprintw(j, rooms[i].x, "|");
            if (visible_map[j][rooms[i].x] == 0) attroff(COLOR_PAIR(41));
        }
        for (int j = rooms[i].y; j < rooms[i].y + rooms[i].height; j++)
        {
            if (visible_map[j][rooms[i].x + rooms[i].width] == 0) attron(COLOR_PAIR(41));
            mvprintw(j, rooms[i].x + rooms[i].width, "|");
            if (visible_map[j][rooms[i].x + rooms[i].width] == 0) attroff(COLOR_PAIR(41));
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
                if (visible_map[j][k] == 0) attron(COLOR_PAIR(41));
                mvaddch(j, k, '.');
                if (visible_map[j][k] == 0) attroff(COLOR_PAIR(41));
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
    init_pair(41, COLOR_BLACK, COLOR_BLACK);
    init_pair(42, COLOR_WHITE, COLOR_BLACK);
    int x1 = room1.x + room1.width / 2;
    int y1 = room1.y + room1.height / 2;
    int x2 = room2.x + room2.width / 2;
    int y2 = room2.y + room2.height / 2;
    int x, y;
    attron(COLOR_PAIR(42));
    for (x = (x1 < x2 ? x1 : x2); x <= (x1 > x2 ? x1 : x2); x++) 
    {
        char ch = mvinch(y1, x) & A_CHARTEXT;
        if (ch != '.' && ch != '|' && ch != '_' && ch != '+')
        {
            if (visible_map[y1][x] == 0) attron(COLOR_PAIR(41));
            mvaddch(y1, x, '#');
            if ( visible_map[y1][x] == 0) attroff(COLOR_PAIR(41));
        }
        else if (ch == '|' || ch == '_') 
        {
            if (visible_map[y1][x] == 0) attron(COLOR_PAIR(41));
            mvaddch(y1, x, '+');
            if (visible_map[y1][x] == 0) attroff(COLOR_PAIR(41));
        }
    }
    refresh();

    for (y = (y1 < y2 ? y1 : y2); y <= (y1 > y2 ? y1 : y2); y++) 
    {
        char ch = mvinch(y, x2) & A_CHARTEXT;
        if (ch != '.' && ch != '|' && ch != '_' && ch != '+') 
        {
            if (visible_map[y][x2] == 0) attron(COLOR_PAIR(41));
            mvaddch(y, x2, '#');
            if (visible_map[y][x2] == 0) attroff(COLOR_PAIR(41));
        }
        else if (ch == '|' || ch == '_') 
        {
            if (visible_map[y][x2] == 0) attron(COLOR_PAIR(41));
            mvaddch(y, x2, '+');
            if (visible_map[y][x2] == 0) attroff(COLOR_PAIR(41));
        }
    }
    attroff(COLOR_PAIR(42));
    refresh();
}

void display_text(const char *text) 
{
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(0));
    mvprintw(2, 154, "%s", text);
    attroff(COLOR_PAIR(0));
    refresh();
}

void clear_text()
{
    mvprintw(2, 154, "                                               ");
    refresh();
}

void update_health()
{
    mvprintw(1, 3, "                      ");
    init_pair(7, COLOR_GREEN, COLOR_BLACK);
    init_pair(8, COLOR_RED, COLOR_BLACK);
    if (health >= 5) attron(COLOR_PAIR(7));
    else attron(COLOR_PAIR(8));
    mvprintw(1, 3, "HEALTH: ");
    if (health >= 5) attroff(COLOR_PAIR(7));
    else attroff(COLOR_PAIR(8));
    int x = 11;
    for (int i = 0; i < health; i++)
    {
       mvprintw(1, x++ ,"💊");
    }
}

void update_energy()
{
    mvprintw(2, 3, "                      ");
    init_pair(7, COLOR_GREEN, COLOR_BLACK);
    init_pair(8, COLOR_RED, COLOR_BLACK);
    if (energy >= 5) attron(COLOR_PAIR(7));
    else attron(COLOR_PAIR(8));
    mvprintw(2, 3, "ENERGY: ");
    if (energy >= 5) attroff(COLOR_PAIR(7));
    else attroff(COLOR_PAIR(8));  
    int x = 11;
    for (int i = 0; i < energy; i++)
    {
       mvprintw(2, x++ ,"🔋");
    }
}

void show_current_enchant()
{
    switch (current_enchant)
    {
        case 0: mvprintw(36, 175, "ENCHANT: 🧪"); break;
        case 1: mvprintw(36, 175, "ENCHANT: 🗲"); break;
        case 2: mvprintw(36, 175, "ENCHANT: 🩸"); break;
        case -1: mvprintw(36, 175, "ENCHANT: NONE"); break;
    }
}


// ///////////////////////////// edit
// void edit()
// {
//     // edit pillars
//     // for (int i = 0; i < 34; i++)
//     // {
//     //     for (int j = 0; j < 50; j++)
//     //     {
//     //         if (mvinch(i, j) == 'o' && (mvinch(i + 1, j) != '.' && mvinch(i + 1, j) != '_' && mvinch(i + 1, j) != '|') &&
//     //             (mvinch(i, j + 1) != '.' && mvinch(i, j + 1) != '_' && mvinch(i, j + 1) != '|') &&
//     //             (mvinch(i, j - 1) != '.' && mvinch(i, j - 1) != '_' && mvinch(i, j - 1) != '|') &&
//     //             (mvinch(i - 1, j) != '.' && mvinch(i - 1, j) != '_' && mvinch(i - 1, j) != '|'))
//     //             {
//     //                 mvaddch(i, j, ' ');
//     //             }
//     //     }
//     // }


//     // edit doors
//     for (int i = 0; i < 6; i++)
//     {
//         if (rooms[i].theme == 2) attron(COLOR_PAIR(1));
//         else if (rooms[i].theme == 3) attron(COLOR_PAIR(2));
//         for (int j = rooms[i].x + 1; j < rooms[i].x + rooms[i].width - 1; j++)
//         {
//             if (mvinch(rooms[i].y - 1, j) != '#' && mvinch(rooms[i].y - 1, j) != '+') 
//             {
//                 if (visible_map[rooms[i].y][j] == 0) attron(COLOR_PAIR(41));
//                 mvaddch(rooms[i].y, j, '_');
//                 if (visible_map[rooms[i].y][j] == 0) attroff(COLOR_PAIR(41));
//             }
            
//             if (mvinch(rooms[i].y + rooms[i].height, j) != '#' && mvinch(rooms[i].y + rooms[i].height, j) != '+')
//             {
//                 if (visible_map[rooms[i].y + rooms[i].height - 1][j] == 0) attron(COLOR_PAIR(41));
//                 mvaddch(rooms[i].y + rooms[i].height - 1, j, '_');
//                  if (visible_map[rooms[i].y + rooms[i].height - 1][j] == 0) attroff(COLOR_PAIR(41));
//             }
//         }
//         for (int j = rooms[i].y + 1; j < rooms[i].y + rooms[i].height - 1; j++)
//         {
//             if (mvinch(j, rooms[i].x - 1) != '#' && mvinch(j, rooms[i].x - 1) != '+') 
//             {
//                 if (visible_map[j][rooms[i].x] == 0) attron(COLOR_PAIR(41));
//                 mvaddch(j, rooms[i].x, '|');
//                 if (visible_map[j][rooms[i].x] == 0) attroff(COLOR_PAIR(41));
//             }
//             if (mvinch(j, rooms[i].x + rooms[i].width + 1) != '#' && mvinch(j, rooms[i].x + rooms[i].width + 1) != '+')
//             {
//                 if (visible_map[j][rooms[i].x + rooms[i].width] == 0) attron(COLOR_PAIR(41));
//                 mvaddch(j, rooms[i].x + rooms[i].width, '|');
//                 if (visible_map[j][rooms[i].x + rooms[i].width] == 0) attroff(COLOR_PAIR(41));
//             }
//         }
//         attroff(COLOR_PAIR(1)); attroff(COLOR_PAIR(2));

//     }

// }

void check_collect()
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
                flushinp();
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
        
    for (int i = 0; i < weapon_index; i++)
    {
        if (main_char.y == weapons[i].y && (main_char.x == weapons[i].x || main_char.x == weapons[i].x + 1))
        {
            display_text("PRESS C TO COLLECT THE WEAPON");
            int c = getch();
            if (c == 'c')
            {
                int type_index = weapons[i].type - 1;
                if (type_index == 1) inventory_weapon[type_index] += 10;
                else if (type_index == 2) inventory_weapon[type_index] += 8;
                else if (type_index == 3) inventory_weapon[type_index] += 20;
                else if (type_index == 4) inventory_weapon[type_index] += 1;
                weapons[i].y = 0; weapons[i].x = 0;
                clear_text();
                display_text("             COLLECTED!");
                refresh();
                napms(750);
                flushinp();
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

    for (int i = -1; i < enchant_index; i++)
    {
        if (main_char.y == enchants[i].y && (main_char.x == enchants[i].x || main_char.x == enchants[i].x + 1))
        {
            display_text("PRESS C TO COLLECT THE ENCHANT");
            int c = getch();
            if (c == 'c')
            {
                inventory_enchant[enchants[i].type - 1]++;
                enchants[i].y = -1; enchants[i].x = 0;
                clear_text();
                display_text("             COLLECTED!");
                refresh();
                napms(750);
                flushinp();
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

    for (int i = 0; i < throwed_weapon_index; i++)
    {
        if (main_char.y == throwed_weapons[i].y && (main_char.x == throwed_weapons[i].x || main_char.x == throwed_weapons[i].x + 1))
        {
            display_text("PRESS C TO COLLECT THE WEAPON");
            int c = getch();
            if (c == 'c')
            {
                int type_index = throwed_weapons[i].type;
                if (type_index == 1) inventory_weapon[type_index] += 1;
                else if (type_index == 2) inventory_weapon[type_index] += 1;
                else if (type_index == 3) inventory_weapon[type_index] += 1;
                throwed_weapons[i].y = 0; throwed_weapons[i].x = 0;
                clear_text();
                display_text("             COLLECTED!");
                refresh();
                napms(750);
                flushinp();
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

void select_visible_map()
{
    for (int r = 0; r < 6; r++) 
    {
        if (main_char.y >= rooms[r].y && main_char.y <= rooms[r].y + rooms[r].height - 1 &&
            main_char.x >= rooms[r].x && main_char.x <= rooms[r].x + rooms[r].width)
            {
                for (int i = rooms[r].y; i < rooms[r].y + rooms[r].height; i++)
                {
                    for (int j = rooms[r].x; j <= rooms[r].x + rooms[r].width; j++)
                    {
                        visible_map[i][j] = 1;
                    }
                }
            }
    }

    for (int i = main_char.y - 1; i <= main_char.y + 1; i++)
    {
        for (int j = main_char.x - 1; j <= main_char.x + 1; j++)
        {
            char ch = mvinch(i, j) & A_CHARTEXT;
            if (ch == '#')
            {
                visible_map[i][j] = 1;
            }
        }
    }
}


//-------------------------------------CREATE_THINGS------------------------------------------------//

void create_enchant()
{
    for (int i = 0; i < 6; i++)
    {
        int p, q = 1;
        if (rooms[i].theme == 2)
        {
            p = rand() % 3;
            q = rand() % 8;
        }  
        else p = rand() % 8;
        if (p == 0 || p == 1 || p == 2)
        {
            for (int j = 0; j < q; j++)
            {
                int flag;
                int y, x;
                do 
                {
                    y = rooms[i].y + 1 + (rand() % (rooms[i].height - 3));
                    x = rooms[i].x + 1 + (rand() % (rooms[i].width - 3));
                    flag = 0;
                    for (int j = 0; j < food_index; j++)
                    {
                        if (y == food[j].y && x == food[j].x) flag = 1;
                    }
                    for (int j = 0; j < weapon_index; j++)
                    {
                        if (y == weapons[j].y && x == weapons[j].x) flag = 1;
                    }
                } while (flag == 1);

                enchants[enchant_index].y = y; enchants[enchant_index].x = x;
                if (p == 0) enchants[enchant_index++].type = 1;
                else if (p == 1) enchants[enchant_index++].type = 2;
                else if (p == 2) enchants[enchant_index++].type = 3;
            }
            
        }
    }
}

void create_weapon()
{
    for (int i = 0; i < 6; i++)
    {
        int p = rand() % 15;
        if (p == 0 || p == 1 || p == 2 || p == 3 || p == 4 || p == 5 || p == 6)
        {
            int flag;
            int y, x;
            do 
            {
                y = rooms[i].y + 1 + (rand() % (rooms[i].height - 3));
                x = rooms[i].x + 1 + (rand() % (rooms[i].width - 3));
                flag = 0;
                for (int j = 0; j < food_index; j++)
                {
                    if (y == food[j].y && x == food[j].x) flag = 1;
                }
            } while (flag == 1);

            weapons[weapon_index].y = y; weapons[weapon_index].x = x;
            if (p == 0 || p == 1 || p == 2) weapons[weapon_index++].type = 2;
            else if (p == 3 || p == 4) weapons[weapon_index++].type = 3;
            else if (p == 5) weapons[weapon_index++].type = 4;
            else if (p == 6) weapons[weapon_index++].type = 5;
        }
    }
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

//-------------------------------------CREATE_THINGS------------------------------------------------//


//-------------------------------------SPAWN_THINGS------------------------------------------------//

void spawn_food()
{
    const char *food1 = "🥫"; //normal and bad food 
    const char *food2 = "🍥"; // super food!
    const char *food3 = "🏺"; //magic food
    for (int i = 0; i < food_index; i++)
    {
        if (food[i].x != 0 && visible_map[food[i].y][food[i].x] == 1)
        {
            if (food[i].type == 1) mvprintw(food[i].y, food[i].x, "🥫");
            else if (food[i].type == 2) mvprintw(food[i].y, food[i].x, "🍥");
            else if (food[i].type == 3) mvprintw(food[i].y, food[i].x, "🏺");
            else mvprintw(food[i].y, food[i].x, "🦠");
        }
    }
}

void spawn_enchant()
{
    const char *enchant1 = "🧪"; //health enchant
    const char *enchant2 = "🗲"; //speed enchant
    const char *enchant3 = "🩸"; //damage enchant
    for (int i = 0; i < enchant_index; i++)
    {
        if (enchants[i].x != 0 && visible_map[enchants[i].y][enchants[i].x] == 1)
        {
            if (enchants[i].type == 1) mvprintw(enchants[i].y, enchants[i].x, "🧪");
            else if (enchants[i].type == 2) mvprintw(enchants[i].y, enchants[i].x, "🗲");
            else if (enchants[i].type == 3) mvprintw(enchants[i].y, enchants[i].x, "🩸");
        }
    }
}

void spawn_weapon()
{
    const char *mace = "⚒";
    const char *dagger = "🗡";
    const char * magic_wand = "🪄";
    const char *arrow = "⬻";
    const char *sword = "⚔";
    for (int i = 0; i < weapon_index; i++)
    {
        if (weapons[i].x != 0 && visible_map[weapons[i].y][weapons[i].x] == 1)
        {
            if (weapons[i].type == 2) mvprintw(weapons[i].y, weapons[i].x, "🗡");
            else if (weapons[i].type == 3) mvprintw(weapons[i].y, weapons[i].x, "🪄");
            else if (weapons[i].type == 4) mvprintw(weapons[i].y, weapons[i].x, "⬻");
            else if (weapons[i].type == 5) mvprintw(weapons[i].y, weapons[i].x, "⚔");
        }
    }
    for (int i = 0; i < throwed_weapon_index; i++)
    {
        if (throwed_weapons[i].x != 0 && visible_map[throwed_weapons[i].y][throwed_weapons[i].x] == 1)
        {
            if (throwed_weapons[i].type == 1) mvprintw(throwed_weapons[i].y, throwed_weapons[i].x, "🗡");
            else if (throwed_weapons[i].type == 2) mvprintw(throwed_weapons[i].y, throwed_weapons[i].x, "🪄");
            else if (throwed_weapons[i].type == 3) mvprintw(throwed_weapons[i].y, throwed_weapons[i].x, "⬻");
        }   
    }
}

//-------------------------------------SPAWN_THINGS------------------------------------------------//


//-------------------------------------INVENTORY------------------------------------------------//

int inventory() 
{
    refresh();
    int startx, starty, width, height;
    WINDOW *inv_win;
    
    height = LINES - 2;
    width = COLS - 4;   
    starty = 1;           
    startx = 2;           

    inv_win = newwin(height, width, starty, startx);

    box(inv_win, 0, 0);

    wrefresh(inv_win);

    mvwprintw(inv_win, 0, (width - 10) / 2, " INVENTORY ");

    mvwprintw(inv_win, 1, 2, "1. FOOD");
    mvwprintw(inv_win, 2, 2, "2. WEAPONS");
    mvwprintw(inv_win, 3, 2, "3. ENCHANTS");
    mvwprintw(inv_win, 4, 2, "4. KEYS");


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
        case '2':
            wclear(inv_win);
            wrefresh(inv_win);
            return show_weapon();
            break;
        case '3':
            wclear(inv_win);
            wrefresh(inv_win);
            return show_enchant();
            break;
        // case '4':
        //     show_keys();
        //     break;
         default:
            wclear(inv_win);
            wrefresh(inv_win);
            return 1;
            break;
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

    to_show fts[4];
    for (int i = 0; i < 4; i++) fts[i].count = 0;

    init_pair(20, COLOR_RED, COLOR_BLACK);

    int current = 0;

    while (1)
    {
        wclear(food_win);
        box(food_win, 0, 0);
        mvwprintw(food_win, 0, (width - 8) / 2, " FOOD ");
        wrefresh(food_win);
        if (inventory_food[0] + inventory_food[1] + inventory_food[2] + inventory_food[3] == 0)
        {
            mvwprintw(food_win, 2, 4, "YOU DON'T HAVE ANY FOOD!");
            wrefresh(food_win);
            int c = getch();
            wclear(food_win);
            return inventory();
        }

        int index = 0;
        for (int i = 0; i < 4; i++)
        {
            if (inventory_food[i] != 0)
            {
                fts[index].count = inventory_food[i];
                fts[index++].type = i + 1;
            }
        }

        int y = 1;
        for (int i = 0; i < index; i++)
        {
            if (current == i) wattron(food_win, COLOR_PAIR(20));
            mvwprintw(food_win, y++, 2, "%s\t%d", (fts[i].type == 1) ? "NORMAL FOOD" : (fts[i].type == 2 ? "SUPER FOOD" : (fts[i].type == 3 ? "MAGICAL FOOD" : "ROTTEN FOOD")), fts[i].count);
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
            if (type == 1) 
            {
                display_text("YOU ATE NORMAL FOOD");
                refresh();
                napms(1000);
                flushinp();
                clear_text();
                wclear(food_win);
                wrefresh(food_win);
                energy = 10;
                return 1;
            }
            else if (type == 2) 
            {
                display_text("YOU ATE SUPER FOOD");
                refresh();
                napms(1000);
                flushinp();
                clear_text();
                wclear(food_win);
                wrefresh(food_win);
                energy = 10; health = 10; power_index = 2; power_count_down = 50;
                return 1;
            }
            else if (type == 3)
            {
                display_text("YOU ATE MAGICAL FOOD");
                refresh();
                napms(1000);
                flushinp();
                clear_text();
                wclear(food_win);
                wrefresh(food_win);
                energy = 10; health = 10; speed_index = 2; speed_count_down = 50;
                return 1;
            }
            else if (type == 4)
            {
                display_text("YOU ATE ROTTEN FOOD");
                refresh();
                napms(1000);
                flushinp();
                clear_text();
                wclear(food_win);
                wrefresh(food_win);
                if (health >= 7) health -= 3;
                else if (health >= 4) health -= 2;
                else health--;
                return 1;
            }
            if (inventory_food[type - 1] == 0) current = 0;
        }
    }

    wrefresh(food_win);
}

int show_weapon()
{
    int startx, starty, width, height;
    WINDOW *weapon_win;
    
    height = LINES - 2;
    width = COLS - 4;   
    starty = 1;           
    startx = 2;           

    weapon_win = newwin(height, width, starty, startx);

    box(weapon_win, 0, 0);

    mvwprintw(weapon_win, 0, (width - 8) / 2, " WEAPON ");
    wrefresh(weapon_win);

    to_show wts[5];
    for (int i = 0; i < 5; i++) wts[i].count = 0;

    init_pair(20, COLOR_RED, COLOR_BLACK);

    int current = 0;

    while (1)
    {
        wclear(weapon_win);
        box(weapon_win, 0, 0);
        mvwprintw(weapon_win, 0, (width - 8) / 2, " WEAPON ");
        wrefresh(weapon_win);

        int index = 0;
        for (int i = 0; i < 5; i++)
        {
            if (inventory_weapon[i] != 0)
            {
                wts[index].count = inventory_weapon[i];
                wts[index++].type = i + 1;
            }
        }

        int y = 1;
        char weapon_type[20];
        for (int i = 0; i < index; i++)
        {

            if (wts[i].type == 1) strcpy(weapon_type, "MACE");
            else if (wts[i].type == 2) strcpy(weapon_type, "DAGGER");
            else if (wts[i].type == 3) strcpy(weapon_type, "MAGIC WAND");
            else if (wts[i].type == 4) strcpy(weapon_type, "ARROW");
            else if (wts[i].type == 5) strcpy(weapon_type, "SWORD");
            if (current == i) wattron(weapon_win, COLOR_PAIR(20));
            mvwprintw(weapon_win, y++, 2, "%s\t%d", weapon_type, wts[i].count);
            if (current == i) wattroff(weapon_win, COLOR_PAIR(20));
        }
        wrefresh(weapon_win);
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
            int type = wts[used_index].type;
            int type_index = type - 1;
            if (type_index == 0) 
            {
                wclear(weapon_win);
                refresh();
                current_weapon = 0;
                display_text("YOUR WEAPON IS NOW MACE");
                refresh();
                napms(1500);
                flushinp();
                clear_text();
                return 1;
            }
            else if (type_index == 1) 
            {
                wclear(weapon_win);
                refresh();
                current_weapon = 1;
                display_text("YOUR WEAPON IS NOW DAGGER");
                refresh();
                napms(1500);
                flushinp();
                clear_text();
                return 1;  
            }
            else if (type_index == 2)
            {
                wclear(weapon_win);
                refresh();
                current_weapon = 2;
                display_text("YOUR WEAPON IS NOW MAGIC WAND");
                refresh();
                napms(1500);
                flushinp();
                clear_text();
                return 1;
            }
            else if (type_index == 3)
            {
                wclear(weapon_win);
                refresh();
                current_weapon = 3;
                display_text("YOUR WEAPON IS NOW ARROW");
                refresh();
                napms(1500);
                flushinp();
                clear_text();
                return 1;
            }
            else if (type_index == 4)
            {
                wclear(weapon_win);
                refresh();
                current_weapon = 4;
                display_text("YOUR WEAPON IS NOW SWORD");
                refresh();
                napms(1500);
                flushinp();
                clear_text();
                return 1;
            }
            current = 0;
        }
    }

    wrefresh(weapon_win);
}

int show_enchant()
{
    int startx, starty, width, height;
    WINDOW *enchant_win;
    
    height = LINES - 2;
    width = COLS - 4;   
    starty = 1;           
    startx = 2;           

    enchant_win = newwin(height, width, starty, startx);

    box(enchant_win, 0, 0);

    mvwprintw(enchant_win, 0, (width - 8) / 2, " ENCHANT ");
    wrefresh(enchant_win);

    to_show ets[3];
    for (int i = 0; i < 3; i++) ets[i].count = 0;

    init_pair(20, COLOR_RED, COLOR_BLACK);

    int current = 0;

    while (1)
    {
        wclear(enchant_win);
        box(enchant_win, 0, 0);
        mvwprintw(enchant_win, 0, (width - 8) / 2, " ENCHANT ");
        wrefresh(enchant_win);

        if (inventory_enchant[0] + inventory_enchant[1] + inventory_enchant[2] == 0)
        {
            mvwprintw(enchant_win, 2, 4, "YOU DON'T HAVE ANY ENCHANT!");
            wrefresh(enchant_win);
            int c = getch();
            wclear(enchant_win);
            return inventory();
        }

        int index = 0;
        for (int i = 0; i < 3; i++)
        {
            if (inventory_enchant[i] != 0)
            {
                ets[index].count = inventory_enchant[i];
                ets[index++].type = i + 1;
            }
        }

        int y = 1;
        char enchant_type[20];
        for (int i = 0; i < index; i++)
        {

            if (ets[i].type == 1) strcpy(enchant_type, "HEALTH ENCHANT");
            else if (ets[i].type == 2) strcpy(enchant_type, "SPEED ENCHANT");
            else if (ets[i].type == 3) strcpy(enchant_type, "POWER ENCHANT");
            if (current == i) wattron(enchant_win, COLOR_PAIR(20));
            mvwprintw(enchant_win, y++, 2, "%s\t%d", enchant_type, ets[i].count);
            if (current == i) wattroff(enchant_win, COLOR_PAIR(20));
        }
        wrefresh(enchant_win);
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
            if (current_enchant == -1)
            {
                int type = ets[used_index].type;
                inventory_enchant[type - 1]--;
                if (type == 1)
                {
                    display_text("YOU ARE USING HEALTH ENCHANT");
                    refresh();
                    napms(1000);
                    flushinp();
                    clear_text();
                    wclear(enchant_win);
                    wrefresh(enchant_win);
                    reach_steps_to_heal = 25;
                    enchant_count_down = 50;
                    energy = 10;
                    current_enchant = 0;
                    return 1;
                }
                else if (type == 2)
                {
                    display_text("YOU ARE USING SPEED ENCHANT");
                    refresh();
                    napms(1000);
                    flushinp();
                    clear_text();
                    wclear(enchant_win);
                    wrefresh(enchant_win);
                    speed_index = 2;
                    enchant_count_down = 50;
                    current_enchant = 1;
                    return 1;
                }
                else if (type == 3)
                {
                    display_text("YOU ARE USING POWER ENCHANT");
                    refresh();
                    napms(1000);
                    flushinp();
                    clear_text();
                    wclear(enchant_win);
                    wrefresh(enchant_win);
                    power_index = 2;
                    enchant_count_down = 50;
                    current_enchant = 2;
                    return 1;
                }
                if (inventory_enchant[type - 1] == 0) current = 0;
            }
            else 
            {
                display_text("WAIT FOR THE LAST ENCHANT TO FINISH...");
                refresh();
                napms(1000);
                flushinp();
                clear_text();
                wclear(enchant_win);
                wrefresh(enchant_win);
                return 1;
            }
        }
    }

    wrefresh(enchant_win);
}

void show_current_weapon()
{
    switch (current_weapon)
    {
        case 0: mvprintw(35, 175, "WEAPON: ⚒"); break;
        case 1: mvprintw(35, 175, "WEAPON: 🗡"); break;
        case 2: mvprintw(35, 175, "WEAPON: 🪄"); break;
        case 3: mvprintw(35, 175, "WEAPON: ⬻"); break;
        case 4: mvprintw(35, 175, "WEAPON: ⚔"); break;
        default: mvprintw(35, 175, "WEAPON: NONE"); break;
    }
}
//-------------------------------------INVENTORY------------------------------------------------//

//-------------------------------------MONSTERS------------------------------------------------//

void set_monsters()
{
    // Deamon
    int has_monster[6] = {0};
    for (int i = 0; i < 6; i++)
    {
        int p = rand() % 2;
        if (p == 1)
        {
            int y = rooms[i].y + 1 + (rand() % (rooms[i].height - 1));
            int x = rooms[i].x + 1 + (rand() % (rooms[i].width - 1));
            monsters[monster_num].y = y; monsters[monster_num].x = x; monsters[monster_num].type = 1; monsters[monster_num].room = i; monsters[monster_num].max_steps = 5; monsters[monster_num++].health = 5;
            has_monster[i]++;
        }
    }

    for (int i = 0; i < 6; i++)
    {
        int p = rand() % 4;
        if (p == 1)
        {
            int y = rooms[i].y + 1 + (rand() % (rooms[i].height - 1));
            int x = rooms[i].x + 1 + (rand() % (rooms[i].width - 1));
            monsters[monster_num].y = y; monsters[monster_num].x = x; monsters[monster_num].type = 2; monsters[monster_num].room = i; monsters[monster_num].max_steps = 5; monsters[monster_num++].health = 10;
            has_monster[i]++;
        }
    }

    for (int i = 0; i < 6; i++)
    {
        int p = rand() % 9;
        if (p == 1 && has_monster[i] < 2)
        {
            int y = rooms[i].y + 1 + (rand() % (rooms[i].height - 1));
            int x = rooms[i].x + 1 + (rand() % (rooms[i].width - 1));
            monsters[monster_num].y = y; monsters[monster_num].x = x; monsters[monster_num].type = 3; monsters[monster_num].room = i; monsters[monster_num].max_steps = 5; monsters[monster_num++].health = 15;
            has_monster[i]++;
        }
    }

    for (int i = 0; i < 6; i++)
    {
        int p = rand() % 16;
        if (p == 1 && has_monster[i] < 2)
        {
            int y = rooms[i].y + 1 + (rand() % (rooms[i].height - 1));
            int x = rooms[i].x + 1 + (rand() % (rooms[i].width - 1));
            monsters[monster_num].y = y; monsters[monster_num].x = x; monsters[monster_num].type = 4; monsters[monster_num].room = i; monsters[monster_num].max_steps = 1000000; monsters[monster_num++].health = 20;
            has_monster[i]++;
        }
    }

    for (int i = 0; i < 6; i++)
    {
        int p = rand() % 20;
        if (p == 1 && has_monster[i] < 2)
        {
            int y = rooms[i].y + 1 + (rand() % (rooms[i].height - 1));
            int x = rooms[i].x + 1 + (rand() % (rooms[i].width - 1));
            monsters[monster_num].y = y; monsters[monster_num].x = x; monsters[monster_num].type = 5; monsters[monster_num].room = i; monsters[monster_num].max_steps = 5; monsters[monster_num++].health = 30;
            has_monster[i]++;
        }
    }
}

void display_monsters()
{
    for (int i = 0; i < monster_num; i++)
    {
        int y = monsters[i].y; int x = monsters[i].x;
        if (visible_map[y][x] == 1 && monsters[i].dead == 0)
        {
            switch(monsters[i].type)
            {
                case 1:
                    mvaddch(y, x, 'D');
                    break;
                case 2:
                    mvaddch(y, x, 'F');
                    break;
                case 3:
                    mvaddch(y, x, 'G');
                    break;
                case 4:
                    mvaddch(y, x, 'S');
                    break;
                case 5:
                    mvaddch(y, x, 'U');
                    break;
            }
        }
    }
}

void check_monsters()
{
    int y = main_char.y, x = main_char.x;
    int in_room = 0;
    for (int i = 0; i < 6; i++)
    {
        if (y > rooms[i].y && y < rooms[i].y + rooms[i].height && x > rooms[i].x && x < rooms[i].x + rooms[i].width)
        {
            in_room = 1;
            for (int j = 0; j < monster_num; j++)
            {
                if (monsters[j].room == i)
                {
                    monsters[j].active = 1;
                }
                else 
                {
                    monsters[j].active = 0;
                }
            }
        }
    }

    if (!in_room)
    {
        for (int i = 0; i < monster_num; i++) monsters[i].active = 0;
    }

}

void move_monsters()
{
    int y = main_char.y, x = main_char.x;
    for (int i = 0; i < monster_num; i++)
    {
        if (monsters[i].active == 1)
        {
            int mon_y = monsters[i].y, mon_x = monsters[i].x, room = monsters[i].room, type = monsters[i].type;
            if (monsters[i].steps < monsters[i].max_steps)
            {
                if (x < mon_x && y > mon_y)
                {
                    int flag = 1;
                    for (int j = 0; j < monster_num; j++)
                    {
                        if (mon_x - 1 == monsters[j].x && mon_y + 1 == monsters[j].y) flag = 0;
                    }
                    if (mon_x - 1 > rooms[room].x && mon_y + 1 < rooms[room].y + rooms[room].height - 1 &&
                        !(mon_x - 1 == x && mon_y + 1 == y) && flag)
                    {
                        monsters[i].x--; monsters[i].y++; monsters[i].steps++;
                    }
                }
                else if (x < mon_x && y < mon_y)
                {
                    int flag = 1;
                    for (int j = 0; j < monster_num; j++)
                    {
                        if (mon_x - 1 == monsters[j].x && mon_y - 1 == monsters[j].y) flag = 0;
                    }
                    if (mon_x - 1 > rooms[room].x && mon_y - 1 > rooms[room].y &&
                        !(mon_x - 1 == x && mon_y - 1 == y) && flag)
                    {
                        monsters[i].x--; monsters[i].y--; monsters[i].steps++;
                    }
                }
                else if (x > mon_x && y > mon_y)
                {
                    int flag = 1;
                    for (int j = 0; j < monster_num; j++)
                    {
                        if (mon_x + 1 == monsters[j].x && mon_y + 1 == monsters[j].y) flag = 0;
                    }
                    if (mon_x + 1 < rooms[room].x + rooms[room].width && mon_y + 1 < rooms[room].y + rooms[room].height - 1 &&
                        !(mon_x + 1 == x && mon_y + 1 == y) && flag) 
                    {
                        monsters[i].x++; monsters[i].y++; monsters[i].steps++;
                    }
                }
                else if (x > mon_x && y < mon_y)
                {
                    int flag = 1;
                    for (int j = 0; j < monster_num; j++)
                    {
                        if (mon_x + 1 == monsters[j].x && mon_y - 1 == monsters[j].y) flag = 0;
                    }
                    if (mon_x + 1 < rooms[room].x + rooms[room].width && mon_y - 1 > rooms[room].y &&
                        !(mon_x + 1 == x && mon_y - 1 == y) && flag)
                    {
                        monsters[i].y--; monsters[i].x++; monsters[i].steps++;
                    }
                }
                else if (y == mon_y)
                {
                    if (x > mon_x && mon_x + 1 != x)
                    {
                        int flag = 1;
                        for (int j = 0; j < monster_num; j++)
                        {
                            if (mon_y == monsters[j].y && mon_x + 1 == monsters[j].x) flag = 0;
                        }
                        if (flag) 
                        {monsters[i].x++; monsters[i].steps++;} 
                    }
                    else if (x < mon_x && mon_x - 1 != x)
                    {
                        int flag = 1;
                        for (int j = 0; j < monster_num; j++)
                        {
                            if (mon_y == monsters[j].y && mon_x - 1 == monsters[j].x) flag = 0;
                        }
                        if (flag) 
                        {monsters[i].x--; monsters[i].steps++;}
                    }
                }
                else if (x == mon_x)
                {
                    if (y < mon_y && mon_y - 1 != y)
                    {
                        int flag = 1;
                        for (int j = 0; j < monster_num; j++)
                        {
                            if (mon_x == monsters[j].x && mon_y - 1 == monsters[j].y) flag = 0;
                        }
                        if (flag) 
                        {monsters[i].y--; monsters[i].steps++;}
                    }
                    else if (y > mon_y && mon_y + 1 != y && mon_y + 1 < rooms[room].y + rooms[room].height - 1)
                    {
                        int flag = 1;
                        for (int j = 0; j < monster_num; j++)
                        {
                            if (mon_x == monsters[j].x && mon_y + 1 == monsters[j].y) flag = 0;
                        }
                        if (flag) 
                        {monsters[i].y++; monsters[i].steps++;}
                    }
                }
            }
        }
    }   
}

void update_monsters_health()
{
    init_pair(71, COLOR_RED, COLOR_BLACK);
    mvprintw(1, 75, "                          ");
    mvprintw(2, 75, "                          ");
    int y = 1;
    attron(COLOR_PAIR(71));
    for (int i = 0; i < monster_num; i++)   
    {
        if (monsters[i].active == 1 && monsters[i].health > 0)
        {
            char symbol;
            switch (monsters[i].type)
            {
                case 1: symbol = 'D'; break;
                case 2: symbol = 'F'; break;
                case 3: symbol = 'G'; break;
                case 4: symbol = 'S'; break;
                case 5: symbol = 'U'; break;
            }
            int health = monsters[i].health;
            mvaddch(y, 75, symbol);
            for (int j = 0; j < health; j++)
            {
                mvprintw(y, 77 + j, "☤");
            }
            y++;
        }
    }
    attroff(COLOR_PAIR(71));
}

void check_damage()
{
    int y = main_char.y, x = main_char.x;
    if (recently_damaged == 0)
    {
        for (int i = 0; i < monster_num; i++)
        {
            int mon_x = monsters[i].x, mon_y = monsters[i].y, mon_type = monsters[i].type;
            if (mon_x >= x - 1 && mon_x <= x + 1 && mon_y >= y - 1 && mon_y <= y + 1)
            {
                if (mon_type == 1 || mon_type == 2 || mon_type == 3) health -= 1;
                else if (mon_type == 4) health -= 1;
                else if (mon_type == 5) health -= 1;
                recently_damaged = 1;
                recently_damaged_count_down = reach_recently_damaged_count_down;
                display_text("THE MONSTER DAMAGED YOU");
                update_health();
                napms(800);
                flushinp();
                refresh();
                count_down = heal_count_down;
                clear_text();
            }
        }
    }
}

void active_sleeping_monsters()
{
    int y = main_char.y, x = main_char.x;
    for (int i = 0; i < monster_num; i++)
    {
        if (monsters[i].steps == monsters[i].max_steps)
        {
            int mon_x = monsters[i].x, mon_y = monsters[i].y;
            if (x >= mon_x - 1 && x <= mon_x + 1 && y >= mon_y - 1 && y <= mon_y + 1)
            {
                monsters[i].steps = 0;
            }
        }
    }
}
//-------------------------------------MONSTERS------------------------------------------------//




//-------------------------------------WEAPON_USAGE------------------------------------------------//

int use_weapon()
{  
    switch (current_weapon)
    {
        case 0: use_mace(); break;
        case 1: use_dagger(); break;
        case 2: use_magic_wand(); break;
        case 3: use_arrow(); break;
        case 4: use_sword(); break;
        default: return 1;
    }
    return 1;
}

void use_mace()
{
    display_text("        YOU USED MACE");
    refresh();
    int y = main_char.y, x = main_char.x;
    for (int i = 0; i < monster_num; i++)
    {
        int mon_x = monsters[i].x, mon_y = monsters[i].y;
        if (mon_x >= x - 1 && mon_x <= x + 1 && mon_y >= y - 1 && mon_y <= y + 1)
        {
            monsters[i].health -= 5 * power_index;
            recently_damaged = 0;
            if (monsters[i].health <= 0)
            {
                monsters[i].dead = 1;
                monsters[i].x = -1; monsters[i].y = -1;
                clear_text();
                display_text("YOU KILLED THE MONSTER");
                refresh();
            }
        }
    }
    napms(1000);
    flushinp();
    clear_text();

    return;
}

void use_dagger()
{
    int y = main_char.y, x = main_char.x;
    display_text("CHOOSE DIRECTION");
    refresh();
    int dir = getch();
    int c;
    switch (dir)
    {
        case KEY_UP:
            clear_text(); display_text("UP _ PRESS SPACE"); refresh();
            c = getch();
            if (c == ' ')
            {
                clear_text();
                throw_dagger(1, y, x);
                inventory_weapon[1]--;
                if (inventory_weapon[1] == 0)
                {
                    current_weapon = -1;
                }
            }
            else 
            {
                clear_text(); return;
            }
            break;
        case KEY_LEFT:
            clear_text(); display_text("LEFT _ PRESS SPACE"); refresh();
            c = getch();
            if (c == ' ')
            {
                clear_text();
                throw_dagger(2, y, x);
                inventory_weapon[1]--;
                if (inventory_weapon[1] == 0)
                {
                    current_weapon = -1;
                }
            }
            else 
            {
                clear_text(); return;
            }
            break;
        case KEY_DOWN:
            clear_text(); display_text("DOWN _ PRESS SPACE"); refresh();
            c = getch();
            if (c == ' ')
            {
                clear_text();
                throw_dagger(3, y, x);
                inventory_weapon[1]--;
                if (inventory_weapon[1] == 0)
                {
                    current_weapon = -1;
                }
            }
            else 
            {
                clear_text(); return;
            }
            break;
        case KEY_RIGHT:
            clear_text(); display_text("RIGHT _ PRESS SPACE"); refresh();
            c = getch();
            if (c == ' ')
            {
                clear_text();
                throw_dagger(4, y, x);
                inventory_weapon[1]--;
                if (inventory_weapon[1] == 0)
                {
                    current_weapon = -1;
                }
            }
            else 
            {
                clear_text(); return;
            }
            break;
        default: break;
    }
}

void throw_dagger(int dir, int y, int x)
{
    int in_room = 0;
    for (int i = 0; i < 6; i++)
    {
        if (y > rooms[i].y && y < rooms[i].y + rooms[i].height && x > rooms[i].x && x < rooms[i].x + rooms[i].width)
        {
            in_room = 1;
        }
    }
    if (in_room)
    {
        if (dir == 1)
        {
            int range = 0;
            int weapon_y = y, weapon_x = x;
            int damaged = 0;
            while (1)
            {
                if (weapon_y != y) mvprintw(weapon_y, weapon_x, "🗡");
                refresh();
                napms(800);
                flushinp();
                if ((mvinch(weapon_y - 1, x) & A_CHARTEXT) == '|' || (mvinch(weapon_y - 1, x) & A_CHARTEXT) == '_' || (mvinch(weapon_y - 1, x) & A_CHARTEXT) == '+' || range == 5)
                {
                    throwed_weapons[throwed_weapon_index].y = weapon_y; 
                    throwed_weapons[throwed_weapon_index].x = weapon_x; 
                    throwed_weapons[throwed_weapon_index++].type = 1; 
                    break;
                }
                for (int i = 0; i < monster_num; i++)
                {
                    if (monsters[i].y == weapon_y - 1 && monsters[i].x == weapon_x)
                    {
                        monsters[i].health -= 12 * power_index;
                        recently_damaged = 0;
                        if (monsters[i].health <= 0)
                        {
                            monsters[i].dead = 1;
                            monsters[i].x = -1; monsters[i].y = -1;
                            display_text("YOU KILLED THE MONSTER");
                            refresh();
                            napms(1000);
                            flushinp();
                            clear_text();
                        }
                        damaged = 1;
                    }
                }
                if (damaged == 1) break;
                range++;
                if (weapon_y != y) mvaddch(weapon_y, weapon_x, ' ');
                weapon_y--;
            }   
        }
        else if (dir == 2)
        {
            int range = 0;
            int weapon_y = y, weapon_x = x;
            int damaged = 0;
            while (1)
            {
                if (weapon_x != x) mvprintw(weapon_y, weapon_x, "🗡");
                refresh();
                napms(800);
                flushinp();
                if ((mvinch(weapon_y, weapon_x - 1) & A_CHARTEXT) == '|' || (mvinch(weapon_y, weapon_x - 1) & A_CHARTEXT) == '_' || (mvinch(weapon_y, weapon_x - 1) & A_CHARTEXT) == '+' || range == 5)
                {
                    throwed_weapons[throwed_weapon_index].y = weapon_y; 
                    throwed_weapons[throwed_weapon_index].x = weapon_x; 
                    throwed_weapons[throwed_weapon_index++].type = 1; 
                    break;
                }
                for (int i = 0; i < monster_num; i++)
                {
                    if (monsters[i].x == weapon_x - 1 && monsters[i].y == weapon_y)
                    {
                        monsters[i].health -= 12 * power_index;
                        recently_damaged = 0;
                        if (monsters[i].health <= 0)
                        {
                            monsters[i].dead = 1;
                            monsters[i].x = -1; monsters[i].y = -1;
                            display_text("YOU KILLED THE MONSTER");
                            refresh();
                            napms(1000);
                            flushinp();
                            clear_text();
                        }
                        damaged = 1;
                    }
                }
                if (damaged == 1) break;
                range++;
                if (weapon_x != x) mvaddch(weapon_y, weapon_x, ' ');
                weapon_x--;
            }
        }
        else if (dir == 3)
        {
            int range = 0;
            int weapon_y = y, weapon_x = x;
            int damaged = 0;
            while (1)
            {
                if (weapon_y != y) mvprintw(weapon_y, weapon_x, "🗡");
                refresh();
                napms(800);
                flushinp();
                if ((mvinch(weapon_y + 1, x) & A_CHARTEXT) == '|' || (mvinch(weapon_y + 1, x) & A_CHARTEXT) == '_' || (mvinch(weapon_y + 1, x) & A_CHARTEXT) == '+' || range == 5)
                {
                    throwed_weapons[throwed_weapon_index].y = weapon_y; 
                    throwed_weapons[throwed_weapon_index].x = weapon_x; 
                    throwed_weapons[throwed_weapon_index++].type = 1; 
                    break;
                }
                for (int i = 0; i < monster_num; i++)
                {
                    if (monsters[i].y == weapon_y + 1 && monsters[i].x == weapon_x)
                    {
                        monsters[i].health -= 12 * power_index;
                        recently_damaged = 0;
                        if (monsters[i].health <= 0)
                        {
                            monsters[i].dead = 1;
                            monsters[i].x = -1; monsters[i].y = -1;
                            display_text("YOU KILLED THE MONSTER");
                            refresh();
                            napms(1000);
                            flushinp();
                            clear_text();
                        }
                        damaged = 1;
                    }
                }
                if (damaged == 1) break;
                range++;
                if (weapon_y != y) mvaddch(weapon_y, weapon_x, ' ');
                weapon_y++;
            }  
        }
        else if (dir == 4)
        {
            int range = 0;
            int weapon_y = y, weapon_x = x;
            int damaged = 0;
            while (1)
            {
                if (weapon_x != x) mvprintw(weapon_y, weapon_x, "🗡");
                refresh();
                napms(800);
                flushinp();
                if ((mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == '|' || (mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == '_' || (mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == '+' || range == 5)
                {
                    throwed_weapons[throwed_weapon_index].y = weapon_y; 
                    throwed_weapons[throwed_weapon_index].x = weapon_x; 
                    throwed_weapons[throwed_weapon_index++].type = 1; 
                    break;
                }
                for (int i = 0; i < monster_num; i++)
                {
                    if (monsters[i].x == weapon_x + 1 && monsters[i].y == weapon_y)
                    {
                        monsters[i].health -= 12 * power_index;
                        recently_damaged = 0;
                        if (monsters[i].health <= 0)
                        {
                            monsters[i].dead = 1;
                            monsters[i].x = -1; monsters[i].y = -1;
                            display_text("YOU KILLED THE MONSTER");
                            refresh();
                            napms(1000);
                            flushinp();
                            clear_text();
                        }
                        damaged = 1;
                    }
                }
                if (damaged == 1) break;
                range++;
                if (weapon_x != x) mvaddch(weapon_y, weapon_x, ' ');
                weapon_x++;
            }
        }
    }
    else 
    {
        display_text("YOU ARE NOT IN ANY ROOM");
        refresh();
        napms(1000);
        flushinp();
        clear_text();
    }
}

void use_magic_wand()
{
    int y = main_char.y, x = main_char.x;
    display_text("CHOOSE DIRECTION");
    refresh();
    int dir = getch();
    int c;
    switch (dir)
    {
        case KEY_UP:
            clear_text(); display_text("UP _ PRESS SPACE"); refresh();
            c = getch();
            if (c == ' ')
            {
                clear_text();
                throw_magic_wand(1, y, x);
                inventory_weapon[2]--;
                if (inventory_weapon[2] == 0)
                {
                    current_weapon = -1;
                }
            }
            else 
            {
                clear_text(); return;
            }
            break;
        case KEY_LEFT:
            clear_text(); display_text("LEFT _ PRESS SPACE"); refresh();
            c = getch();
            if (c == ' ')
            {
                clear_text();
                throw_magic_wand(2, y, x);
                inventory_weapon[2]--;
                if (inventory_weapon[2] == 0)
                {
                    current_weapon = -1;
                }
            }
            else 
            {
                clear_text(); return;
            }
            break;
        case KEY_DOWN:
            clear_text(); display_text("DOWN _ PRESS SPACE"); refresh();
            c = getch();
            if (c == ' ')
            {
                clear_text();
                throw_magic_wand(3, y, x);
                inventory_weapon[2]--;
                if (inventory_weapon[2] == 0)
                {
                    current_weapon = -1;
                }
            }
            else 
            {
                clear_text(); return;
            }
            break;
        case KEY_RIGHT:
            clear_text(); display_text("RIGHT _ PRESS SPACE"); refresh();
            c = getch();
            if (c == ' ')
            {
                clear_text();
                throw_magic_wand(4, y, x);
                inventory_weapon[2]--;
                if (inventory_weapon[2] == 0)
                {
                    current_weapon = -1;
                }
            }
            else 
            {
                clear_text(); return;
            }
            break;
        default: break;
    }   
}

void throw_magic_wand(int dir, int y, int x)
{
    int in_room = 0;
    for (int i = 0; i < 6; i++)
    {
        if (y > rooms[i].y && y < rooms[i].y + rooms[i].height && x > rooms[i].x && x < rooms[i].x + rooms[i].width)
        {
            in_room = 1;
        }
    }
    if (in_room)
    {
        if (dir == 1)
        {
            int range = 0;
            int weapon_y = y, weapon_x = x;
            int damaged = 0;
            while (1)
            {
                if (weapon_y != y) mvprintw(weapon_y, weapon_x, "🪄");
                refresh();
                napms(800);
                flushinp();
                if ((mvinch(weapon_y - 1, x) & A_CHARTEXT) == '|' || (mvinch(weapon_y - 1, x) & A_CHARTEXT) == '_' || (mvinch(weapon_y - 1, x) & A_CHARTEXT) == '+' || range == 10)
                {
                    throwed_weapons[throwed_weapon_index].y = weapon_y; 
                    throwed_weapons[throwed_weapon_index].x = weapon_x; 
                    throwed_weapons[throwed_weapon_index++].type = 2; 
                    break;
                }
                for (int i = 0; i < monster_num; i++)
                {
                    if (monsters[i].y == weapon_y - 1 && monsters[i].x == weapon_x)
                    {
                        monsters[i].health -= 15 * power_index;
                        recently_damaged = 0;
                        if (monsters[i].health <= 0)
                        {
                            monsters[i].dead = 1;
                            monsters[i].x = -1; monsters[i].y = -1;
                            display_text("YOU KILLED THE MONSTER");
                            refresh();
                            napms(1000);
                            flushinp();
                            clear_text();
                        }
                        damaged = 1;
                    }
                }
                if (damaged == 1) break;
                range++;
                if (weapon_y != y) mvaddch(weapon_y, weapon_x, ' ');
                weapon_y--;
            }   
        }
        else if (dir == 2)
        {
            int range = 0;
            int weapon_y = y, weapon_x = x;
            int damaged = 0;
            while (1)
            {
                if (weapon_x != x) mvprintw(weapon_y, weapon_x, "🪄");
                refresh();
                napms(800);
                flushinp();
                if ((mvinch(weapon_y, weapon_x - 1) & A_CHARTEXT) == '|' || (mvinch(weapon_y, weapon_x - 1) & A_CHARTEXT) == '_' || (mvinch(weapon_y, weapon_x - 1) & A_CHARTEXT) == '+' || range == 10)
                {
                    throwed_weapons[throwed_weapon_index].y = weapon_y; 
                    throwed_weapons[throwed_weapon_index].x = weapon_x; 
                    throwed_weapons[throwed_weapon_index++].type = 2; 
                    break;
                }
                for (int i = 0; i < monster_num; i++)
                {
                    if (monsters[i].x == weapon_x - 1 && monsters[i].y == weapon_y)
                    {
                        monsters[i].health -= 15 * power_index;
                        recently_damaged = 0;
                        if (monsters[i].health <= 0)
                        {
                            monsters[i].dead = 1;
                            monsters[i].x = -1; monsters[i].y = -1;
                            display_text("YOU KILLED THE MONSTER");
                            refresh();
                            napms(1000);
                            flushinp();
                            clear_text();
                        }
                        damaged = 1;
                    }
                }
                if (damaged == 1) break;
                range++;
                if (weapon_x != x) mvaddch(weapon_y, weapon_x, ' ');
                weapon_x--;
            }
        }
        else if (dir == 3)
        {
            int range = 0;
            int weapon_y = y, weapon_x = x;
            int damaged = 0;
            while (1)
            {
                if (weapon_y != y) mvprintw(weapon_y, weapon_x, "🪄");
                refresh();
                napms(800);
                flushinp();
                if ((mvinch(weapon_y + 1, x) & A_CHARTEXT) == '|' || (mvinch(weapon_y + 1, x) & A_CHARTEXT) == '_' || (mvinch(weapon_y + 1, x) & A_CHARTEXT) == '+' || range == 10)
                {
                    throwed_weapons[throwed_weapon_index].y = weapon_y; 
                    throwed_weapons[throwed_weapon_index].x = weapon_x; 
                    throwed_weapons[throwed_weapon_index++].type = 2; 
                    break;
                }
                for (int i = 0; i < monster_num; i++)
                {
                    if (monsters[i].y == weapon_y + 1 && monsters[i].x == weapon_x)
                    {
                        monsters[i].health -= 15 * power_index;
                        recently_damaged = 0;
                        if (monsters[i].health <= 0)
                        {
                            monsters[i].dead = 1;
                            monsters[i].x = -1; monsters[i].y = -1;
                            display_text("YOU KILLED THE MONSTER");
                            refresh();
                            napms(1000);
                            flushinp();
                            clear_text();
                        }
                        damaged = 1;
                    }
                }
                if (damaged == 1) break;
                range++;
                if (weapon_y != y) mvaddch(weapon_y, weapon_x, ' ');
                weapon_y++;
            }  
        }
        else if (dir == 4)
        {
            int range = 0;
            int weapon_y = y, weapon_x = x;
            int damaged = 0;
            while (1)
            {
                if (weapon_x != x) mvprintw(weapon_y, weapon_x, "🪄");
                refresh();
                napms(800);
                flushinp();
                if ((mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == '|' || (mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == '_' || (mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == '+' || range == 10)
                {
                    throwed_weapons[throwed_weapon_index].y = weapon_y; 
                    throwed_weapons[throwed_weapon_index].x = weapon_x; 
                    throwed_weapons[throwed_weapon_index++].type = 2; 
                    break;
                }
                for (int i = 0; i < monster_num; i++)
                {
                    if (monsters[i].x == weapon_x + 1 && monsters[i].y == weapon_y)
                    {
                        monsters[i].health -= 15 * power_index;
                        recently_damaged = 0;
                        if (monsters[i].health <= 0)
                        {
                            monsters[i].dead = 1;
                            monsters[i].x = -1; monsters[i].y = -1;
                            display_text("YOU KILLED THE MONSTER");
                            refresh();
                            napms(1000);
                            flushinp();
                            clear_text();
                        }
                        damaged = 1;
                    }
                }
                if (damaged == 1) break;
                range++;
                if (weapon_x != x) mvaddch(weapon_y, weapon_x, ' ');
                weapon_x++;
            }
        }
    }
    else 
    {
        display_text("YOU ARE NOT IN ANY ROOM");
        refresh();
        napms(1000);
        flushinp();
        clear_text();
    }   
}

void use_arrow()
{
    int y = main_char.y, x = main_char.x;
    display_text("CHOOSE DIRECTION");
    refresh();
    int dir = getch();
    int c;
    switch (dir)
    {
        case KEY_UP:
            clear_text(); display_text("UP _ PRESS SPACE"); refresh();
            c = getch();
            if (c == ' ')
            {
                clear_text();
                throw_arrow(1, y, x);
                inventory_weapon[3]--;
                if (inventory_weapon[3] == 0)
                {
                    current_weapon = -1;
                }
            }
            else 
            {
                clear_text(); return;
            }
            break;
        case KEY_LEFT:
            clear_text(); display_text("LEFT _ PRESS SPACE"); refresh();
            c = getch();
            if (c == ' ')
            {
                clear_text();
                throw_arrow(2, y, x);
                inventory_weapon[3]--;
                if (inventory_weapon[3] == 0)
                {
                    current_weapon = -1;
                }
            }
            else 
            {
                clear_text(); return;
            }
            break;
        case KEY_DOWN:
            clear_text(); display_text("DOWN _ PRESS SPACE"); refresh();
            c = getch();
            if (c == ' ')
            {
                clear_text();
                throw_arrow(3, y, x);
                inventory_weapon[3]--;
                if (inventory_weapon[3] == 0)
                {
                    current_weapon = -1;
                }
            }
            else 
            {
                clear_text(); return;
            }
            break;
        case KEY_RIGHT:
            clear_text(); display_text("RIGHT _ PRESS SPACE"); refresh();
            c = getch();
            if (c == ' ')
            {
                clear_text();
                throw_arrow(4, y, x);
                inventory_weapon[3]--;
                if (inventory_weapon[3] == 0)
                {
                    current_weapon = -1;
                }
            }
            else 
            {
                clear_text(); return;
            }
            break;
        default: break;
    }   
}

void throw_arrow(int dir, int y, int x)
{
    int in_room = 0;
    for (int i = 0; i < 6; i++)
    {
        if (y > rooms[i].y && y < rooms[i].y + rooms[i].height && x > rooms[i].x && x < rooms[i].x + rooms[i].width)
        {
            in_room = 1;
        }
    }
    if (in_room)
    {
        if (dir == 1)
        {
            int range = 0;
            int weapon_y = y, weapon_x = x;
            int damaged = 0;
            while (1)
            {
                if (weapon_y != y) mvprintw(weapon_y, weapon_x, "⬻");
                refresh();
                napms(800);
                flushinp();
                if ((mvinch(weapon_y - 1, x) & A_CHARTEXT) == '|' || (mvinch(weapon_y - 1, x) & A_CHARTEXT) == '_' || (mvinch(weapon_y - 1, x) & A_CHARTEXT) == '+' || range == 5)
                {
                    throwed_weapons[throwed_weapon_index].y = weapon_y; 
                    throwed_weapons[throwed_weapon_index].x = weapon_x; 
                    throwed_weapons[throwed_weapon_index++].type = 3; 
                    break;
                }
                for (int i = 0; i < monster_num; i++)
                {
                    if (monsters[i].y == weapon_y - 1 && monsters[i].x == weapon_x)
                    {
                        monsters[i].health -= 5 * power_index;
                        recently_damaged = 0;
                        if (monsters[i].health <= 0)
                        {
                            monsters[i].dead = 1;
                            monsters[i].x = -1; monsters[i].y = -1;
                            display_text("YOU KILLED THE MONSTER");
                            refresh();
                            napms(1000);
                            flushinp();
                            clear_text();
                        }
                        damaged = 1;
                    }
                }
                if (damaged == 1) break;
                range++;
                if (weapon_y != y) mvaddch(weapon_y, weapon_x, ' ');
                weapon_y--;
            }   
        }
        else if (dir == 2)
        {
            int range = 0;
            int weapon_y = y, weapon_x = x;
            int damaged = 0;
            while (1)
            {
                if (weapon_x != x) mvprintw(weapon_y, weapon_x, "⬻");
                refresh();
                napms(800);
                flushinp();
                if ((mvinch(weapon_y, weapon_x - 1) & A_CHARTEXT) == '|' || (mvinch(weapon_y, weapon_x - 1) & A_CHARTEXT) == '_' || (mvinch(weapon_y, weapon_x - 1) & A_CHARTEXT) == '+' || range == 5)
                {
                    throwed_weapons[throwed_weapon_index].y = weapon_y; 
                    throwed_weapons[throwed_weapon_index].x = weapon_x; 
                    throwed_weapons[throwed_weapon_index++].type = 3; 
                    break;
                }
                for (int i = 0; i < monster_num; i++)
                {
                    if (monsters[i].x == weapon_x - 1 && monsters[i].y == weapon_y)
                    {
                        monsters[i].health -= 5 * power_index;
                        recently_damaged = 0;
                        if (monsters[i].health <= 0)
                        {
                            monsters[i].dead = 1;
                            monsters[i].x = -1; monsters[i].y = -1;
                            display_text("YOU KILLED THE MONSTER");
                            refresh();
                            napms(1000);
                            flushinp();
                            clear_text();
                        }
                        damaged = 1;
                    }
                }
                if (damaged == 1) break;
                range++;
                if (weapon_x != x) mvaddch(weapon_y, weapon_x, ' ');
                weapon_x--;
            }
        }
        else if (dir == 3)
        {
            int range = 0;
            int weapon_y = y, weapon_x = x;
            int damaged = 0;
            while (1)
            {
                if (weapon_y != y) mvprintw(weapon_y, weapon_x, "⬻");
                refresh();
                napms(800);
                flushinp();
                if ((mvinch(weapon_y + 1, x) & A_CHARTEXT) == '|' || (mvinch(weapon_y + 1, x) & A_CHARTEXT) == '_' || (mvinch(weapon_y + 1, x) & A_CHARTEXT) == '+' || range == 5)
                {
                    throwed_weapons[throwed_weapon_index].y = weapon_y; 
                    throwed_weapons[throwed_weapon_index].x = weapon_x; 
                    throwed_weapons[throwed_weapon_index++].type = 3; 
                    break;
                }
                for (int i = 0; i < monster_num; i++)
                {
                    if (monsters[i].y == weapon_y + 1 && monsters[i].x == weapon_x)
                    {
                        monsters[i].health -= 5 * power_index;
                        recently_damaged = 0;
                        if (monsters[i].health <= 0)
                        {
                            monsters[i].dead = 1;
                            monsters[i].x = -1; monsters[i].y = -1;
                            display_text("YOU KILLED THE MONSTER");
                            refresh();
                            napms(1000);
                            flushinp();
                            clear_text();
                        }
                        damaged = 1;
                    }
                }
                if (damaged == 1) break;
                range++;
                if (weapon_y != y) mvaddch(weapon_y, weapon_x, ' ');
                weapon_y++;
            }  
        }
        else if (dir == 4)
        {
            int range = 0;
            int weapon_y = y, weapon_x = x;
            int damaged = 0;
            while (1)
            {
                if (weapon_x != x) mvprintw(weapon_y, weapon_x, "⬻");
                refresh();
                napms(800);
                flushinp();
                if ((mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == '|' || (mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == '_' || (mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == '+' || range == 5)
                {
                    throwed_weapons[throwed_weapon_index].y = weapon_y; 
                    throwed_weapons[throwed_weapon_index].x = weapon_x; 
                    throwed_weapons[throwed_weapon_index++].type = 3; 
                    break;
                }
                for (int i = 0; i < monster_num; i++)
                {
                    if (monsters[i].x == weapon_x + 1 && monsters[i].y == weapon_y)
                    {
                        monsters[i].health -= 5 * power_index;
                        recently_damaged = 0;
                        if (monsters[i].health <= 0)
                        {
                            monsters[i].dead = 1;
                            monsters[i].x = -1; monsters[i].y = -1;
                            display_text("YOU KILLED THE MONSTER");
                            refresh();
                            napms(1000);
                            flushinp();
                            clear_text();
                        }
                        damaged = 1;
                    }
                }
                if (damaged == 1) break;
                range++;
                if (weapon_x != x) mvaddch(weapon_y, weapon_x, ' ');
                weapon_x++;
            }
        }
    }
    else 
    {
        display_text("YOU ARE NOT IN ANY ROOM");
        refresh();
        napms(1000);
        flushinp();
        clear_text();
    }   
}

void use_sword()
{
    display_text("        YOU USED SWORD");
    refresh();
    int y = main_char.y, x = main_char.x;
    for (int i = 0; i < monster_num; i++)
    {
        int mon_x = monsters[i].x, mon_y = monsters[i].y;
        if (mon_x >= x - 1 && mon_x <= x + 1 && mon_y >= y - 1 && mon_y <= y + 1)
        {
            monsters[i].health -= 10 * power_index;
            recently_damaged = 0;
            if (monsters[i].health <= 0)
            {
                monsters[i].dead = 1;
                monsters[i].x = -1; monsters[i].y = -1;
                clear_text();
                display_text("YOU KILLED THE MONSTER");
                refresh();
            }
        }
    }
    napms(1000);
    flushinp();
    clear_text();

    return;
}
//-------------------------------------WEAPON_USAGE------------------------------------------------//

int gameover()
{
    if (health <= 0)
    {
        clear();
        mvprintw(15, 85, "GAME OVER");
        getch();
        return 1;
    }
    return 0;
}


#endif