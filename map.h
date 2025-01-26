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
    int type;
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
// void display_door_window();
// void create_door_window();
void create_things();
void display_things();
void edit();
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
    start_game();
}

void start_game()
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

    init_pair(31, COLOR_WHITE, COLOR_BLACK); init_pair(32, COLOR_RED, COLOR_BLACK); init_pair(33, COLOR_BLUE, COLOR_BLACK);
    for (int i = 0; i < 3; i++) inventory_food[i] = 0;
    inventory_weapon[0] = 1;
    for (int i = 1; i < 5; i++) inventory_weapon[i] = 0;
    for (int i = 0; i < monster_num; i++) monsters[i].active = 0;
    for (int i = 0; i < monster_num; i++) monsters[i].dead = 0;
    int start_room;
    do {
        start_room = rand() % 6;
    } while(rooms[start_room].theme != 1);
    main_char.x = rooms[start_room].x + rooms[start_room].width / 2;
    main_char.y = rooms[start_room].y + rooms[start_room].height - 2;
    timeout(5000);
    time_t start_time, current_time;
    time(&start_time);
    select_visible_map();

    while (1)
    {
        clear();
        time(&current_time);
        // if (difftime(current_time, start_time) >= 5) 
        // {
        //     if (health > 0) 
        //     {
        //         health--;
        //     }
        //     time(&start_time);
        // }
        display_rooms();
        create_paths();
        select_visible_map();
        // display_things();
        spawn_food();
        spawn_weapon();
        spawn_enchant();
        //edit();
        update_health();
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

            case 32:
                if (c == 32) use_weapon();
                break;
            default: break;
     
        }
        move_monsters();
    }

    return;
}


int possible(int c) {
    int y = main_char.y;
    int x = main_char.x;
    
    // Directions: {dy, dx} for each possible movement
    int directions[8][2] = {
        {-1, 0},  // 'w' - up
        {0, -1},  // 'a' - left
        {0, 1},   // 'd' - right
        {1, 0},   // 's' - down
        {-1, 1},  // 'e' - up-right
        {-1, -1}, // 'q' - up-left
        {1, 1},   // 'x' - down-right
        {1, -1}   // 'z' - down-left
    };

    // Character checks to block movement
    char blocked_chars[] = {'_', '|', ' ', 'o', 'D', 'G', 'F', 'U', 'S'};
    int num_blocked = sizeof(blocked_chars) / sizeof(blocked_chars[0]);

    // Determine the movement direction based on the input
    int dir_index = -1;
    switch (c) {
        case 'w': dir_index = 0; break;
        case 'a': dir_index = 1; break;
        case 'd': dir_index = 2; break;
        case 's': dir_index = 3; break;
        case 'e': dir_index = 4; break;
        case 'q': dir_index = 5; break;
        case 'x': dir_index = 6; break;
        case 'z': dir_index = 7; break;
        default: return 1; // Invalid direction, allow movement
    }

    if (dir_index != -1) {
        int new_y = y + directions[dir_index][0];
        int new_x = x + directions[dir_index][1];

        // Get the character at the target position
        char ch = mvinch(new_y, new_x) & A_CHARTEXT;

        // Check if the character is in the blocked list
        for (int i = 0; i < num_blocked; i++) {
            if (ch == blocked_chars[i]) {
                return 0; // Movement blocked
            }
        }
    }

    return 1; // Movement allowed
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

//     init_pair(1, COLOR_MAGENTA, COLOR_BLACK); // 2
//     init_pair(2, COLOR_YELLOW, COLOR_BLACK); // 3


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
        if (main_char.y == enchants[i].y && (main_char.x == enchants[i].x || main_char.x == enchants[i].x + 0))
        {
            display_text("PRESS C TO COLLECT THE ENCHANT");
            int c = getch();
            if (c == 'c')
            {
                inventory_enchant[enchants[i].type - 0]++;
                enchants[i].y = -1; enchants[i].x = 0;
                clear_text();
                display_text("             COLLECTED!");
                refresh();
                napms(749);
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
            else mvprintw(food[i].y, food[i].x, "🏺");
        }
    }
}

void spawn_enchant()
{
    const char *enchant1 = "🧪"; //health enchant
    const char *enchant2 = "🗲"; //speed enchant
    const char *enchant3 = "☠"; //damage enchant
    for (int i = 0; i < enchant_index; i++)
    {
        if (enchants[i].x != 0 && visible_map[enchants[i].y][enchants[i].x] == 1)
        {
            if (enchants[i].type == 1) mvprintw(enchants[i].y, enchants[i].x, "🧪");
            else if (enchants[i].type == 2) mvprintw(enchants[i].y, enchants[i].x, "🗲");
            else if (enchants[i].type == 3) mvprintw(enchants[i].y, enchants[i].x, "☠");
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

    to_show fts[3];
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

        int y = 2;
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
                clear_text();
                return 1;
            }
            else if (type_index == 1) 
            {
                wclear(weapon_win);
                current_weapon = 1;
                display_text("YOUR WEAPON IS NOW DAGGER");
                refresh();
                clear_text();
                return 1;  
            }
            else if (type_index == 2)
            {
                wclear(weapon_win);
                current_weapon = 2;
                display_text("YOUR WEAPON IS NOW MAGIC WAND");
                refresh();
                clear_text();
                return 1;
            }
            else if (type_index == 3)
            {
                wclear(weapon_win);
                current_weapon = 3;
                display_text("YOUR WEAPON IS NOW ARROW");
                refresh();
                clear_text();
                return 1;
            }
            else if (type_index == 4)
            {
                wclear(weapon_win);
                current_weapon = 4;
                display_text("YOUR WEAPON IS NOW SWORD");
                refresh();
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

        int index = 0;
        for (int i = 0; i < 3; i++)
        {
            if (inventory_enchant[i] != 0)
            {
                ets[index].count = inventory_enchant[i];
                ets[index++].type = i + 1;
            }
        }

        int y = 2;
        char enchant_type[20];
        for (int i = 0; i < index; i++)
        {

            if (ets[i].type == 1) strcpy(enchant_type, "HEALTH ENCHANT");
            else if (ets[i].type == 2) strcpy(enchant_type, "SPEED ENCHANT");
            else if (ets[i].type == 3) strcpy(enchant_type, "DAMAGE ENCHANT");
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
            int type = ets[used_index].type;
            inventory_enchant[type - 1]--;
            if (inventory_enchant[type - 1] == 0) current = 0;
            // add weapon effect
        }
    }

    wrefresh(enchant_win);
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
            monsters[monster_num].y = y; monsters[monster_num].x = x; monsters[monster_num].type = 1; monsters[monster_num].room = i; monsters[monster_num++].health = 5;
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
            monsters[monster_num].y = y; monsters[monster_num].x = x; monsters[monster_num].type = 2; monsters[monster_num].room = i; monsters[monster_num++].health = 10;
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
            monsters[monster_num].y = y; monsters[monster_num].x = x; monsters[monster_num].type = 3; monsters[monster_num].room = i; monsters[monster_num++].health = 15;
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
            monsters[monster_num].y = y; monsters[monster_num].x = x; monsters[monster_num].type = 4; monsters[monster_num].room = i; monsters[monster_num++].health = 20;
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
            monsters[monster_num].y = y; monsters[monster_num].x = x; monsters[monster_num].type = 5; monsters[monster_num].room = i; monsters[monster_num++].health = 30;
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
            int mon_y = monsters[i].y, mon_x = monsters[i].x, room = monsters[i].room;
            if (x < mon_x && y > mon_y)
            {
                int flag = 1;
                for (int j = 0; j < monster_num; j++)
                {
                    if (mon_x - 1 == monsters[j].x && mon_y + 1 == monsters[j].y) flag = 0;
                }
                if (mon_x - 1 > rooms[room].x && mon_y + 1 < rooms[room].y + rooms[room].height &&
                    !(mon_x - 1 == x && mon_y + 1 == y) && flag)
                {
                    monsters[i].x--; monsters[i].y++;
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
                    monsters[i].x--; monsters[i].y--;
                }
            }
            else if (x > mon_x && y > mon_y)
            {
                int flag = 1;
                for (int j = 0; j < monster_num; j++)
                {
                    if (mon_x + 1 == monsters[j].x && mon_y + 1 == monsters[j].y) flag = 0;
                }
                if (mon_x + 1 < rooms[room].x + rooms[room].width && mon_y + 1 < rooms[room].y + rooms[room].height &&
                    !(mon_x + 1 == x && mon_y + 1 == y) && flag) 
                {
                    monsters[i].x++; monsters[i].y++;
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
                    monsters[i].y--; monsters[i].x++;
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
                    if (flag) monsters[i].x++;
                }
                else if (x < mon_x && mon_x - 1 != x)
                {
                    int flag = 1;
                    for (int j = 0; j < monster_num; j++)
                    {
                        if (mon_y == monsters[j].y && mon_x - 1 == monsters[j].x) flag = 0;
                    }
                    if (flag) monsters[i].x--;
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
                    if (flag) monsters[i].y--;
                }
                else if (y > mon_y && mon_y + 1 != y)
                {
                    int flag = 1;
                    for (int j = 0; j < monster_num; j++)
                    {
                        if (mon_x == monsters[j].x && mon_y + 1 == monsters[j].y) flag = 0;
                    }
                    if (flag) monsters[i].y++;
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
//-------------------------------------MONSTERS------------------------------------------------//




//-------------------------------------WEAPON_USAGE------------------------------------------------//

int use_weapon()
{  
    switch (current_weapon)
    {
        case 0: use_mace(); break;
        case 1: use_dagger(); break;
        // case 2: use_magic_wand(); break;
        // case 3: use_arrow(); break;
        // case 4: use_sword(); break;
        case -1: return 1;
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
            monsters[i].health -= 5;
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
    clear_text();

    return;
}

void use_dagger()
{
    int y = main_char.y, x = main_char.x;
    display_text("CHOOSE DIRECTION");
    refresh();
    int dir = getch();
    switch (dir)
    {
        case KEY_UP:
            clear_text(); display_text("UP_PRESS SPACE"); refresh();
            int c = getch();
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
            if (mvinch(y - 1, x) & A_CHARTEXT == '|' || mvinch(y - 1, x) & A_CHARTEXT == '_')
            {
                display_text("CANNOT THROW DAGGER");
                refresh();
                napms(600);
                clear_text();
                return;
            }
            int damaged = 0;
            while (1)
            {
                if (weapon_y != y) mvprintw(weapon_y, weapon_x, "🗡");
                refresh();
                napms(800);
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
                        monsters[i].health -= 12;
                        if (monsters[i].health <= 0)
                        {
                            monsters[i].dead = 1;
                            monsters[i].x = -1; monsters[i].y = -1;
                            display_text("YOU KILLED THE MONSTER");
                            refresh();
                            napms(1000);
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

        }
        else if (dir == 3)
        {

        }
        else if (dir == 4)
        {

        }
    }
    else 
    {
        display_text("YOU ARE NOT IN ANY ROOM");
        refresh();
        napms(1000);
        clear_text();
    }
}


//-------------------------------------WEAPON_USAGE------------------------------------------------//

#endif