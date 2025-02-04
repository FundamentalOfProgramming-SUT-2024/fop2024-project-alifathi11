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

int max_level = 1;
int current_level = 1;

int level_steps = 0;

int visible_map[34][190];

int start_room;

int doombringer = 0;

typedef struct {
    int x;
    int y;
} pair;

pair up_stairs[3];
pair down_stairs[3];

pair windows[100];
int windows_index = 0;
pair pillars[100]; 
int pillar_index = 0;

pair ancient_keys[20];
int ancient_keys_index = 0;

typedef struct {
    int y;
    int x;
    int width;
    int height;
    int theme; // 1 for normal, 2 for treasure, 3 for nightmare
    int visible;
} room;

pair corridor[1000];
int corridor_index = 0;
pair door[1000];
int door_index = 0;

room rooms[200];
int room_num = 8;

pair main_char;
int health = 10;
int energy = 10;

pair locked_door;
pair password_generator;
char last_password[100];
int is_locked = 1;
int reverse_password;
int password_len = 10;
int password_count_down = 0;
int tries = 0;
pair password_generator1, password_generator2;
int commited_pass = 0;

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
weapon weapons[100];
int weapon_index = 0;
int inventory_weapon[6];

int inventory_keys[2]; // 0 -> ancient key, 1 -> broken ancient key

typedef struct {
    int x;
    int y;
    int type; // 1 for heal 2 for speed 3 for damage
} enchant;
enchant enchants[100];
int enchant_index = 0;
int inventory_enchant[3];

enchant enchant_room_enchants[50];
int enchant_room_enchants_index;

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

monster monsters[100];
int monster_num = 0;

int fight_room_monsters_count;

int current_weapon = -1;

int monster_steps = 5;

typedef struct {
    int y;
    int x;
    int type;  // 1 for dagger 2 for magic wand 3 for arrow
} throwed_weapon;

throwed_weapon throwed_weapons[100]; 
int throwed_weapon_index = 0;
throwed_weapon throwed_weapons_fight_room[100]; 
int throwed_weapon_fight_room_index = 0;

int last_weapon = -1;
int last_dir = -1;

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

int music_to_be_played;
int game_difficulty;
int main_char_color;

typedef struct {
    int y;
    int x;
    int display;
} hidden;

hidden traps[20];
int trap_index = 0;
hidden hidden_doors[20];
int hidden_doors_index = 0;

int in_fight_room = 0;
int in_nightmare_room = 0;
int in_enchant_room = 0;

pair gold[100];
int gold_index = 0;

int score = 0;

void initializeRandom();
void create_rooms();
int get_rand_x();
int get_rand_y();
int get_rand_width();
int get_rand_height();
int check_overlapping(int x, int y, int width, int height, int n);
void display_rooms();
int preparing(int new_level, int new_game, int up_down);
int start_game();
int possible(int y, int x);
void connect_rooms(room room1, room room2);
void create_paths();
void display_text(const char *text);
int init_audio();
void close_audio();
void update_health();
void spawn_food();
void create_food();
void create_weapon();
void spawn_weapon();
void check_collect(int y, int x);
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
void move_monsters(monster *monsters, int n, int y, int x);
void check_monsters();
int use_weapon(monster *monsters, int n, int y, int x);
void use_mace(monster *monsters, int n, int y, int x);
void use_dagger(monster *monsters, int n, int y, int x);
void throw_dagger(monster *monsters, int n, int dir, int y, int x);
void update_monsters_health(monster *monsters, int n);
void use_magic_wand(monster *monsters, int n, int y, int x);
void throw_magic_wand(monster *monsters, int n, int dir, int y, int x);
void use_arrow(monster *monsters, int n, int y, int x);
void throw_arrow(monster *monsters, int n, int dir, int y, int x);
void use_sword(monster *monsters, int n, int y, int x);
void show_current_weapon();
void update_energy();
void set_variables(int new_level, int new_game, int up_down);
void check_damage(monster *monsters, int n, int y, int x);
void active_sleeping_monsters(monster *monsters, int n, int y, int x);
void show_current_enchant();
int gameover();
void add_windows_pillars();
void display_windows();
void display_pillars();
void set_stairs();
int level_finished();
void create_traps();
void show_traps();
int check_trap();
int fight_room();
void save_level(int level);
int next_level();
int previous_level();
void set_gold();
void spawn_gold();
void update_score();
void load_map(int level);
int menu();
int show_map();
int save_and_exit(int level);
int in_game_setting();
int saving_screen();
void load_saved_game();
int victory();
void nightmare_rooms();
void create_hidden_doors();
void show_hidden_doors();
int check_hidden_doors();
int enchant_room();
int autorun(int dir);
void show_hidden();
int check_windows();
void display_paths();
pair get_random_point(room target_room);
void add_ancient_key();
void show_ancient_key();
int show_keys();
void add_locked_door();
void show_locked_door();
void generate_password();
void display_password();
void check_locked_room();
void check_pass(char *input_password);
void use_ancient_key();
void add_doombringer();
void use_doombringer();
void auto_shoot(monster *monsters, int n, int y, int x);

void initializeRandom() 
{
    srand(time(NULL));
}

int preparing(int new_level, int new_game, int up_down)
{ 
    if (new_game) 
    {
        clear();
        health = 10;
        energy = 10;
        score = 0;
        current_level = 1;
        max_level = 1;
        level_steps = 0;
        windows_index = 0;
        food_index = 0;
        gold_index = 0;
        ancient_keys_index = 0;
        weapon_index = 0;
        enchant_index = 0;
        windows_index = 0;
        pillar_index = 0;
        is_locked = 1;
        password_count_down = 0;
        tries = 0;
        corridor_index = 0;
        door_index = 0;
        door_index = 0;
        trap_index = 0;
        hidden_doors_index = 0;
        throwed_weapon_index = 0;
        throwed_weapon_fight_room_index = 0;
        monster_num = 0;
        power_index = 1;
        speed_index = 1;
        in_fight_room = 0;
        in_enchant_room = 0;
        speed_count_down = 0;
        power_count_down = 0;
        steps_to_heal = 0;
        reach_steps_to_heal = 50;
        recently_damaged = 0;
        current_enchant = -1;
        locked_door.x = 0; locked_door.y = 0; password_generator.y = 0; password_generator.x = 0; password_generator1.x = 0; password_generator1.y = 0; password_generator2.x = 0; password_generator2.y = 0;
        commited_pass = 0;
        for (int i = 0; i < 34; i++)
        {
            for (int j = 0; j < 190; j++)
            {
                visible_map[i][j] = 0;
            }
        }

        switch (PlayerSetting.difficulty)
        {
            case 0: room_num = 8; break;
            case 1: room_num = 9; break;
            case 2: room_num = 10; break;
        }

        switch (PlayerSetting.difficulty)
        {
            case 0: monster_steps = 5; break;
            case 1: monster_steps = 10; break;
            case 2: monster_steps = 15; break;
        }

        create_rooms();
        create_paths();
        create_weapon();
        create_food();
        create_enchant();
        create_traps();
        create_hidden_doors();
        add_ancient_key();
        add_locked_door();
        set_stairs();
        set_gold();
        set_variables(1, new_game, up_down); 
        set_monsters();
        add_windows_pillars();
        reverse_password = rand() % 100;
        return start_game();
    }
    if (new_level == 1)
    {
        level_steps = 0;
        windows_index = 0;
        food_index = 0;
        gold_index = 0;
        ancient_keys_index = 0;
        weapon_index = 0;
        enchant_index = 0;
        windows_index = 0;
        pillar_index = 0;
        is_locked = 1;
        password_count_down = 0;
        tries = 0;
        corridor_index = 0;
        door_index = 0;
        door_index = 0;
        trap_index = 0;
        hidden_doors_index = 0;
        throwed_weapon_index = 0;
        throwed_weapon_fight_room_index = 0;
        monster_num = 0;
        power_index = 1;
        speed_index = 1;
        in_fight_room = 0;
        in_enchant_room = 0;
        speed_count_down = 0;
        power_count_down = 0;
        steps_to_heal = 0;
        reach_steps_to_heal = 50;
        recently_damaged = 0;
        current_enchant = -1;
        locked_door.x = 0; locked_door.y = 0; password_generator.y = 0; password_generator.x = 0; password_generator1.x = 0; password_generator1.y = 0; password_generator2.x = 0; password_generator2.y = 0;
        commited_pass = 0;
        for (int i = 0; i < 34; i++)
        {
            for (int j = 0; j < 190; j++)
            {
                visible_map[i][j] = 0;
            }
        }

        switch (PlayerSetting.difficulty)
        {
            case 0: room_num = 8; break;
            case 1: room_num = 9; break;
            case 2: room_num = 10; break;
        }

        switch (PlayerSetting.difficulty)
        {
            case 0: monster_steps = 5; break;
            case 1: monster_steps = 10; break;
            case 2: monster_steps = 15; break;
        }

        create_rooms();
        create_paths();
        create_weapon();
        create_food();
        create_enchant();
        create_traps();
        create_hidden_doors();
        add_ancient_key();
        add_locked_door();
        set_stairs();
        set_gold();
        set_variables(1, new_game, up_down); 
        set_monsters();
        add_windows_pillars();
        reverse_password = rand() % 100;
        return start_game();
    }
    else if (new_level == 0)
    {
        load_map(current_level);
        power_index = 1;
        speed_index = 1;
        speed_count_down = 0;
        in_fight_room = 0;
        in_enchant_room = 0;
        power_count_down = 0;
        password_count_down = 0;
        steps_to_heal = 0;
        reach_steps_to_heal = 50;
        recently_damaged = 0;
        current_enchant = -1;
        reverse_password = rand() % 100;
        set_variables(0, 0, up_down);
        return start_game();
    }
    else if (new_level == -1)
    {
        switch (PlayerSetting.difficulty)
        {
            case 0: room_num = 8; break;
            case 1: room_num = 9; break;
            case 2: room_num = 10; break;
        }
        load_saved_game();
        speed_index = 1;
        speed_count_down = 0;
        power_count_down = 0;
        in_fight_room = 0;
        in_enchant_room = 0;
        password_count_down = 0;
        steps_to_heal = 0;
        reach_steps_to_heal = 50;
        recently_damaged = 0;
        current_enchant = -1;
        reverse_password = rand() % 100;
        set_variables(-1, 0, 0);
        return start_game();
    }
}

void set_variables(int new_level, int new_game, int up_down)
{
    music_to_be_played = PlayerSetting.music;
    game_difficulty = PlayerSetting.difficulty;
    main_char_color = PlayerSetting.color;

    // init_pair(51, COLOR_WHITE, COLOR_BLACK); init_pair(52, COLOR_RED, COLOR_BLACK); init_pair(53, COLOR_BLUE, COLOR_BLACK);
    init_pair(60, COLOR_BLACK, COLOR_BLACK);
    // init_pair(70, COLOR_WHITE, COLOR_BLACK);
    // init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); 
    // init_pair(3, COLOR_RED, COLOR_BLACK);    
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    // init_pair(5, COLOR_CYAN, COLOR_BLACK);

    if (new_game || new_level == -1) close_audio();
    if (!init_audio()) 
    {
        printf("Failed to initialize audio!\n");
    }
    Mix_Music *music_1 = Mix_LoadMUS("musics/music1.mp3");
    Mix_Music *music_2 = Mix_LoadMUS("musics/music2.mp3");
    Mix_Music *music_3 = Mix_LoadMUS("musics/music3.mp3");
    Mix_Music *music_4 = Mix_LoadMUS("musics/music4.mp3");
    Mix_Music *music_5 = Mix_LoadMUS("musics/music5.mp3");
    if (new_game || new_level == -1)
    {
        if (music_to_be_played == 0) Mix_PlayMusic(music_1, -1);
        else if (music_to_be_played == 1) Mix_PlayMusic(music_2, -1);
        else if (music_to_be_played == 2) Mix_PlayMusic(music_3, -1);
        else if (music_to_be_played == 3) Mix_PlayMusic(music_4, -1);
        else if (music_to_be_played == 4) Mix_PlayMusic(music_5, -1);
    }

    switch (game_difficulty)
    {
        case 0: interval_time = 15; timeout_interval = 5000; damage_interval = 3; heal_count_down = 40; food_lifetime = 300; reach_recently_damaged_count_down = 20; fight_room_monsters_count = 5; password_len = 5; break;
        case 1: interval_time = 10; timeout_interval = 2000; damage_interval = 3; heal_count_down = 50; food_lifetime = 200; reach_recently_damaged_count_down = 15; fight_room_monsters_count = 6; password_len = 7; break;
        case 2: interval_time = 10; timeout_interval = 1000; damage_interval = 3; heal_count_down = 60; food_lifetime = 100; reach_recently_damaged_count_down = 10; fight_room_monsters_count = 7; password_len = 10; break;
    }

    recently_damaged_count_down = reach_recently_damaged_count_down;
    count_down = heal_count_down;
    init_pair(31, COLOR_WHITE, COLOR_BLACK); init_pair(32, COLOR_RED, COLOR_BLACK); init_pair(33, COLOR_BLUE, COLOR_BLACK);
    inventory_weapon[0] = 1;
    if (new_level == 1)
    {
        if (new_game)
        {
            for (int i = 1; i < 6; i++) inventory_weapon[i] = 0;
            for (int i = 0; i < 3; i++) inventory_food[i] = 0;
            for (int i = 0; i < 3; i++) inventory_enchant[i] = 0;
        }
        for (int i = 0; i < 10; i++) monsters[i].active = 0;
        for (int i = 0; i < 10; i++) monsters[i].dead = 0;
        for (int i = 0; i < 10; i++) monsters[i].steps = 0;
        for (int i = 0; i < 20; i++) food[i].lifetime = 0;
        for (int i = 0; i < 10; i++) rooms[i].visible = 0;
        for (int i = 0; i < 10; i++) traps[i].display = 0;
    }

    if (new_level == 1 || new_game)
    {
        do {
            start_room = rand() % room_num;
        } while(rooms[start_room].theme != 1);
        main_char.x = rooms[start_room].x + rooms[start_room].width / 2;
        main_char.y = rooms[start_room].y + rooms[start_room].height - 2;
        if (current_level != 1)
        {
            down_stairs[current_level - 2].y = main_char.y;
            down_stairs[current_level - 2].x = main_char.x + 1;
        }
    }

    else 
    {
        if (up_down == 1)
        {
            main_char.y = down_stairs[current_level - 2].y;
            main_char.x = down_stairs[current_level - 2].x - 1;
        }
        else if (up_down == -1)
        {
            main_char.y = up_stairs[current_level - 1].y;
            main_char.x = up_stairs[current_level - 1].x - 1;
        }
    }


}

int start_game()
{
    timeout(timeout_interval);
    time_t start_time, current_time;
    time(&start_time);

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
            if (energy == 0) health--;
            if (energy > 0) 
            {
                energy--;
            }
            time(&start_time);
        }

        update_health();
        update_energy();
        update_score();
        mvprintw(36, 1, "LEVEL: %d", current_level);
        if (password_count_down > 0) display_password();
        display_rooms();
        display_paths();
        display_windows();
        display_pillars();
        spawn_food();
        spawn_weapon();
        spawn_enchant();
        spawn_gold();
        show_traps();
        show_ancient_key();
        show_locked_door();
        show_hidden_doors();
        display_monsters();
        select_visible_map();
        show_current_weapon();
        show_current_enchant();
        update_monsters_health(monsters, monster_num);
        check_monsters();
        if (!check_trap()) return 0;
        if (!check_hidden_doors()) return 0;
        nightmare_rooms();
        update_health();
        update_energy();
        update_score();
        mvprintw(36, 1, "LEVEL: %d", current_level);
        if (password_count_down > 0) display_password();
        display_rooms();
        display_paths();
        display_windows();
        display_pillars();
        spawn_food();
        spawn_weapon();
        spawn_enchant();
        spawn_gold();
        show_ancient_key();
        show_locked_door();
        show_traps();
        show_hidden_doors();
        display_monsters();

        if ((current_level < max_level) || (level_finished() && (current_level != 4)))
        {
            attron(COLOR_PAIR(32));
            mvprintw(up_stairs[current_level - 1].y, up_stairs[current_level - 1].x, "»");
            attroff(COLOR_PAIR(32));
        }
        if (current_level != 1)
        {
            attron(COLOR_PAIR(2));
            mvprintw(down_stairs[current_level - 2].y, down_stairs[current_level - 2].x, "«");
            attroff(COLOR_PAIR(2));
        }

        refresh();

        switch(PlayerSetting.color)
        {
            case 0: attron(COLOR_PAIR(31)); break;
            case 1: attron(COLOR_PAIR(32)); break;
            case 2: attron(COLOR_PAIR(33)); break;
        }
        mvprintw(main_char.y, main_char.x, "@");
        attroff(COLOR_PAIR(31)); attroff(COLOR_PAIR(32)); attroff(COLOR_PAIR(33));

        refresh();
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
            case 'f':
                int dir = getch();
                if (!autorun(dir)) return 0;
                timeout(timeout_interval);
                break;
            case 'g':
                show_hidden();
                break;
            case 'i':
                if (c == 'i') clear();
                if (inventory()) break;
            case 32:
                if (c == 32) use_weapon(monsters, monster_num, main_char.y, main_char.x);
                break;
            case 'u':
                auto_shoot(monsters, monster_num, main_char.y, main_char.x);
                break;
            case 27: 
                if (menu() == 5)
                {
                    return 2;
                    break;
                }
                break;
            default: break;

        }

        generate_password();
        check_locked_room();
        check_collect(main_char.y, main_char.x);

        check_damage(monsters, monster_num, main_char.y, main_char.x);
        if (gameover()) return 0;
        if (victory()) return 1;
        move_monsters(monsters, monster_num, main_char.y, main_char.x);
        active_sleeping_monsters(monsters, monster_num, main_char.y, main_char.x);

        if (current_level < max_level || level_finished())
        {
            if (main_char.y == up_stairs[current_level - 1].y && main_char.x == up_stairs[current_level - 1].x)
            {
                return next_level();
            }
        }         

        if (main_char.y == down_stairs[current_level - 2].y && main_char.x == down_stairs[current_level - 2].x)
        {
            return previous_level();
        }

        if (c = 'w' || c == 's' || c == 'a' || c == 'd' || c == 'z' || c == 'x' || c == 'q' || c == 'e')
        {
            if (count_down > 0) count_down--;
            if (speed_count_down > 0) speed_count_down--;
            if (power_count_down > 0) power_count_down--;
            if (enchant_count_down > 0) enchant_count_down--;
            if (steps_to_heal < reach_steps_to_heal) steps_to_heal++;
            if (recently_damaged_count_down > 0) recently_damaged_count_down--;
            if (password_count_down > 0) password_count_down--;
            level_steps++;
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

        if (power_count_down <= 0 && current_enchant != 2) 
        {
            power_index = 1;
        }

        if (speed_count_down <= 0 && current_enchant != 1)
        {
            speed_index = 1;
        }

        if (enchant_count_down <= 0) 
        {
            if (current_enchant == 0)
            {
                reach_steps_to_heal = 50;
                current_enchant = -1;
            }
            else if (current_enchant == 1)
            {
                speed_index = 1;
                current_enchant = -1;
            }
            else if (current_enchant == 2)
            {
                power_index = 1;
                current_enchant = -1;
            }
        }
    }
}

int possible(int y, int x) 
{
    char blocked[] = {'|', '_', '-', '=', 'o', 'D', 'F', 'G', 'S', 'U', ' ', 'V', '~'}; 

    int c = mvinch(y, x) & A_CHARTEXT;

    if (c == '=') return check_windows();

    for (int i = 0; i < 13; i++) 
    {
        if (c == blocked[i]) 
        {
            return 0;
        }
    }

    return 1;
}

void show_hidden()
{
    int y = main_char.y, x = main_char.x;
    for (int i = 0; i < hidden_doors_index; i++)
    {
        if (hidden_doors[i].y >= y - 5 && hidden_doors[i].y <= y + 5 && hidden_doors[i].x >= x - 10 && hidden_doors[i].x <= x + 10)
        {
            attron(COLOR_PAIR(32));
            mvprintw(hidden_doors[i].y, hidden_doors[i].x, "?");
            attroff(COLOR_PAIR(32));
        }
    }
    for (int i = 0; i < trap_index; i++)
    {
        if (traps[i].y >= y - 5 && traps[i].y <= y + 5 && traps[i].x >= x - 10 && traps[i].x <= x + 10)
        {
            mvprintw(traps[i].y, traps[i].x, "☠");
        }
    }
    getch();
}

int autorun(int dir)
{
    char blocked[] = {'|', '_', '-', '=', 'o', 'D', 'F', 'G', 'S', 'U', ' ', 'V', '~'}; 
    timeout(200);
    while (1)
    {
        int v = getch();
        if (v == 'w' || v == 'a' || v == 's' || v == 'd' || v == 'q' || v == 'z' || v == 'x' || v == 'e') return 1;
        char ch;
        switch (dir)
        {
            case 'w': ch = mvinch(main_char.y - 1, main_char.x) & A_CHARTEXT; break;
            case 'q': ch = mvinch(main_char.y - 1, main_char.x - 1) & A_CHARTEXT; break;
            case 'a': ch = mvinch(main_char.y, main_char.x - 1) & A_CHARTEXT; break;
            case 'z': ch = mvinch(main_char.y + 1, main_char.x - 1) & A_CHARTEXT; break;
            case 's': ch = mvinch(main_char.y + 1, main_char.x) & A_CHARTEXT; break;
            case 'x': ch = mvinch(main_char.y + 1, main_char.x + 1) & A_CHARTEXT; break;
            case 'd': ch = mvinch(main_char.y, main_char.x + 1) & A_CHARTEXT; break;
            case 'e': ch = mvinch(main_char.y - 1, main_char.x + 1) & A_CHARTEXT; break;
            default: return 1;
        }
        for (int i = 0; i < 13; i++)
        {
            if (ch == blocked[i])
            {
                return 1;
            }
        }
        update_health();
        update_energy();
        update_score();
        display_rooms();
        display_paths();
        display_windows();
        display_pillars();
        spawn_food();
        spawn_weapon();
        spawn_enchant();
        spawn_gold();
        show_traps();
        show_hidden_doors();
        display_monsters();
        select_visible_map();
        show_current_weapon();
        show_current_enchant();
        update_monsters_health(monsters, monster_num);
        check_monsters();
        check_collect(main_char.y, main_char.x);
        if (!check_trap()) return 0;
        if (!check_hidden_doors()) return 0;
        nightmare_rooms();
        update_health();
        update_energy();
        update_score();
        display_rooms();
        display_paths();
        display_windows();
        display_pillars();
        spawn_food();
        spawn_weapon();
        spawn_enchant();
        spawn_gold();
        show_ancient_key();
        show_locked_door();
        show_traps();
        show_hidden_doors();
        display_monsters();
        if ((current_level < max_level) || (level_finished() && (current_level != 4)))
        {
            attron(COLOR_PAIR(32));
            mvprintw(up_stairs[current_level - 1].y, up_stairs[current_level - 1].x,"»");
            attroff(COLOR_PAIR(32));
        }
        if (current_level != 1)
        {
            attron(COLOR_PAIR(2));
            mvprintw(down_stairs[current_level - 2].y, down_stairs[current_level - 2].x, "«");
            attroff(COLOR_PAIR(2));
        }

        refresh();

        switch(PlayerSetting.color)
        {
            case 0: attron(COLOR_PAIR(31)); break;
            case 1: attron(COLOR_PAIR(32)); break;
            case 2: attron(COLOR_PAIR(33)); break;
        }
        mvprintw(main_char.y, main_char.x, "@");
        attroff(COLOR_PAIR(31)); attroff(COLOR_PAIR(32)); attroff(COLOR_PAIR(33));
        refresh();
        switch (dir)
        {
            case 'w': main_char.y--; break;
            case 'q': main_char.y--; main_char.x--; break;
            case 'a': main_char.x--; break;
            case 'z': main_char.y++; main_char.x--; break;
            case 's': main_char.y++; break;
            case 'x': main_char.y++; main_char.x++; break;
            case 'd': main_char.x++; break;
            case 'e': main_char.y--; main_char.x++; break;
            default: return 1;
        }
        check_damage(monsters, monster_num, main_char.y, main_char.x);
        if (gameover()) return 0;
        if (victory()) return 1;
        move_monsters(monsters, monster_num, main_char.y, main_char.x);
        active_sleeping_monsters(monsters, monster_num, main_char.y, main_char.x);
        napms(200);
        flushinp();
    }   
}

void create_rooms()
{
    int nightmare_num = 0;
    for (int i = 0; i < room_num; i++)
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
        if (theme >= 30 && theme < 50 && nightmare_num < 1) 
        {rooms[i].theme = 3; nightmare_num++;}
        else rooms[i].theme = 1;
    }

    if (current_level == 4)
    {
        int p;
        do 
        {
            p = rand() % room_num;
        } while (rooms[p].theme != 1);
        rooms[p].theme = 2;
    }

    return;
}

int get_rand_x() { return 10 + rand() % 155; } 
int get_rand_y() { return 5 + rand() % 20; } 
int get_rand_width() { return 10 + rand() % 10; } 
int get_rand_height() { return 5 + rand() % 6; }

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
        if (!(x + width <= x1 || x >= x2 || y + height <= y1 || y >= y2)) 
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
    
    for (int i = 0; i < room_num; i++)
    {
        for (int j = rooms[i].x + 1; j < rooms[i].x + rooms[i].width; j++)
        {
            if (visible_map[rooms[i].y][j] == 0) attron(COLOR_PAIR(41));
            else if (rooms[i].theme == 3) attron(COLOR_PAIR(1));
            else if (rooms[i].theme == 2) attron(COLOR_PAIR(2));
            mvprintw(rooms[i].y, j, "-");
            if (visible_map[rooms[i].y][j] == 0) attroff(COLOR_PAIR(41));
            else if (rooms[i].theme == 3) attroff(COLOR_PAIR(1));
            else if (rooms[i].theme == 2) attroff(COLOR_PAIR(2));
        }
        for (int j = rooms[i].x; j < rooms[i].x + rooms[i].width; j++)
        {
            if (visible_map[rooms[i].y + rooms[i].height - 1][j] == 0) attron(COLOR_PAIR(41));
            else if (rooms[i].theme == 3) attron(COLOR_PAIR(1));
            else if (rooms[i].theme == 2) attron(COLOR_PAIR(2));
            mvprintw(rooms[i].y + rooms[i].height - 1, j, "_");
            if (visible_map[rooms[i].y + rooms[i].height - 1][j] == 0) attroff(COLOR_PAIR(41));
            else if (rooms[i].theme == 3) attroff(COLOR_PAIR(1));
            else if (rooms[i].theme == 2) attroff(COLOR_PAIR(2));
        }
        for (int j = rooms[i].y; j < rooms[i].y + rooms[i].height; j++)
        {
            if (visible_map[j][rooms[i].x] == 0) attron(COLOR_PAIR(41));
            else if (rooms[i].theme == 3) attron(COLOR_PAIR(1));
            else if (rooms[i].theme == 2) attron(COLOR_PAIR(2));
            mvprintw(j, rooms[i].x, "|");
            if (visible_map[j][rooms[i].x] == 0) attroff(COLOR_PAIR(41));
            else if (rooms[i].theme == 3) attroff(COLOR_PAIR(1));
            else if (rooms[i].theme == 2) attroff(COLOR_PAIR(2));
        }
        for (int j = rooms[i].y; j < rooms[i].y + rooms[i].height; j++)
        {
            if (visible_map[j][rooms[i].x + rooms[i].width] == 0) attron(COLOR_PAIR(41));
            else if (rooms[i].theme == 3) attron(COLOR_PAIR(1));
            else if (rooms[i].theme == 2) attron(COLOR_PAIR(2));
            mvprintw(j, rooms[i].x + rooms[i].width, "|");
            if (visible_map[j][rooms[i].x + rooms[i].width] == 0) attroff(COLOR_PAIR(41));
            else if (rooms[i].theme == 3) attroff(COLOR_PAIR(1));
            else if (rooms[i].theme == 2) attroff(COLOR_PAIR(2));
        }

        refresh();

        for (int j = rooms[i].y + 1; j < rooms[i].y + rooms[i].height - 1; j++) 
        {
            for (int k = rooms[i].x + 1; k < rooms[i].x + rooms[i].width; k++) 
            {
                if (visible_map[j][k] == 0) attron(COLOR_PAIR(41));
                else if (rooms[i].theme == 3) attron(COLOR_PAIR(4));
                else if (rooms[i].theme == 2) attron(COLOR_PAIR(2));
                mvaddch(j, k, '.');
                if (visible_map[j][k] == 0) attroff(COLOR_PAIR(41));
                else if (rooms[i].theme == 3) attroff(COLOR_PAIR(4));
                else if (rooms[i].theme == 2) attroff(COLOR_PAIR(2));
            }
        }
        refresh();
    }
    refresh();
    return;
}

void create_paths()
{
    for (int i = 0; i < room_num - 1; i++)
    {   
        connect_rooms(rooms[i], rooms[i + 1]);
    }
}

pair get_random_point(room Room) 
{
    pair p;
    p.x = Room.x + 1 + (rand() % (Room.width - 2));
    p.y = Room.y + 1 + (rand() % (Room.height - 2));
    return p;
}

void connect_rooms(room room1, room room2) 
{
    display_rooms();
    init_pair(41, COLOR_BLACK, COLOR_BLACK);
    init_pair(42, COLOR_WHITE, COLOR_BLACK);
    int x1, x2, y1, y2;
    int flag;
    int tries = 0;
    do 
    {
        if (tries >= 100000)
        {
            int x1 = room1.x + room1.width / 2;
            int y1 = room1.y + room1.height / 2;
            int x2 = room2.x + room2.width / 2;
            int y2 = room2.y + room2.height / 2;   
            break;    
        } 
        y1 = get_random_point(room1).y;
        x1 = get_random_point(room1).x;
        y2 = get_random_point(room2).y;
        x2 = get_random_point(room2).x;
        flag = 0;
        for (int i = 0; i < room_num; i++)
        {
            if (y1 == rooms[i].y || y1 == rooms[i].y + rooms[i].height - 1 || x1 == rooms[i].x || x1 == rooms[i].x + rooms[i].width ||
                y2 == rooms[i].y || y2 == rooms[i].y + rooms[i].height - 1 || x2 == rooms[i].x || x2 == rooms[i].x + rooms[i].width)
            flag = 1;
        }
        tries++;
    } while (flag);

    int x, y;
    attron(COLOR_PAIR(42));
    for (x = (x1 < x2 ? x1 : x2); x <= (x1 > x2 ? x1 : x2); x++) 
    {
        char ch = mvinch(y1, x) & A_CHARTEXT;
        if (ch != '.' && ch != '|' && ch != '_' && ch != '-' && ch != '+')
        {
            if (visible_map[y1][x] == 0) attron(COLOR_PAIR(41)); 
            corridor[corridor_index].x = x; corridor[corridor_index++].y = y1;
            //mvaddch(y1, x, '#');
            if ( visible_map[y1][x] == 0) attroff(COLOR_PAIR(41));
        }
        else if (ch == '|' || ch == '_' || ch == '-') 
        {
            if (visible_map[y1][x] == 0) attron(COLOR_PAIR(41));
            door[door_index].x = x; door[door_index++].y = y1;
            //mvaddch(y1, x, '+');
            if (visible_map[y1][x] == 0) attroff(COLOR_PAIR(41));
        }
    }
    refresh();

    for (y = (y1 < y2 ? y1 : y2); y <= (y1 > y2 ? y1 : y2); y++) 
    {
        char ch = mvinch(y, x2) & A_CHARTEXT;
        if (ch != '.' && ch != '|' && ch != '_' && ch != '+' && ch != '-') 
        {
            if (visible_map[y][x2] == 0) attron(COLOR_PAIR(41));
            corridor[corridor_index].x = x2; corridor[corridor_index++].y = y;
            //mvaddch(y, x2, '#');
            if (visible_map[y][x2] == 0) attroff(COLOR_PAIR(41));
        }
        else if (ch == '|' || ch == '_' || ch == '-') 
        {
            if (visible_map[y][x2] == 0) attron(COLOR_PAIR(41));
            door[door_index].x = x2; door[door_index++].y = y;
            //mvaddch(y, x2, '+');
            if (visible_map[y][x2] == 0) attroff(COLOR_PAIR(41));
        }
    }
    attroff(COLOR_PAIR(42));
    refresh();
}

void display_paths()
{
    for (int i = 0; i < corridor_index; i++)
    {
        if (visible_map[corridor[i].y][corridor[i].x] == 0) attron(COLOR_PAIR(60)); 
        mvaddch(corridor[i].y, corridor[i].x, '#');
        attroff(COLOR_PAIR(60));
    }
    for (int i = 0; i < door_index; i++)
    {
        if (visible_map[door[i].y][door[i].x] == 0) attron(COLOR_PAIR(60)); 
        mvaddch(door[i].y, door[i].x, '+');
        attroff(COLOR_PAIR(60));
    }
}

void add_windows_pillars()
{
    display_rooms();
    display_paths();
    display_monsters();
    for (int i = 0; i < 34; i++)
    {
        for (int j = 0;j < 190; j++)
        {
            if ((mvinch(i, j) & A_CHARTEXT) == '|' && (mvinch(i, j - 1) & A_CHARTEXT) == '.' && (mvinch(i, j + 1) & A_CHARTEXT) == '.')
            {
                int p = rand() % 3;
                if (p == 0)
                {
                    windows[windows_index].x = j;
                    windows[windows_index++].y = i;
                }
            }
        }
    }

    for (int i = 0; i < room_num; i++)
    {
        int p, q;
        p = rand() % 2;
        if (p)
        {
            q = rand() % 4;
            for (int j = 0; j < q; j++)
            {
                int y, x;
                do 
                {
                    y = rooms[i].y + 1 + (rand() % (rooms[i].height - 2));
                    x = rooms[i].x + 1 + (rand() % (rooms[i].width - 2));
                } while ((mvinch(y, x) & A_CHARTEXT) != '.' || (y == main_char.y && x == main_char.x));

                pillars[pillar_index].x = x; pillars[pillar_index++].y = y;
            }
        }
    }
}

void display_windows()
{
    for (int i = 0; i < windows_index; i++)
    {
        if (visible_map[windows[i].y][windows[i].x] == 1)
        {
            mvaddch(windows[i].y, windows[i].x, '=');
        }
    }
}

void display_pillars()
{
    for (int i = 0; i < pillar_index; i++)
    {
        if (pillars[i].x != 0 && visible_map[pillars[i].y][pillars[i].x] == 1)
        {
            attron(COLOR_PAIR(1));
            mvaddch(pillars[i].y, pillars[i].x, 'o');
            attroff(COLOR_PAIR(1));
        }
    }
}

int check_windows()
{
    int save_visible_map[34][190];
    for (int i = 0; i < 34; i++)
    {
        for (int j = 0; j < 190; j++)
        {
            save_visible_map[i][j] = visible_map[i][j];
        }
    }
    int y = main_char.y, x = main_char.x;
    int p;
    for (int i = 0; i < windows_index; i++)
    {
        if (y == windows[i].y && x == windows[i].x - 1)
        {
            pair point; point.y = y; point.x = x + 3;
            for (int j = 0; j < room_num; j++)
            {
                if (point.y > rooms[j].y && point.y < rooms[j].y + rooms[j].height && point.x > rooms[j].x && point.x < rooms[j].x + rooms[j].width) p = j;
            }
        }
        if (y == windows[i].y && x == windows[i].x + 1)
        {
            pair point; point.y = y; point.x = x - 3;
            for (int j = 0; j < room_num; j++)
            {
                if (point.y > rooms[j].y && point.y < rooms[j].y + rooms[j].height && point.x > rooms[j].x && point.x < rooms[j].x + rooms[j].width) p = j;
            }
        }
    }

    for (int i = rooms[p].y; i < rooms[p].y + rooms[p].height; i++)
    {
        for (int j = rooms[p].x; j <= rooms[p].x + rooms[p].width; j++)
            {
                visible_map[i][j] = 1;
            }
    }

    clear();
    update_health();
    update_energy();
    update_score();
    display_rooms();
    display_paths();
    display_windows();
    display_pillars();
    spawn_food();
    spawn_weapon();
    spawn_enchant();
    spawn_gold();
    show_traps();
    show_hidden_doors();
    display_monsters();
    show_current_weapon();
    show_current_enchant();
    update_monsters_health(monsters, monster_num);
    if ((current_level < max_level) || (level_finished() && (current_level != 4)))
    {
        attron(COLOR_PAIR(32));
        mvprintw(up_stairs[current_level - 1].y, up_stairs[current_level - 1].x, ">");
        attroff(COLOR_PAIR(32));
    }
    if (current_level != 1)
    {
        attron(COLOR_PAIR(2));
        if (visible_map[down_stairs[current_level - 2].y][down_stairs[current_level - 2].x] == 1) mvprintw(down_stairs[current_level - 2].y, down_stairs[current_level - 2].x, "<");
        attroff(COLOR_PAIR(2));
    }
    switch(PlayerSetting.color)
    {
        case 0: attron(COLOR_PAIR(31)); break;
        case 1: attron(COLOR_PAIR(32)); break;
        case 2: attron(COLOR_PAIR(33)); break;
    }
    mvprintw(main_char.y, main_char.x, "@");
    attroff(COLOR_PAIR(31)); attroff(COLOR_PAIR(32)); attroff(COLOR_PAIR(33));
    refresh();


    getch();

    for (int i = 0; i < 34; i++)
    {
        for (int j = 0; j < 190; j++)
        {
            visible_map[i][j] = save_visible_map[i][j];
        }
    }

    return 0;
}

void display_text(const char *text) 
{
    clear_text();
    int len = strlen(text);
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(0));
    mvprintw(2, 190 - len - 5, "%s", text);
    attroff(COLOR_PAIR(0));
    refresh();
}

void display_password()
{
    int len = password_len;
    if (password_count_down < 10) attron(COLOR_PAIR(32));
    mvprintw(2, 190 - len - 14, "PASSWORD: %s", last_password);
    attroff(COLOR_PAIR(32));
    refresh();  
}

void clear_text()
{
    mvprintw(2, 130, "                                                         ");
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

void update_score()
{
    init_pair(81, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(81));
    mvprintw(3, 3, "score: %d", score);
    attroff(COLOR_PAIR(81));
}

void show_current_enchant()
{
    switch (current_enchant)
    {
        case 0: mvprintw(36, 175, "ENCHANT: 🧪"); break;
        case 1: mvprintw(36, 175, "ENCHANT: 🗲"); break;
        case 2: mvprintw(36, 175, "ENCHANT: 🩸"); break;
        case -1: mvprintw(36, 175, "ENCHANT: _"); break;
    }
}

void check_collect(int y, int x)
{
    if (in_fight_room)
    {
        for (int i = 0; i < throwed_weapon_fight_room_index; i++)
        {
            if (y == throwed_weapons_fight_room[i].y && (x == throwed_weapons_fight_room[i].x || x == throwed_weapons_fight_room[i].x + 1))
            {
                display_text("PRESS C TO COLLECT THE WEAPON");
                int c = getch();
                if (c == 'c')
                {
                    int type_index = throwed_weapons_fight_room[i].type;
                    if (type_index == 1) inventory_weapon[type_index] += 1;
                    else if (type_index == 2) inventory_weapon[type_index] += 1;
                    else if (type_index == 3) inventory_weapon[type_index] += 1;
                    throwed_weapons_fight_room[i].y = 0; throwed_weapons_fight_room[i].x = 0;
                    clear_text();
                    display_text("COLLECTED!");
                    refresh();
                    napms(750);
                    flushinp();
                }  
            }
        }    
    }

    else if (in_enchant_room)
    {
        for (int i = 0; i < enchant_room_enchants_index; i++)
        {
            if (y == enchant_room_enchants[i].y && (x == enchant_room_enchants[i].x || x == enchant_room_enchants[i].x + 1))
            {
                display_text("PRESS C TO COLLECT THE ENCHANT");
                int c = getch();
                if (c == 'c')
                {
                    int type_index = enchant_room_enchants[i].type;
                    if (type_index == 1) inventory_enchant[type_index - 1] += 1;
                    else if (type_index == 2) inventory_enchant[type_index - 1] += 1;
                    else if (type_index == 3) inventory_enchant[type_index - 1] += 1;
                    enchant_room_enchants[i].y = 0; enchant_room_enchants[i].x = 0;
                    clear_text();
                    display_text("COLLECTED!");
                    refresh();
                    napms(750);
                    flushinp();
                }   
            }
        }
    }

    else 
    {
        clear();
        update_health();
        update_energy();
        update_score();
        mvprintw(36, 1, "LEVEL: %d", current_level);
        if (password_count_down > 0) display_password();
        display_rooms();
        display_paths();
        display_windows();
        display_pillars();
        spawn_food();
        spawn_weapon();
        spawn_enchant();
        spawn_gold();
        show_ancient_key();
        show_locked_door();
        show_traps();
        show_hidden_doors();
        display_monsters();
        show_current_weapon();
        show_current_enchant();
        update_monsters_health(monsters, monster_num);

        if ((current_level < max_level) || (level_finished() && (current_level != 4)))
        {
            attron(COLOR_PAIR(32));
            mvprintw(up_stairs[current_level - 1].y, up_stairs[current_level - 1].x, "»");
            attroff(COLOR_PAIR(32));
        }
        if (current_level != 1)
        {
            attron(COLOR_PAIR(2));
            mvprintw(down_stairs[current_level - 2].y, down_stairs[current_level - 2].x, "«");
            attroff(COLOR_PAIR(2));
        }

        switch(PlayerSetting.color)
        {
            case 0: attron(COLOR_PAIR(31)); break;
            case 1: attron(COLOR_PAIR(32)); break;
            case 2: attron(COLOR_PAIR(33)); break;
        }
        mvprintw(main_char.y, main_char.x, "@");
        attroff(COLOR_PAIR(31)); attroff(COLOR_PAIR(32)); attroff(COLOR_PAIR(33));
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
                    display_text("COLLECTED!");
                    refresh();
                    napms(750);
                    flushinp();
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
                    if (type_index == 1) 
                    {
                        inventory_weapon[type_index] += 10;
                        weapons[i].y = 0; weapons[i].x = 0;
                        clear_text();
                        display_text("COLLECTED!");
                        refresh();
                        napms(750);
                        flushinp();
                    }
                    else if (type_index == 2) 
                    {
                        inventory_weapon[type_index] += 8;
                        weapons[i].y = 0; weapons[i].x = 0;
                        clear_text();
                        display_text("COLLECTED!");
                        refresh();
                        napms(750);
                        flushinp();
                        
                    }
                    else if (type_index == 3) 
                    {
                        inventory_weapon[type_index] += 20;
                        weapons[i].y = 0; weapons[i].x = 0;
                        clear_text();
                        display_text("COLLECTED!");
                        refresh();
                        napms(750);
                        flushinp();
                    }
                    else if (type_index == 4)
                    {
                        if (inventory_weapon[4] == 0) 
                        {
                            inventory_weapon[type_index] += 1;
                            weapons[i].y = 0; weapons[i].x = 0;
                            clear_text();
                            display_text("COLLECTED!");
                            refresh();
                            napms(750);
                            flushinp();
                        }
                        else 
                        {
                            clear_text();
                            refresh();
                        }
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
                    display_text("COLLECTED!");
                    refresh();
                    napms(750);
                    flushinp();
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
                    display_text("COLLECTED!");
                    refresh();
                    napms(750);
                    flushinp();
                    refresh();
                }  
            }
        }

        for (int i = 0; i < gold_index; i++)
        {
           if (main_char.y == gold[i].y && (main_char.x == gold[i].x || main_char.x == gold[i].x + 1))
           {
                score += 10;
                gold[i].x = 0; gold[i].y = 0;
           } 
        }

        for (int i = 0; i < ancient_keys_index; i++)
        {
            if (main_char.y == ancient_keys[i].y && (main_char.x == ancient_keys[i].x || main_char.x == ancient_keys[i].x + 1))
            {
                display_text("PRESS C TO COLLECT THE KEY");
                int c = getch();
                if (c == 'c')
                {
                    inventory_keys[0]++;
                    ancient_keys[i].x = 0; ancient_keys[i].y = 0;
                    clear_text();
                    display_text("COLLECTED!");
                    refresh();
                    napms(750);
                    flushinp();
                    refresh();
                }  
            }   
        }
    }
}

void select_visible_map()
{
    for (int r = 0; r < room_num; r++) 
    {
        if (main_char.y >= rooms[r].y && main_char.y <= rooms[r].y + rooms[r].height - 1 &&
            main_char.x >= rooms[r].x && main_char.x <= rooms[r].x + rooms[r].width)
        {
                rooms[r].visible = 1;
                if (rooms[r].theme != 3)
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

int check_trap()
{
    if (trap_index == 0) return 1;
    int y = main_char.y, x = main_char.x;
    for (int i = 0; i < trap_index; i++)
    {
        if ((y == traps[i].y || y == traps[i].y + 1 || y == traps[i].y - 1) && (x == traps[i].x - 1 || x == traps[i].x + 1 || x == traps[i].x) && traps[i].display == 0)
        {
            traps[i].display = 1;
            in_fight_room = 1;
            if (!fight_room()) return 0;
            else return 1;
        }
    }
}

int check_hidden_doors()
{
    if (hidden_doors_index == 0) return 1;
    int y = main_char.y, x = main_char.x;
    for (int i = 0; i < hidden_doors_index; i++)
    {
        if (y == hidden_doors[i].y && x == hidden_doors[i].x)
        {
            hidden_doors[i].display = 1;
            in_enchant_room = 1;
            if (!enchant_room()) return 0;
            else return 1;
        }
    }   
}

void generate_password()
{
    update_health();
    update_energy();
    update_score();
    if (password_count_down > 0) display_password();
    display_rooms();
    display_paths();
    display_windows();
    display_pillars();
    spawn_food();
    spawn_weapon();
    spawn_enchant();
    spawn_gold();
    show_ancient_key();
    show_locked_door();
    show_traps();
    show_hidden_doors();
    display_monsters();
    show_current_weapon();
    show_current_enchant();
    update_monsters_health(monsters, monster_num);

    if ((current_level < max_level) || (level_finished() && (current_level != 4)))
    {
        attron(COLOR_PAIR(32));
        mvprintw(up_stairs[current_level - 1].y, up_stairs[current_level - 1].x, "»");
        attroff(COLOR_PAIR(32));
    }
    if (current_level != 1)
    {
        attron(COLOR_PAIR(2));
        mvprintw(down_stairs[current_level - 2].y, down_stairs[current_level - 2].x, "«");
        attroff(COLOR_PAIR(2));
    }
        
    switch(PlayerSetting.color)
    {
        case 0: attron(COLOR_PAIR(31)); break;
        case 1: attron(COLOR_PAIR(32)); break;
        case 2: attron(COLOR_PAIR(33)); break;
    }
    mvprintw(main_char.y, main_char.x, "@");
    attroff(COLOR_PAIR(31)); attroff(COLOR_PAIR(32)); attroff(COLOR_PAIR(33));

    if ((current_level == 3 || current_level == 4) && (is_locked == 1) && (tries < 3))
    {
        int y = main_char.y, x = main_char.x;
        switch(PlayerSetting.color)
        {
        case 0: attron(COLOR_PAIR(31)); break;
        case 1: attron(COLOR_PAIR(32)); break;
        case 2: attron(COLOR_PAIR(33)); break;
        }
        mvprintw(main_char.y, main_char.x, "@");
        attroff(COLOR_PAIR(31)); attroff(COLOR_PAIR(32)); attroff(COLOR_PAIR(33));
        refresh();
        if (current_level == 3)
        {
            if ((y == password_generator.y || y == password_generator.y + 1) && (x == password_generator.x || x == password_generator.x + 1))
            {
                display_text("PRESS SPACE TO GENERATE A PASSWORD");
                int c = getch();
                if (c == 32)
                {
                    for (int i = 0; i < password_len; i++)
                    {
                        int p = rand() % 3;
                        char tmp;
                        if (p == 0) tmp = 'a' + rand() % 26;
                        else if (p == 1) tmp = '1' + rand() % 10;
                        else tmp = 'A' + rand() % 26;
                        last_password[i] = tmp;
                    }
                    last_password[password_len] = '\0';
                    password_count_down = 30;
                }
                else return;
            }
        }
        else if (current_level == 4)
        {
            if (((y == password_generator1.y || y == password_generator1.y + 1) && (x == password_generator1.x || x == password_generator1.x + 1)) ||
                ((y == password_generator2.y || y == password_generator2.y + 1) && (x == password_generator2.x || x == password_generator2.x + 1)))
            {
                display_text("PRESS SPACE TO GENERATE A PASSWORD");
                int c = getch();
                if (c == 32)
                {
                    for (int i = 0; i < password_len; i++)
                    {
                        int p = rand() % 3;
                        char tmp;
                        if (p == 0) tmp = 'a' + rand() % 26;
                        else if (p == 1) tmp = '1' + rand() % 10;
                        else tmp = 'A' + rand() % 26;
                        last_password[i] = tmp;
                    }
                    last_password[password_len] = '\0';
                    password_count_down = 30;
                }
                else return;
            }   
        }
    }
    
}

void check_locked_room()
{
    update_health();
    update_energy();
    update_score();
    if (password_count_down > 0) display_password();
    display_rooms();
    display_paths();
    display_windows();
    display_pillars();
    spawn_food();
    spawn_weapon();
    spawn_enchant();
    spawn_gold();
    show_ancient_key();
    show_locked_door();
    show_traps();
    show_hidden_doors();
    display_monsters();
    show_current_weapon();
    show_current_enchant();
    update_monsters_health(monsters, monster_num);

    if ((current_level < max_level) || (level_finished() && (current_level != 4)))
    {
        attron(COLOR_PAIR(32));
        mvprintw(up_stairs[current_level - 1].y, up_stairs[current_level - 1].x, "»");
        attroff(COLOR_PAIR(32));
    }
    if (current_level != 1)
    {
        attron(COLOR_PAIR(2));
        mvprintw(down_stairs[current_level - 2].y, down_stairs[current_level - 2].x, "«");
        attroff(COLOR_PAIR(2));
    }
        
    switch(PlayerSetting.color)
    {
        case 0: attron(COLOR_PAIR(31)); break;
        case 1: attron(COLOR_PAIR(32)); break;
        case 2: attron(COLOR_PAIR(33)); break;
    }
    mvprintw(main_char.y, main_char.x, "@");
    attroff(COLOR_PAIR(31)); attroff(COLOR_PAIR(32)); attroff(COLOR_PAIR(33));

    if (current_level == 3 || current_level == 4)
    {
        if (tries < 3 && is_locked == 1)
        {
            char input[100];
            int input_index = 0;
            int y = main_char.y, x = main_char.x;
            switch(PlayerSetting.color)
            {
            case 0: attron(COLOR_PAIR(31)); break;
            case 1: attron(COLOR_PAIR(32)); break;
            case 2: attron(COLOR_PAIR(33)); break;
            }
            mvprintw(main_char.y, main_char.x, "@");
            attroff(COLOR_PAIR(31)); attroff(COLOR_PAIR(32)); attroff(COLOR_PAIR(33));
            refresh();
            if ((y == locked_door.y || y == locked_door.y + 1 || y == locked_door.y - 1) && (x == locked_door.x - 1 || x == locked_door.x + 1))
            {
                timeout(-1);
                display_text("PRESS SPACE TO ENTER THE PASSWORD");
                int c = getch();
                if (c == 32)
                {
                    clear_text();
                    move(2, 190 - password_len - 5);
                    curs_set(1);
                    while (1) 
                    {
                        int ch = getch();  
                        if (ch == '\n') 
                        {  
                            noecho();
                            curs_set(0);
                            input[input_index] = '\0'; 
                            check_pass(input); 
                            timeout(timeout_interval); 
                            break;
                        } 
                        else if (ch == 27) 
                        { 
                            noecho();
                            curs_set(0);
                            refresh();
                            timeout(timeout_interval);  
                            break;
                        } 
                        else if (ch == KEY_BACKSPACE || ch == 127) 
                        { 
                            if (input_index > 0) 
                            {
                                input_index--;
                                input[input_index] = '\0';
                                move(2, 190 - password_len - 5 + input_index);  
                                addch(' ');  
                                move(2, 190 - password_len - 5 + input_index);  
                            }
                        } 
                        else if (input_index < password_len) {  
                            input[input_index] = ch;
                            input_index++;
                            addch(ch); 
                        }
                    }
                }
            }
        }
    }
}

void check_pass(char *input_password)
{
    if (reverse_password < 30)
    {
        int flag = 1;
        for (int i = 0; i < password_len; i++)
        {
            if (input_password[i] != last_password[password_len - 1 - i]) flag = 0;
        }
        if (flag) 
        {
            if (current_level == 3)
            {
                doombringer++;
                if (doombringer >= 2) add_doombringer();
                is_locked = 0;
                display_text("YOU HAVE COLLECTED THE FIRST PART OF 'DOOMBRINGET'");
                refresh();
                napms(1000);
                flushinp();
                clear_text();
            }
            else if (current_level == 4)
            {
                if (commited_pass == 0)
                {
                    commited_pass++;
                    display_text("YOU NEED ONE MORE PASSWORD");
                    refresh();
                    napms(1000);
                    flushinp();
                    clear_text();
                    return;
                }
                else if (commited_pass == 1)
                {
                    is_locked = 0;
                    display_text("YOU HAVE COLLECTED THE SECOND PART OF 'DOOMBRINGET'");
                    refresh();
                    napms(1000);
                    flushinp();
                    clear_text();
                    doombringer++;
                    if (doombringer >= 2) add_doombringer();
                    password_count_down = 0;
                    return;
                }
            }  
        }
        else 
        {
            display_text("WRONG PASSWORD");
            refresh();
            napms(800);
            flushinp();
            clear_text();
            tries++;
            return;
        }
    }
    else 
    {
        if (strcmp(input_password, last_password) == 0) 
        {
            if (current_level == 3)
            {
                doombringer++;
                if (doombringer >= 2) add_doombringer();
                is_locked = 0;
                display_text("YOU HAVE COLLECTED THE FIRST PART OF 'DOOMBRINGET'");
                refresh();
                napms(1000);
                flushinp();
                clear_text();
                return;
            }
            else if (current_level == 4)
            {
                if (commited_pass == 0)
                {
                    commited_pass++;
                    display_text("YOU NEED ONE MORE PASSWORD");
                    refresh();
                    napms(1000);
                    flushinp();
                    clear_text();
                }
                else if (commited_pass == 1)
                {
                    is_locked = 0;
                    display_text("YOU HAVE COLLECTED THE SECOND PART OF 'DOOMBRINGET'");
                    refresh();
                    napms(1000);
                    flushinp();
                    clear_text();
                    doombringer++;
                    if (doombringer >= 2) add_doombringer();
                    password_count_down = 0;
                    return;
                }
            } 
        }
        else
        {
            display_text("WRONG PASSWORD");
            refresh();
            napms(800);
            flushinp();
            clear_text();
            tries++;
            return;
        } 
    }
}

//-------------------------------------CREATE_THINGS------------------------------------------------//

void create_enchant()
{

    for (int i = 0; i < room_num; i++)
    {
        int p, q = 1;
        if (rooms[i].theme == 2)
        {
            p = 0; q = 0;
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
    for (int i = 0; i < room_num; i++)
    {
        int p = rand() % 15;
        if (rooms[i].theme == 2) p = -1;
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
    for (int i = 0; i < room_num; i++)
    {
        int p = rand() % 7;
        if (rooms[i].theme == 2) p = -1;
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

void create_traps()
{
    if (current_level != 4)
    {
        for (int i = 0; i < room_num; i++)
        {
            if (rooms[i].theme != 3)
            {
                int p = rand() % 10;
                if (p == 0)
                {
                    int y = rooms[i].y + 1 + (rand() % (rooms[i].height - 3));
                    int x = rooms[i].x + 1 + (rand() % (rooms[i].width - 3));
                    traps[trap_index].y = y; traps[trap_index++].x = x;
                }
            }
        }
    }
    else 
    {
        for (int i = 0; i < room_num; i++)
        {
            if (rooms[i].theme == 2)
            {
                int p = rand() % 4 + 3; 
                for (int j = 0; j < p; j++)
                {
                    int y = rooms[i].y + 1 + (rand() % (rooms[i].height - 3));
                    int x = rooms[i].x + 1 + (rand() % (rooms[i].width - 3));
                    traps[trap_index].y = y; traps[trap_index++].x = x;              
                }
            }
        }
    }   
}

void create_hidden_doors()
{
    for (int i = 0; i < room_num; i++)
    {
        if (rooms[i].theme == 1)
        {
            int p = rand() % 10; 
            if (p == 0 || p == 1)
            {
                int y = rooms[i].y + 1 + (rand() % (rooms[i].height - 3));
                int x = rooms[i].x + 1 + (rand() % (rooms[i].width - 3));
                hidden_doors[hidden_doors_index].y = y; hidden_doors[hidden_doors_index].x = x; hidden_doors[hidden_doors_index++].display = 0;   
            }        
        }
    }
}

void set_gold()
{
    for (int i = 0; i < room_num; i++)
    {
        if (rooms[i].theme == 2)
        {
            int p = rand() % 5 + 5;
            for (int j = 0; j < p; j++)
            {
                int y = rooms[i].y + 1 + (rand() % (rooms[i].height - 3));
                int x = rooms[i].x + 1 + (rand() % (rooms[i].width - 3));
                gold[gold_index].y = y; gold[gold_index++].x = x;
            }
        }
        else 
        {
            int p = rand() % 10;
            if (p <= 5)
            {
                int y = rooms[i].y + 1 + (rand() % (rooms[i].height - 3));
                int x = rooms[i].x + 1 + (rand() % (rooms[i].width - 3));
                gold[gold_index].y = y; gold[gold_index++].x = x;
            }
        }
    } 
}

void set_stairs()
{
    if (current_level != 4)
    {
        int y, x;
        int p;
        do
        {
            p = rand() % room_num;
        } while (rooms[p].theme != 1);

        y = rooms[p].y + 1;
        x = rooms[p].x + rooms[p].width - 1;


        up_stairs[current_level - 1].y = y; up_stairs[current_level - 1].x = x;
    }
}

void add_ancient_key()
{
    for (int i = 0; i < room_num; i++)
    {
        if (rooms[i].theme == 1)
        {
            int p = rand() % 15;
            if (p == 0)
            {
                int y = rooms[i].y + 1 + (rand() % (rooms[i].height - 2));
                int x = rooms[i].x + 1 + (rand() % (rooms[i].width - 2));
                ancient_keys[ancient_keys_index].x = x; 
                ancient_keys[ancient_keys_index++].y = y;
            }
        }
    }
}

void add_locked_door()
{
    display_rooms();
    display_paths();
    if (current_level == 3)
    {
        int p;
        do
        {
            p = rand() % room_num;
        } while (rooms[p].theme != 1);

        int q = rand() % 2;
        for (int i = rooms[p].y + 1; i < rooms[p].y + rooms[p].height; i++)
        {
            if (q)
            {
                if ((mvinch(i, rooms[p].x - 1) & A_CHARTEXT) == ' ')
                {
                    locked_door.y = i; locked_door.x = rooms[p].x;
                    break;
                }
            }
            else 
            {
                if ((mvinch(i, rooms[p].x + rooms[p].width + 1) & A_CHARTEXT) == ' ')
                {
                    locked_door.y = i; locked_door.x = rooms[p].x + rooms[p].width;
                    break;
                }
            }
        }

        int r;
        do
        {
            r = rand() % room_num;
        } while (r == p || rooms[r].theme != 1);

        if (q)
        {
            password_generator.y = rooms[r].y + rooms[r].height - 2;
            password_generator.x = rooms[r].x + rooms[r].width - 1;
        }
        else 
        {
            password_generator.y = rooms[r].y + rooms[r].height - 2;
            password_generator.x = rooms[r].x + 1;
        }
    }

    if (current_level == 4)
    {
        int p;
        do
        {
            p = rand() % room_num;
        } while (rooms[p].theme != 1);

        int q = rand() % 2;
        for (int i = rooms[p].y + 1; i < rooms[p].y + rooms[p].height; i++)
        {
            if (q)
            {
                if ((mvinch(i, rooms[p].x - 1) & A_CHARTEXT) == ' ')
                {
                    locked_door.y = i; locked_door.x = rooms[p].x;
                    break;
                }
            }
            else 
            {
                if ((mvinch(i, rooms[p].x + rooms[p].width + 1) & A_CHARTEXT) == ' ')
                {
                    locked_door.y = i; locked_door.x = rooms[p].x + rooms[p].width;
                    break;
                }
            }
        }

        int r;
        do
        {
            r = rand() % room_num;
        } while (r == p || rooms[r].theme != 1);

        if (q)
        {
            password_generator1.y = rooms[r].y + rooms[r].height - 2;
            password_generator1.x = rooms[r].x + rooms[r].width - 1;
        }
        else 
        {
            password_generator1.y = rooms[r].y + rooms[r].height - 2;
            password_generator1.x = rooms[r].x + 1;
        }
        int g;
        do
        {
            g = rand() % room_num;
        } while (g == p || g == r || rooms[g].theme != 1);

        if (q)
        {
            password_generator2.y = rooms[g].y + rooms[g].height - 2;
            password_generator2.x = rooms[g].x + rooms[g].width - 1;
        }
        else 
        {
            password_generator2.y = rooms[g].y + rooms[g].height - 2;
            password_generator2.x = rooms[g].x + 1;
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

    if (in_fight_room)
    {
        for (int i = 0; i < throwed_weapon_fight_room_index; i++)
        {
            if (throwed_weapons_fight_room[i].x != 0)
            {
                if (throwed_weapons_fight_room[i].type == 1) mvprintw(throwed_weapons_fight_room[i].y, throwed_weapons_fight_room[i].x, "🗡");
                else if (throwed_weapons_fight_room[i].type == 2) mvprintw(throwed_weapons_fight_room[i].y, throwed_weapons_fight_room[i].x, "🪄");
                else if (throwed_weapons_fight_room[i].type == 3) mvprintw(throwed_weapons_fight_room[i].y, throwed_weapons_fight_room[i].x, "⬻");
            }   
        }  
    }
    
    else 
    {
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
}

void show_traps()
{
    for (int i = 0; i < trap_index; i++)
    {
        if (traps[i].x != 0 && traps[i].display == 1 && visible_map[traps[i].y][traps[i].x] == 1) mvprintw(traps[i].y, traps[i].x, "☠");
    }
}

void show_hidden_doors()
{
    for (int i = 0; i < hidden_doors_index; i++)
    {
        attron(COLOR_PAIR(32));
        if (hidden_doors[i].display == 1 && visible_map[hidden_doors[i].y][hidden_doors[i].x] == 1) mvprintw(hidden_doors[i].y, hidden_doors[i].x, "?");
        attroff(COLOR_PAIR(32));
    }
}

void spawn_gold()
{
    for (int i = 0; i < gold_index; i++)
    {
        if (gold[i].x != 0 && visible_map[gold[i].y][gold[i].x] == 1) mvprintw(gold[i].y, gold[i].x, "🪙");
    }
}   

void show_ancient_key()
{
    for (int i = 0; i < ancient_keys_index; i++)
    {
        if (ancient_keys[i].x != 0 && visible_map[ancient_keys[i].y][ancient_keys[i].x] == 1)
        {
            attron(COLOR_PAIR(2));
            mvprintw(ancient_keys[i].y, ancient_keys[i].x, "Δ");
            attroff(COLOR_PAIR(2));
        }
    }
}

void show_locked_door()
{
    if (current_level == 3)
    {
        if (visible_map[locked_door.y][locked_door.x] == 1)
        {
            if (is_locked) attron(COLOR_PAIR(32));
            else attron(COLOR_PAIR(4));
            mvprintw(locked_door.y, locked_door.x, "~");
            attroff(COLOR_PAIR(32)); attroff(COLOR_PAIR(4));
        }
        if (visible_map[password_generator.y][password_generator.x] == 1)
        {
            attron(COLOR_PAIR(2));
            mvprintw(password_generator.y, password_generator.x, "&");
            attroff(COLOR_PAIR(2));
        }
    }
    if (current_level == 4)
    {
        if (visible_map[locked_door.y][locked_door.x] == 1)
        {
            if (is_locked) attron(COLOR_PAIR(32));
            else attron(COLOR_PAIR(4));
            mvprintw(locked_door.y, locked_door.x, "~");
            attroff(COLOR_PAIR(32)); attroff(COLOR_PAIR(4));
        }
        if (visible_map[password_generator1.y][password_generator1.x] == 1)
        {
            attron(COLOR_PAIR(2));
            mvprintw(password_generator1.y, password_generator1.x, "&");
            attroff(COLOR_PAIR(2));
        }
        if (visible_map[password_generator2.y][password_generator2.x] == 1)
        {
            attron(COLOR_PAIR(2));
            mvprintw(password_generator2.y, password_generator2.x, "&");
            attroff(COLOR_PAIR(2));
        }
    }
}
//-------------------------------------SPAWN_THINGS------------------------------------------------//


//-------------------------------------INVENTORY------------------------------------------------//

int inventory() 
{
    clear();
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
        case '4':
            wclear(inv_win);
            wrefresh(inv_win);
            return show_keys();
            break;
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
            mvwprintw(food_win, y++, 2, "%d \t%s", fts[i].count, (fts[i].type == 1) ? "NORMAL FOOD" : (fts[i].type == 2 ? "SUPER FOOD" : (fts[i].type == 3 ? "MAGICAL FOOD" : "ROTTEN FOOD")));
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
                timeout(timeout_interval);
                refresh();
                napms(600);
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
                napms(600);
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
                napms(600);
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
                napms(600);
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

    to_show wts[6];
    for (int i = 0; i < 6; i++) wts[i].count = 0;

    init_pair(20, COLOR_RED, COLOR_BLACK);

    int current = 0;

    while (1)
    {
        wclear(weapon_win);
        box(weapon_win, 0, 0);
        mvwprintw(weapon_win, 0, (width - 8) / 2, " WEAPON ");
        wrefresh(weapon_win);

        int index = 0;
        for (int i = 0; i < 6; i++)
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
            else if (wts[i].type == 6) strcpy(weapon_type, "DOOMBRINGER");
            if (current == i) wattron(weapon_win, COLOR_PAIR(20));
            mvwprintw(weapon_win, y++, 2, "%d \t%s", wts[i].count, weapon_type);
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
                current_weapon = 0;
                display_text("YOUR WEAPON IS NOW MACE");
                refresh();
                napms(600);
                flushinp();
                clear_text();
                wclear(weapon_win);
                wrefresh(weapon_win);
                refresh();
                return 1;
            }
            else if (type_index == 1) 
            {
                if (current_weapon == -1) current_weapon = 1;
                if (current_weapon == 1 || current_weapon == 2 || current_weapon == 3) current_weapon = 1;
                if (last_weapon == 1) current_weapon = 1;
                last_weapon = 1;
                display_text("YOUR WEAPON IS NOW DAGGER");
                refresh();
                napms(600);
                flushinp();
                clear_text();
                wclear(weapon_win);
                wrefresh(weapon_win);
                refresh();
                return 1;  
            }
            else if (type_index == 2)
            {
                if (current_weapon == -1) current_weapon = 2;
                if (current_weapon == 1 || current_weapon == 2 || current_weapon == 3) current_weapon = 2;
                if (last_weapon == 2) current_weapon = 2;
                last_weapon = 2;
                display_text("YOUR WEAPON IS NOW MAGIC WAND");
                refresh();
                napms(600);
                flushinp();
                clear_text();
                wclear(weapon_win);
                wrefresh(weapon_win);
                refresh();
                return 1;
            }
            else if (type_index == 3)
            {
                if (current_weapon == -1) current_weapon = 3;
                if (current_weapon == 1 || current_weapon == 2 || current_weapon == 3) current_weapon = 3;
                if (last_weapon == 3) current_weapon = 3;
                last_weapon = 3;
                display_text("YOUR WEAPON IS NOW ARROW");
                refresh();
                napms(600);
                flushinp();
                clear_text();
                wclear(weapon_win);
                wrefresh(weapon_win);
                refresh();
                return 1;
            }
            else if (type_index == 4)
            {
                current_weapon = 4;
                display_text("YOUR WEAPON IS NOW SWORD");
                refresh();
                napms(1500);
                flushinp();
                clear_text();
                wclear(weapon_win);
                wrefresh(weapon_win);
                refresh();
                return 1;
            }
            else if (type_index == 5)
            {
                current_weapon = 5;
                display_text("YOUR WEAPON IS NOW DOOMBRINGER");
                refresh();
                napms(1500);
                flushinp();
                clear_text();
                wclear(weapon_win);
                wrefresh(weapon_win);
                refresh();
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
            mvwprintw(enchant_win, y++, 2, "%d \t%s", ets[i].count, enchant_type);
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
                    timeout(timeout_interval);
                    refresh();
                    napms(600);
                    flushinp();
                    clear_text();
                    wclear(enchant_win);
                    wrefresh(enchant_win);
                    reach_steps_to_heal = 25;
                    enchant_count_down = 100;
                    energy = 10;
                    current_enchant = 0;
                    return 1;
                }
                else if (type == 2)
                {
                    display_text("YOU ARE USING SPEED ENCHANT");
                    refresh();
                    napms(600);
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
                    napms(600);
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
                napms(800);
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

int show_keys()
{
    int startx, starty, width, height;
    WINDOW *key_win;
    
    height = LINES - 2;
    width = COLS - 4;   
    starty = 1;           
    startx = 2;           

    key_win = newwin(height, width, starty, startx);

    box(key_win, 0, 0);

    mvwprintw(key_win, 0, (width - 8) / 2, " KEY ");
    wrefresh(key_win);

    to_show kts[2];
    for (int i = 0; i < 5; i++) kts[i].count = 0;

    init_pair(20, COLOR_RED, COLOR_BLACK);

    int current = 0;

    while (1)
    {
        wclear(key_win);
        box(key_win, 0, 0);
        mvwprintw(key_win, 0, (width - 8) / 2, " KEY ");
        wrefresh(key_win);
    
        if (inventory_keys[0] + inventory_keys[1] == 0)
        {
            mvwprintw(key_win, 2, 4, "YOU DON'T HAVE ANY KEY!");
            wrefresh(key_win);
            int c = getch();
            wclear(key_win);
            return inventory();
        }

        int index = 0;
        for (int i = 0; i < 2; i++)
        {
            if (inventory_keys[i] != 0)
            {
                kts[index].count = inventory_keys[i];
                kts[index++].type = i + 1;
            }
        }

        int y = 1;
        char key_type[20];
        for (int i = 0; i < index; i++)
        {

            if (kts[i].type == 1) strcpy(key_type, "ANCIENT KEY");
            else if (kts[i].type == 2) strcpy(key_type, "BROKEN ANCIENT KEY");
            if (current == i) wattron(key_win, COLOR_PAIR(20));
            mvwprintw(key_win, y++, 2, "%d \t%s", kts[i].count, key_type);
            if (current == i) wattroff(key_win, COLOR_PAIR(20));
        }
        wrefresh(key_win);
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
            int type = kts[used_index].type;
            int type_index = type - 1;
            if (type_index == 0) 
            {
                wclear(key_win);
                wrefresh(key_win);
                refresh();
                use_ancient_key();
                return 1;
            }
            else if (type_index == 1) 
            {
                if (inventory_keys[1] > 1)
                {
                    display_text("COMBINING TWO BROKEN KEYS...");
                    refresh();
                    wrefresh(key_win);
                    napms(1000);
                    flushinp();
                    clear_text();
                    inventory_keys[1] -= 2;
                    inventory_keys[0]++;
                }
            }
            current = 0;
        }
    }

    wrefresh(key_win);  
}

void show_current_weapon()
{
    if ((last_weapon == current_weapon) && current_weapon != -1)
    {
        switch (current_weapon)
        {
            case 1: mvprintw(35, 175, "WEAPON: 🗡"); break;
            case 2: mvprintw(35, 175, "WEAPON: 🪄"); break;
            case 3: mvprintw(35, 175, "WEAPON: ⬻"); break;
        }
    }
    else 
    {
        switch (current_weapon)
        {
            case 0: mvprintw(35, 175, "WEAPON: ⚒"); break;
            case 1: mvprintw(35, 175, "WEAPON: 🗡"); break;
            case 2: mvprintw(35, 175, "WEAPON: 🪄"); break;
            case 3: mvprintw(35, 175, "WEAPON: ⬻"); break;
            case 4: mvprintw(35, 175, "WEAPON: ⚔"); break;
            case 5: mvprintw(35, 175, "WEAPON: 💀"); break;
            default: mvprintw(35, 175, "WEAPON: _"); break;
        }
        switch (last_weapon)
        {
            case 1: mvprintw(35, 185, "🗡"); break;
            case 2: mvprintw(35, 185, "🪄"); break;
            case 3: mvprintw(35, 185, "⬻"); break;
            default: mvprintw(35, 185, "_"); break;
        }
    }
}
//-------------------------------------INVENTORY------------------------------------------------//

//-------------------------------------MONSTERS------------------------------------------------//

void set_monsters()
{
    display_rooms();
    display_paths();
    display_pillars();
    spawn_food();
    spawn_gold();
    spawn_weapon();
    show_ancient_key();
    show_traps();
    int has_monster[room_num];
    for (int i = 0; i < room_num; i++) has_monster[i] = 0;
    for (int i = 0; i < room_num; i++)
    {
        if (rooms[i].theme != 3 && rooms[i].theme != 2 && i != start_room)
        {
            int p = rand() % 2;
            if (p == 1)
            {
                int y, x;
                do 
                {
                    y = rooms[i].y + 1 + (rand() % (rooms[i].height - 2));
                    x = rooms[i].x + 1 + (rand() % (rooms[i].width - 2));
                } while ((mvinch(y, x) & A_CHARTEXT) != '.');
                monsters[monster_num].y = y; monsters[monster_num].x = x; monsters[monster_num].type = 1; monsters[monster_num].room = i; monsters[monster_num].max_steps = monster_steps; monsters[monster_num++].health = 5;
                has_monster[i]++;
            }
        }
    }

    for (int i = 0; i < room_num; i++)
    {
        if (rooms[i].theme != 3&& rooms[i].theme != 2 && i != start_room)
        {
            int p = rand() % 3;
            if (p == 1)
            {
                int y, x;
                do 
                {
                    y = rooms[i].y + 1 + (rand() % (rooms[i].height - 2));
                    x = rooms[i].x + 1 + (rand() % (rooms[i].width - 2));
                } while ((mvinch(y, x) & A_CHARTEXT) != '.');
                monsters[monster_num].y = y; monsters[monster_num].x = x; monsters[monster_num].type = 2; monsters[monster_num].room = i; monsters[monster_num].max_steps = monster_steps; monsters[monster_num++].health = 10;
                has_monster[i]++;
            }
        }
    }

    for (int i = 0; i < room_num; i++)
    {
        if (rooms[i].theme != 3 && rooms[i].theme != 2 && i != start_room)
        {
            int p = rand() % 6;
            if (p == 1 && has_monster[i] < 2)
            {
                int y, x;
                do 
                {
                    y = rooms[i].y + 1 + (rand() % (rooms[i].height - 2));
                    x = rooms[i].x + 1 + (rand() % (rooms[i].width - 2));
                } while ((mvinch(y, x) & A_CHARTEXT) != '.');
                monsters[monster_num].y = y; monsters[monster_num].x = x; monsters[monster_num].type = 3; monsters[monster_num].room = i; monsters[monster_num].max_steps = monster_steps; monsters[monster_num++].health = 15;
                has_monster[i]++;
            }
        }
    }

    for (int i = 0; i < room_num; i++)
    {
        if (rooms[i].theme != 3 && rooms[i].theme != 2 && i != start_room)
        {
            int p = rand() % 10;
            if (p == 1 && has_monster[i] < 2)
            {
                int y, x;
                do 
                {
                    y = rooms[i].y + 1 + (rand() % (rooms[i].height - 2));
                    x = rooms[i].x + 1 + (rand() % (rooms[i].width - 2));
                } while ((mvinch(y, x) & A_CHARTEXT) != '.');
                monsters[monster_num].y = y; monsters[monster_num].x = x; monsters[monster_num].type = 4; monsters[monster_num].room = i; monsters[monster_num].max_steps = 1000000; monsters[monster_num++].health = 20;
                has_monster[i]++;
            }
        }
    }

    for (int i = 0; i < room_num; i++)
    {
        if (rooms[i].theme != 3 && rooms[i].theme != 2 && i != start_room)
        {
            int p = rand() % 15;
            if (p == 1 && has_monster[i] < 2)
            {
                int y, x;
                do 
                {
                    y = rooms[i].y + 1 + (rand() % (rooms[i].height - 2));
                    x = rooms[i].x + 1 + (rand() % (rooms[i].width - 2));
                } while ((mvinch(y, x) & A_CHARTEXT) != '.');
                monsters[monster_num].y = y; monsters[monster_num].x = x; monsters[monster_num].type = 5; monsters[monster_num].room = i; monsters[monster_num].max_steps = monster_steps; monsters[monster_num++].health = 30;
                has_monster[i]++;
            }
        }
    }

    if (current_level == 4)
    {
        for (int i = 0; i < room_num; i++)
        {
            if (rooms[i].theme == 2)
            {
                int y = rooms[i].y + 1 + (rand() % (rooms[i].height - 2));
                int x = rooms[i].x + 1 + (rand() % (rooms[i].width - 2));
                monsters[monster_num].y = y; monsters[monster_num].x = x; monsters[monster_num].type = 6; monsters[monster_num].room = i; monsters[monster_num].max_steps = 1000000; monsters[monster_num++].health = 50;
            }
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
                case 6:
                    attron(COLOR_PAIR(32));
                    mvaddch(y, x, 'V');
                    attroff(COLOR_PAIR(32));
                    break;
            }
        }
    }
}

void check_monsters()
{
    int y = main_char.y, x = main_char.x;
    int in_room = 0;
    for (int i = 0; i < room_num; i++)
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

void move_monsters(monster *monsters, int n, int y, int x)
{
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
                        !(mon_x - 1 == x && mon_y + 1 == y) && flag && (mvinch(monsters[i].y + 1, monsters[i].x - 1) & A_CHARTEXT) == '.')
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
                        !(mon_x - 1 == x && mon_y - 1 == y) && flag && (mvinch(monsters[i].y - 1, monsters[i].x - 1) & A_CHARTEXT) == '.')
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
                        !(mon_x + 1 == x && mon_y + 1 == y) && flag && (mvinch(monsters[i].y + 1, monsters[i].x + 1) & A_CHARTEXT) == '.') 
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
                        !(mon_x + 1 == x && mon_y - 1 == y) && flag && (mvinch(monsters[i].y - 1, monsters[i].x + 1) & A_CHARTEXT) == '.')
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
                        if (flag && (mvinch(monsters[i].y, monsters[i].x + 1) & A_CHARTEXT) == '.') 
                        {monsters[i].x++; monsters[i].steps++;} 
                    }
                    else if (x < mon_x && mon_x - 1 != x)
                    {
                        int flag = 1;
                        for (int j = 0; j < monster_num; j++)
                        {
                            if (mon_y == monsters[j].y && mon_x - 1 == monsters[j].x) flag = 0;
                        }
                        if (flag && (mvinch(monsters[i].y, monsters[i].x - 1) & A_CHARTEXT) == '.') 
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
                        if (flag && (mvinch(monsters[i].y - 1, monsters[i].x) & A_CHARTEXT) == '.') 
                        {monsters[i].y--; monsters[i].steps++;}
                    }
                    else if (y > mon_y && mon_y + 1 != y && mon_y + 1 < rooms[room].y + rooms[room].height - 1)
                    {
                        int flag = 1;
                        for (int j = 0; j < monster_num; j++)
                        {
                            if (mon_x == monsters[j].x && mon_y + 1 == monsters[j].y) flag = 0;
                        }
                        if (flag && (mvinch(monsters[i].y + 1, monsters[i].x) & A_CHARTEXT) == '.') 
                        {monsters[i].y++; monsters[i].steps++;}
                    }
                }
            }
        }
    }   
}

void update_monsters_health(monster *monsters, int n)
{
    init_pair(71, COLOR_RED, COLOR_BLACK);
    if (in_fight_room == 1)
    {
        mvprintw(1, 75, "                          ");
        mvprintw(2, 75, "                          ");
        mvprintw(3, 75, "                          ");
        mvprintw(4, 75, "                          ");
        mvprintw(5, 75, "                          ");
    }
    else 
    {
        mvprintw(1, 75, "                          ");
        mvprintw(2, 75, "                          ");  
    }
    int y = 1;
    attron(COLOR_PAIR(71));
    for (int i = 0; i < n; i++)   
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
                case 6: symbol = 'V'; break;
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

void check_damage(monster *monsters, int n, int y, int x)
{
    if (recently_damaged == 0)
    {
        for (int i = 0; i < n; i++)
        {
            int mon_x = monsters[i].x, mon_y = monsters[i].y, mon_type = monsters[i].type;
            if (mon_x >= x - 1 && mon_x <= x + 1 && mon_y >= y - 1 && mon_y <= y + 1)
            {
                if (!in_fight_room)
                {
                    update_health();
                    update_energy();
                    update_score();
                    mvprintw(36, 1, "LEVEL: %d", current_level);
                    if (password_count_down > 0) display_password();
                    display_rooms();
                    display_paths();
                    display_windows();
                    display_pillars();
                    spawn_food();
                    spawn_weapon();
                    spawn_enchant();
                    spawn_gold();
                    show_ancient_key();
                    show_locked_door();
                    show_traps();
                    show_hidden_doors();
                    display_monsters();
                    show_current_weapon();
                    show_current_enchant();
                    update_monsters_health(monsters, monster_num);

                    if ((current_level < max_level) || (level_finished() && (current_level != 4)))
                    {
                        attron(COLOR_PAIR(32));
                        mvprintw(up_stairs[current_level - 1].y, up_stairs[current_level - 1].x, "»");
                        attroff(COLOR_PAIR(32));
                    }
                    if (current_level != 1)
                    {
                        attron(COLOR_PAIR(2));
                        mvprintw(down_stairs[current_level - 2].y, down_stairs[current_level - 2].x, "«");
                        attroff(COLOR_PAIR(2));
                    }
                    switch(PlayerSetting.color)
                    {
                        case 0: attron(COLOR_PAIR(31)); break;
                        case 1: attron(COLOR_PAIR(32)); break;
                        case 2: attron(COLOR_PAIR(33)); break;
                    }
                    mvprintw(main_char.y, main_char.x, "@");
                    attroff(COLOR_PAIR(31)); attroff(COLOR_PAIR(32)); attroff(COLOR_PAIR(33));
                }

                if (in_fight_room)
                {
                    attron(COLOR_PAIR(32));
                    for (int i = 0; i < 190; i++) mvaddch(20, i, '#');
                    for (int i = 6; i < 34; i++) mvaddch(i, 90, '#');
                    for (int i = 80; i < 100; i++) 
                    {
                        mvaddch(12, i, '-');
                        mvaddch(27, i, '_');
                    }
                    for (int i = 12; i < 28; i++)
                    {
                        mvaddch(i, 80, '|');
                        mvaddch(i, 100, '|');
                    }

                    attroff(COLOR_PAIR(32));
                    attron(COLOR_PAIR(2));
                    for (int i = 13; i < 27; i++)
                    {
                        for (int j = 81; j < 100; j++)
                        {
                            mvaddch(i, j, '.');
                        }
                    }
                    attroff(COLOR_PAIR(2));

                    for (int i = 0; i < fight_room_monsters_count; i++)
                    {
                        if (monsters[i].dead == 0) 
                        {
                            int mon_y = monsters[i].y, mon_x = monsters[i].x;
                            switch (monsters[i].type)
                            {
                                case 1: mvprintw(mon_y, mon_x, "D"); break;
                                case 2: mvprintw(mon_y, mon_x, "F"); break;
                                case 3: mvprintw(mon_y, mon_x, "G"); break;
                                case 4: mvprintw(mon_y, mon_x, "S"); break;
                            }
                        }
                    }
                    refresh();

                    switch(PlayerSetting.color)
                    {
                        case 0: attron(COLOR_PAIR(31)); break;
                        case 1: attron(COLOR_PAIR(32)); break;
                        case 2: attron(COLOR_PAIR(33)); break;
                    }
                    mvprintw(y, x, "@");
                    attroff(COLOR_PAIR(31)); attroff(COLOR_PAIR(32)); attroff(COLOR_PAIR(33));

                    update_health();
                    update_energy();
                    show_current_weapon();
                    show_current_enchant();
                    update_monsters_health(monsters, fight_room_monsters_count);
                    spawn_weapon(); 
                }
                
                if (mon_type == 1 || mon_type == 2 || mon_type == 3) health -= 1;
                else if (mon_type == 4) health -= 2;
                else if (mon_type == 5) health -= 2;
                else if (mon_type == 6) health -= 3;
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

void active_sleeping_monsters(monster *monsters, int n, int y, int x)
{
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

int use_weapon(monster *monsters, int n, int y, int x)
{  
    switch (current_weapon)
    {
        case 0: use_mace(monsters, n, y, x); break;
        case 1: use_dagger(monsters, n, y, x); break;
        case 2: use_magic_wand(monsters, n, y, x); break;
        case 3: use_arrow(monsters, n, y, x); break;
        case 4: use_sword(monsters, n, y, x); break;
        case 5: use_doombringer(monsters, n, y, x); break;
        default: return 1;
    }
    return 1;
}

void use_mace(monster *monsters, int n, int y, int x)
{
    display_text("YOU USED MACE");
    refresh();
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

    for (int i = 0; i < pillar_index; i++)
    {
        if (pillars[i].y >= y - 1 && pillars[i].y <= y + 1 && pillars[i].x >= x - 1 && pillars[i].x <= x + 1)
        {
            pillars[i].x = 0; pillars[i].y = 0;
        }
    }
    for (int i = 0; i < trap_index; i++)
    {
        if (traps[i].y >= y - 1 && traps[i].y <= y + 1 && traps[i].x >= x - 1 && traps[i].x <= x + 1)
        {
            traps[i].x = 0; traps[i].y = 0;
        }
    }
    napms(1000);
    flushinp();
    clear_text();

    return;
}

void use_dagger(monster *monsters, int n, int y, int x)
{
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
                throw_dagger(monsters, n, 1, y, x);
                inventory_weapon[1]--;
                if (inventory_weapon[1] == 0)
                {
                    current_weapon = -1;
                    last_weapon = -1;
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
                throw_dagger(monsters, n, 2, y, x);
                inventory_weapon[1]--;
                if (inventory_weapon[1] == 0)
                {
                    current_weapon = -1;
                    last_weapon = -1;
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
                throw_dagger(monsters, n, 3, y, x);
                inventory_weapon[1]--;
                if (inventory_weapon[1] == 0)
                {
                    current_weapon = -1;
                    last_weapon = -1;
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
                throw_dagger(monsters, n, 4,  y, x);
                inventory_weapon[1]--;
                if (inventory_weapon[1] == 0)
                {
                    current_weapon = -1;
                    last_weapon = -1;
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

void throw_dagger(monster *monsters, int n, int dir, int y, int x)
{
    int in_room = 0;
    if (in_fight_room) in_room = 1;
    for (int i = 0; i < room_num; i++)
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
                napms(300);
                flushinp();
                if ((mvinch(weapon_y - 1, x) & A_CHARTEXT) == '|' || (mvinch(weapon_y - 1, x) & A_CHARTEXT) == 'o' || (mvinch(weapon_y - 1, x) & A_CHARTEXT) == '_' || (mvinch(weapon_y - 1, x) & A_CHARTEXT) == '-' || (mvinch(weapon_y - 1, x) & A_CHARTEXT) == '+' ||  range == 5)
                {
                    if (in_fight_room)
                    {
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index].y = weapon_y; 
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index].x = weapon_x; 
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index++].type = 1;   
                    }
                    else 
                    {
                        throwed_weapons[throwed_weapon_index].y = weapon_y; 
                        throwed_weapons[throwed_weapon_index].x = weapon_x; 
                        throwed_weapons[throwed_weapon_index++].type = 1; 
                    }
                    break;
                }
                for (int i = 0; i < n; i++)
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
                napms(300);
                flushinp();
                if ((mvinch(weapon_y, weapon_x - 1) & A_CHARTEXT) == '|' || (mvinch(weapon_y, weapon_x - 1) & A_CHARTEXT) == 'o' || (mvinch(weapon_y, weapon_x - 1) & A_CHARTEXT) == '_' || (mvinch(weapon_y, weapon_x - 1) & A_CHARTEXT) == '-' || (mvinch(weapon_y, weapon_x - 1) & A_CHARTEXT) == '+' || range == 5)
                {
                    if (in_fight_room)
                    {
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index].y = weapon_y; 
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index].x = weapon_x; 
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index++].type = 1;   
                    }
                    else 
                    {
                        throwed_weapons[throwed_weapon_index].y = weapon_y; 
                        throwed_weapons[throwed_weapon_index].x = weapon_x; 
                        throwed_weapons[throwed_weapon_index++].type = 1; 
                    }
                    break;
                }
                for (int i = 0; i < n; i++)
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
                napms(300);
                flushinp();
                if ((mvinch(weapon_y + 1, x) & A_CHARTEXT) == '|' || (mvinch(weapon_y + 1, x) & A_CHARTEXT) == 'o' || (mvinch(weapon_y + 1, x) & A_CHARTEXT) == '_' || (mvinch(weapon_y + 1, x) & A_CHARTEXT) == '-' ||(mvinch(weapon_y + 1, x) & A_CHARTEXT) == '+' || range == 5)
                {
                    if (in_fight_room)
                    {
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index].y = weapon_y; 
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index].x = weapon_x; 
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index++].type = 1;   
                    }
                    else
                    {
                        throwed_weapons[throwed_weapon_index].y = weapon_y; 
                        throwed_weapons[throwed_weapon_index].x = weapon_x; 
                        throwed_weapons[throwed_weapon_index++].type = 1; 
                    }
                    break;
                }
                for (int i = 0; i < n; i++)
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
                napms(300);
                flushinp();
                if ((mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == '|' || (mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == 'o' || (mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == '_' || (mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == '-' || (mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == '+' || range == 5)
                {
                    if (in_fight_room)
                    {
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index].y = weapon_y; 
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index].x = weapon_x; 
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index++].type = 1;   
                    }
                    else
                    {
                        throwed_weapons[throwed_weapon_index].y = weapon_y; 
                        throwed_weapons[throwed_weapon_index].x = weapon_x; 
                        throwed_weapons[throwed_weapon_index++].type = 1; 
                    }
                    break;
                }
                for (int i = 0; i < n; i++)
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

void use_magic_wand(monster *monsters, int n, int y, int x)
{
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
                throw_magic_wand(monsters, n, 1, y, x);
                inventory_weapon[2]--;
                if (inventory_weapon[2] == 0)
                {
                    current_weapon = -1;
                    last_weapon = -1;
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
                throw_magic_wand(monsters, n, 2, y, x);
                inventory_weapon[2]--;
                if (inventory_weapon[2] == 0)
                {
                    current_weapon = -1;
                    last_weapon = -1;
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
                throw_magic_wand(monsters, n, 3, y, x);
                inventory_weapon[2]--;
                if (inventory_weapon[2] == 0)
                {
                    current_weapon = -1;
                    last_weapon = -1;
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
                throw_magic_wand(monsters, n, 4, y, x);
                inventory_weapon[2]--;
                if (inventory_weapon[2] == 0)
                {
                    current_weapon = -1;
                    last_weapon = -1;
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

void throw_magic_wand(monster *monsters, int n, int dir, int y, int x)
{
    int in_room = 0;
    if (in_fight_room) in_room = 1;
    for (int i = 0; i < room_num; i++)
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
                napms(300);
                flushinp();
                if ((mvinch(weapon_y - 1, x) & A_CHARTEXT) == '|' || (mvinch(weapon_y - 1, x) & A_CHARTEXT) == 'o' || (mvinch(weapon_y - 1, x) & A_CHARTEXT) == '_' || (mvinch(weapon_y - 1, x) & A_CHARTEXT) == '-' || (mvinch(weapon_y - 1, x) & A_CHARTEXT) == '+' || range == 10)
                {
                    if (in_fight_room)
                    {
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index].y = weapon_y; 
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index].x = weapon_x; 
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index++].type = 2;   
                    }
                    else
                    {
                        throwed_weapons[throwed_weapon_index].y = weapon_y; 
                        throwed_weapons[throwed_weapon_index].x = weapon_x; 
                        throwed_weapons[throwed_weapon_index++].type = 2; 
                    }
                    break;
                }
                for (int i = 0; i < n; i++)
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
                if (weapon_x != x && weapon_x != x - 1) mvprintw(weapon_y, weapon_x, "🪄");
                refresh();
                napms(300);
                flushinp();
                if ((mvinch(weapon_y, weapon_x - 1) & A_CHARTEXT) == '|' || (mvinch(weapon_y, weapon_x - 1) & A_CHARTEXT) == 'o' || (mvinch(weapon_y, weapon_x - 1) & A_CHARTEXT) == '_' || (mvinch(weapon_y, weapon_x - 1) & A_CHARTEXT) == '-' || (mvinch(weapon_y, weapon_x - 1) & A_CHARTEXT) == '+' || range == 10)
                {
                    if (in_fight_room)
                    {
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index].y = weapon_y; 
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index].x = weapon_x; 
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index++].type = 2;   
                    }
                    else
                    {
                        throwed_weapons[throwed_weapon_index].y = weapon_y; 
                        throwed_weapons[throwed_weapon_index].x = weapon_x; 
                        throwed_weapons[throwed_weapon_index++].type = 2; 
                    }
                    break;
                }
                for (int i = 0; i < n; i++)
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
                napms(300);
                flushinp();
                if ((mvinch(weapon_y + 1, x) & A_CHARTEXT) == '|' || (mvinch(weapon_y + 1, x) & A_CHARTEXT) == 'o' || (mvinch(weapon_y + 1, x) & A_CHARTEXT) == '_' || (mvinch(weapon_y + 1, x) & A_CHARTEXT) == '-' || (mvinch(weapon_y + 1, x) & A_CHARTEXT) == '+' || range == 10)
                {
                    if (in_fight_room)
                    {
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index].y = weapon_y; 
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index].x = weapon_x; 
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index++].type = 2;   
                    }
                    else
                    {
                        throwed_weapons[throwed_weapon_index].y = weapon_y; 
                        throwed_weapons[throwed_weapon_index].x = weapon_x; 
                        throwed_weapons[throwed_weapon_index++].type = 2; 
                    }
                    break;
                }
                for (int i = 0; i < n; i++)
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
                napms(300);
                flushinp();
                if ((mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == '|' || (mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == 'o' || (mvinch(weapon_y, weapon_x + 2) & A_CHARTEXT) == '|'|| (mvinch(weapon_y, weapon_x + 2) & A_CHARTEXT) == 'o' || (mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == ' ' || (mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == '_' || (mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == '-' || (mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == '+' || range == 10)
                {
                    if (in_fight_room)
                    {
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index].y = weapon_y; 
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index].x = weapon_x; 
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index++].type = 2;   
                    }
                    else 
                    {
                        throwed_weapons[throwed_weapon_index].y = weapon_y; 
                        throwed_weapons[throwed_weapon_index].x = weapon_x; 
                        throwed_weapons[throwed_weapon_index++].type = 2; 
                    }
                    break;
                }
                for (int i = 0; i < n; i++)
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
                if (weapon_x != x && weapon_x != x - 1) mvaddch(weapon_y, weapon_x, ' ');
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

void use_arrow(monster *monsters, int n, int y, int x)
{
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
                throw_arrow(monsters, n, 1, y, x);
                inventory_weapon[3]--;
                if (inventory_weapon[3] == 0)
                {
                    current_weapon = -1;
                    last_weapon = -1;
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
                throw_arrow(monsters, n, 2, y, x);
                inventory_weapon[3]--;
                if (inventory_weapon[3] == 0)
                {
                    current_weapon = -1;
                    last_weapon = -1;
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
                throw_arrow(monsters, n, 3, y, x);
                inventory_weapon[3]--;
                if (inventory_weapon[3] == 0)
                {
                    current_weapon = -1;
                    last_weapon = -1;
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
                throw_arrow(monsters, n, 4, y, x);
                inventory_weapon[3]--;
                if (inventory_weapon[3] == 0)
                {
                    current_weapon = -1;
                    last_weapon = -1;
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

void throw_arrow(monster *monsters, int n, int dir, int y, int x)
{
    int in_room = 0;
    if (in_fight_room) in_room = 1;
    for (int i = 0; i < room_num; i++)
    {
        if (y > rooms[i].y && y < rooms[i].y + rooms[i].height && x > rooms[i].x && x < rooms[i].x + rooms[i].width)
        {
            in_room = 1;
        }
    }
    if (y > rooms[100].y && y < rooms[100].y + rooms[100].height && x > rooms[100].x && x < rooms[100].x + rooms[100].width)
    {
        in_room = 1;
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
                if (weapon_y != y) mvprintw(weapon_y, weapon_x, "↟");
                refresh();
                napms(300);
                flushinp();
                if ((mvinch(weapon_y - 1, x) & A_CHARTEXT) == '|' || (mvinch(weapon_y - 1, x) & A_CHARTEXT) == 'o' || (mvinch(weapon_y - 1, x) & A_CHARTEXT) == '_' || (mvinch(weapon_y - 1, x) & A_CHARTEXT) == '-' || (mvinch(weapon_y - 1, x) & A_CHARTEXT) == '+' || range == 5)
                {
                    if (in_fight_room)
                    {
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index].y = weapon_y; 
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index].x = weapon_x; 
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index++].type = 3;   
                    }
                    else 
                    {
                        throwed_weapons[throwed_weapon_index].y = weapon_y; 
                        throwed_weapons[throwed_weapon_index].x = weapon_x; 
                        throwed_weapons[throwed_weapon_index++].type = 3; 
                    }
                    break;
                }
                for (int i = 0; i < n; i++)
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
                napms(300);
                flushinp();
                if ((mvinch(weapon_y, weapon_x - 1) & A_CHARTEXT) == '|' || (mvinch(weapon_y, weapon_x - 1) & A_CHARTEXT) == 'o' || (mvinch(weapon_y, weapon_x - 1) & A_CHARTEXT) == '_' || (mvinch(weapon_y, weapon_x - 1) & A_CHARTEXT) == '-' || (mvinch(weapon_y, weapon_x - 1) & A_CHARTEXT) == '+' || range == 5)
                {
                    if (in_fight_room)
                    {
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index].y = weapon_y; 
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index].x = weapon_x; 
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index++].type = 3;   
                    }
                    else
                    {
                        throwed_weapons[throwed_weapon_index].y = weapon_y; 
                        throwed_weapons[throwed_weapon_index].x = weapon_x; 
                        throwed_weapons[throwed_weapon_index++].type = 3; 
                    }
                    break;
                }
                for (int i = 0; i < n; i++)
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
                if (weapon_y != y) mvprintw(weapon_y, weapon_x, "↡");
                refresh();
                napms(300);
                flushinp();
                if ((mvinch(weapon_y + 1, x) & A_CHARTEXT) == '|' || (mvinch(weapon_y + 1, x) & A_CHARTEXT) == 'o' || (mvinch(weapon_y + 1, x) & A_CHARTEXT) == '_' || (mvinch(weapon_y + 1, x) & A_CHARTEXT) == '-' || (mvinch(weapon_y + 1, x) & A_CHARTEXT) == '+' || range == 5)
                {
                    if (in_fight_room)
                    {
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index].y = weapon_y; 
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index].x = weapon_x; 
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index++].type = 3;   
                    }
                    else
                    {
                        throwed_weapons[throwed_weapon_index].y = weapon_y; 
                        throwed_weapons[throwed_weapon_index].x = weapon_x; 
                        throwed_weapons[throwed_weapon_index++].type = 3; 
                    }
                    break;
                }
                for (int i = 0; i < n; i++)
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
                if (weapon_x != x) mvprintw(weapon_y, weapon_x, "↠");
                refresh();
                napms(300);
                flushinp();
                if ((mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == '|' || (mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == 'o' || (mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == '_' || (mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == '-' || (mvinch(weapon_y, weapon_x + 1) & A_CHARTEXT) == '+' || range == 5)
                {
                    if (in_fight_room)
                    {
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index].y = weapon_y; 
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index].x = weapon_x; 
                        throwed_weapons_fight_room[throwed_weapon_fight_room_index++].type = 3;   
                    }
                    else
                    {
                        throwed_weapons[throwed_weapon_index].y = weapon_y; 
                        throwed_weapons[throwed_weapon_index].x = weapon_x; 
                        throwed_weapons[throwed_weapon_index++].type = 3; 
                    }
                    break;
                }
                for (int i = 0; i < n; i++)
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

void use_sword(monster *monsters, int n, int y, int x)
{
    display_text("YOU USED SWORD");
    refresh();
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

void add_doombringer()
{
    display_text("YOU NOW HAVE THE DOOMBRINGER");
    refresh();
    napms(1000);
    flushinp();
    clear_text();
    inventory_weapon[5] = 1;
    show_weapon();
}

void use_doombringer(monster *monsters, int n, int y, int x)
{
    
    int in_room = 0;
    if (in_fight_room) in_room = 1;
    for (int i = 0; i < room_num; i++)
    {
        if (y > rooms[i].y && y < rooms[i].y + rooms[i].height - 1 && x > rooms[i].x && x < rooms[i].x + rooms[i].width)
        {
            in_room = 1;
        }
    }

    if (!in_room)
    {
        display_text("YOU MUST BE IN A ROOM TO USE DOOMBRINGER");
        refresh();
        napms(800);
        flushinp();
        clear_text();
        return;
    }

    display_text("YOU USED DOOMBRINGER");
    refresh();
    for (int i = 0; i < monster_num; i++)
    {
        int mon_x = monsters[i].x, mon_y = monsters[i].y;
        if (mon_x >= x - 2 && mon_x <= x + 2 && mon_y >= y - 2 && mon_y <= y + 2)
        {
            monsters[i].health -= 15;
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

void auto_shoot(monster *monsters, int n, int y, int x)
{
    if (last_weapon == -1)
    {
        display_text("NOTHING TO SHOOT");
        refresh();
        napms(800);
        flushinp();
        clear_text();
        return;
    }

    char monsters_symbols[] = {'V', 'U', 'S', 'G', 'F', 'D'};

    int p = -1;
    for (int i = 0; i < room_num; i++)
    {
        if (main_char.y > rooms[i].y && main_char.y < rooms[i].y + rooms[i].height && main_char.x > rooms[i].x && main_char.x < rooms[i].x + rooms[i].width)
        {
            p = i;
        }
    }

    if (in_fight_room) p = 100;

    if (p == -1) 
    {
        display_text("YOU ARE NOT IN ANY ROOM");
        refresh();
        napms(800);
        flushinp();
        clear_text();
        return;
    }

    for (int i = rooms[p].y; i < rooms[p].y + rooms[p].height; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if ((mvinch(i, x) & A_CHARTEXT) == monsters_symbols[j])
            {
                if (i > y)
                {
                    switch (last_weapon)
                    {
                        case 1: inventory_weapon[1]--; if (inventory_weapon[1] == 0) { current_weapon = -1; last_weapon = -1; } throw_dagger(monsters, n, 3, y, x); return;
                        case 2: inventory_weapon[2]--; if (inventory_weapon[2] == 0) { current_weapon = -1; last_weapon = -1; } throw_magic_wand(monsters, n, 3, y, x); return;
                        case 3: inventory_weapon[3]--; if (inventory_weapon[3] == 0) { current_weapon = -1; last_weapon = -1; } throw_arrow(monsters, n, 3, y, x); return;
                    }
                }
                else if (i < y)
                {
                    switch (last_weapon)
                    {
                        case 1: inventory_weapon[1]--; if (inventory_weapon[1] == 0) { current_weapon = -1; last_weapon = -1; } throw_dagger(monsters, n, 1, y, x); return;
                        case 2: inventory_weapon[2]--; if (inventory_weapon[2] == 0) { current_weapon = -1; last_weapon = -1; } throw_magic_wand(monsters, n, 1, y, x); return;
                        case 3: inventory_weapon[3]--; if (inventory_weapon[3] == 0) { current_weapon = -1; last_weapon = -1; } throw_arrow(monsters, n, 1, y, x); return;  
                    }
                }
            }
        }
    }

    for (int i = rooms[p].x; i < rooms[p].x + rooms[p].width; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if ((mvinch(y, i) & A_CHARTEXT) == monsters_symbols[j])
            {
                if (i > x)
                {
                    switch (last_weapon)
                    {
                        case 1: inventory_weapon[1]--; if (inventory_weapon[1] == 0) { current_weapon = -1; last_weapon = -1; } throw_dagger(monsters, n, 4, y, x); return;
                        case 2: inventory_weapon[2]--; if (inventory_weapon[2] == 0) { current_weapon = -1; last_weapon = -1; } throw_magic_wand(monsters, n, 4, y, x); return;
                        case 3: inventory_weapon[3]--; if (inventory_weapon[3] == 0) { current_weapon = -1; last_weapon = -1; } throw_arrow(monsters, n, 4, y, x); return;
                    }
                }
                else if (i < x)
                {
                    switch (last_weapon)
                    {
                        case 1: inventory_weapon[1]--; if (inventory_weapon[1] == 0) { current_weapon = -1; last_weapon = -1; } throw_dagger(monsters, n, 2, y, x); return;
                        case 2: inventory_weapon[2]--; if (inventory_weapon[2] == 0) { current_weapon = -1; last_weapon = -1; } throw_magic_wand(monsters, n, 2, y, x); return;
                        case 3: inventory_weapon[3]--; if (inventory_weapon[3] == 0) { current_weapon = -1; last_weapon = -1; } throw_arrow(monsters, n, 2, y, x); return;  
                    }
                }
            }
        }
    }
}
//-------------------------------------WEAPON_USAGE------------------------------------------------//


//-------------------------------------ENDING------------------------------------------------//
int gameover()
{
    if (health <= 0)
    {
        close_audio();
        init_audio();
        Mix_Music *defeat_music = Mix_LoadMUS("musics/defeat.mp3");
        Mix_PlayMusic(defeat_music, 1);
        init_pair(77, COLOR_GREEN, COLOR_BLACK);
        for (int i = 0; i < player_count; i++)
        {
            if (strcmp(players[i].username, current_user) == 0)
            {
                players[i].last_game_exists = 0;
            }
        }
        timeout(-1);
        clear();
        attron(COLOR_PAIR(32));
        mvprintw(10, 70, "                  _\\<");
        mvprintw(11, 70, "                 (   >");
        mvprintw(12, 70, "                 __)(");
        mvprintw(13, 70, "           _____/  //   ___");
        mvprintw(14, 70, "          /        \\\\  /  \\__");
        mvprintw(15, 70, "          |  _     //  \\     ||");
        mvprintw(16, 70, "          | | \\    \\\\  / _   ||");
        mvprintw(17, 70, "          | |  |    \\\\/ | \\  ||");
        mvprintw(18, 70, "          | |_/     |/  |  | ||");
        mvprintw(19, 70, "          | | \\     /|  |_/  ||");
        mvprintw(20, 70, "          | |  \\    \\|  |     >_ )");
        mvprintw(21, 70, "          | |   \\. _|\\  |    < _|=");
        mvprintw(22, 70, "          |          /_.| .  \\/");
        mvprintw(23, 70, "  *       | *   **  / * **  |\\)/)    **");
        mvprintw(24, 70, "   \\)))ejm97/.,(//,,..,,\\||(,wo,\\ ).((//");
        mvprintw(25, 70, "                             -  \\");

        mvprintw(26, 85, "GAME OVER");
        attroff(COLOR_PAIR(32));
        getch();
        getch();
        return 1;
    }
    return 0;
}

int saving_screen()
{
    for (int i = 0; i < player_count; i++)
    {
        if (strcmp(players[i].username, current_user) == 0)
        {
            players[i].last_game_exists = 1;
            players[i].last_game_last_level = current_level;
        }
    }

    clear();
    init_pair(100, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(100));
    mvprintw(15, 86, "SAVING...");
    for (int i = 0; i < 7; i++)
    {
        mvprintw(16, 86 + i, "▌");
        refresh();
        napms(1000);
    }
    attroff(COLOR_PAIR(100));
    return 5;  
}

int victory()
{
    if (current_level == 4)
    {
        int flag1 = 1;
        for (int i = 0; i < trap_index; i++)
        {
            if (traps[i].display == 0) flag1 = 0;
        }
        int flag2 = 1;
        for (int i = 0; i < monster_num; i++)
        {
            if (monsters[i].type == 6 && monsters[i].dead == 0) flag2 = 0;
        }

        if (flag1 && flag2)
        {
            close_audio();
            init_audio();
            Mix_Music *victory_music = Mix_LoadMUS("musics/victory.mp3");
            Mix_PlayMusic(victory_music, 1);
            init_pair(77, COLOR_GREEN, COLOR_BLACK);
            clear();
            timeout(-1);
            for (int i = 0; i < player_count; i++)
            {
                if (strcmp(players[i].username, current_user) == 0)
                {
                    players[i].last_game_exists = 0;
                    players[i].score += score;
                    players[i].finished_games++;
                }
            }
            attron(COLOR_PAIR(77));
            mvprintw(13, 65, "__     ______  _    _     __          ___ ");                 
            mvprintw(14, 65, "\\ \\   / / __ \\| |  | |    \\ \\        / (_)  ");             
            mvprintw(15, 65, " \\ \\_/ / |  | | |  | |     \\ \\  /\\  / / _ _ ");               
            mvprintw(16, 65, "  \\   /| |  | | |  |        \\ \\/  \\/ / | | '_ \\ ");             
            mvprintw(17, 65, "   | | | |__| | |__| |       \\  /\\  /  | | | | |");             
            mvprintw(18, 65, "   |_|  \\____/ \\____/         \\/  \\/   |_|_| |_|  ");   

            mvprintw(21, 85, "VICTORY");
            mvprintw(22, 83, "SCORE: %d", score);
            attroff(COLOR_PAIR(77));
            getch();
            getch();
            return 1;
        }
    }
    return 0;
}

//-------------------------------------ENDING------------------------------------------------//

//-------------------------------------CHANGE_LEVEL------------------------------------------------//

int next_level()
{
    save_level(current_level);
    clear();
    if (current_level < max_level) 
    {
        current_level++;
        return preparing(0, 0, 1);
    }
         
    else if (current_level == max_level) 
    {
        current_level++;
        max_level++;
        return preparing(1, 0, 1);
    }  
}

int previous_level()
{

    save_level(current_level);
    clear();
    current_level--;
    main_char.y = up_stairs[current_level - 1].y; main_char.x = up_stairs[current_level - 1].x - 1;
    return preparing(0, 0, -1);

}

void save_level(int level)
{
    char username[100];
    strcpy(username, current_user);
    char filename[200];
    sprintf(filename, "files/%s_%d", username, level);
    FILE *file = fopen(filename, "w"); // rooms -> x y width height theme visible
    fprintf(file, "rooms:\n");

    for (int i = 0; i < room_num; i++)
    {
        fprintf(file, "%d %d %d %d %d %d\n", rooms[i].x, rooms[i].y, rooms[i].width, rooms[i].height, rooms[i].theme, rooms[i].visible);
    }

    fprintf(file, "corridor: %d\n", corridor_index);

    for (int i = 0; i < corridor_index; i++)
    {
        fprintf(file, "%d %d\n", corridor[i].x, corridor[i].y);
    }

    fprintf(file, "door: %d\n", door_index);

    for (int i = 0; i < door_index; i++)
    {
        fprintf(file, "%d %d\n", door[i].x, door[i].y);
    }
    
    fprintf(file, "food: %d\n", food_index); // food -> x y type lifetime
    for (int i = 0; i < food_index; i++)
    {
        fprintf(file, "%d %d %d %d\n", food[i].x, food[i].y, food[i].type, food[i].lifetime);
    }

    fprintf(file, "weapon: %d\n", weapon_index); // weapon -> x y type 
    for (int i = 0; i < weapon_index; i++)
    {
        fprintf(file, "%d %d %d\n", weapons[i].x, weapons[i].y, weapons[i].type);
    }

    fprintf(file, "enchant: %d\n", enchant_index); // enchants -> x y type 
    for (int i = 0; i < enchant_index; i++)
    {
        fprintf(file, "%d %d %d\n", enchants[i].x, enchants[i].y, enchants[i].type);
    }

    fprintf(file, "traps: %d\n", trap_index); // traps -> x y display
    for (int i = 0; i < trap_index; i++) 
    {
        fprintf(file, "%d %d %d\n", traps[i].x, traps[i].y, traps[i].display);
    }

    fprintf(file, "hidden doors: %d\n", hidden_doors_index); // traps -> x y display
    for (int i = 0; i < hidden_doors_index; i++) 
    {
        fprintf(file, "%d %d %d\n", hidden_doors[i].x, hidden_doors[i].y, hidden_doors[i].display);
    }

    fprintf(file, "monsters: %d\n", monster_num); // monsters -> x y active dead health max_steps room steps type
    for (int i = 0; i < monster_num; i++)
    {
        fprintf(file, "%d %d %d %d %d %d %d %d %d\n", monsters[i].x, monsters[i].y, monsters[i].active, monsters[i].dead, monsters[i].health, monsters[i].max_steps, monsters[i].room, monsters[i].steps, monsters[i].type);
    }

    fprintf(file, "gold: %d\n", gold_index); // gold -> x y
    for (int i = 0; i < gold_index; i++)
    {
        fprintf(file, "%d %d\n", gold[i].x, gold[i].y);
    }

    fprintf(file, "throwed_weapon: %d\n", throwed_weapon_index); //throwed_weapon -> x y type
    for (int i = 0; i < throwed_weapon_index; i++)
    {
        fprintf(file, "%d %d %d\n", throwed_weapons[i].x, throwed_weapons[i].y, throwed_weapons[i].type);
    }

    fprintf(file, "windows: %d\n", windows_index); //windows-> x y 
    for (int i = 0; i < windows_index; i++)
    {
        fprintf(file, "%d %d\n", windows[i].x, windows[i].y);
    }

    fprintf(file, "pillars: %d\n", pillar_index); //pillars-> x y 
    for (int i = 0; i < pillar_index; i++)
    {
        fprintf(file, "%d %d\n", pillars[i].x, pillars[i].y);
    }

    fprintf(file, "ancient keys: %d\n", ancient_keys_index); //ancient keys-> x y 
    for (int i = 0; i < ancient_keys_index; i++)
    {
        fprintf(file, "%d %d\n", ancient_keys[i].x, ancient_keys[i].y);
    }

    fprintf(file, "locked door: %d %d\n", locked_door.x, locked_door.y);
    fprintf(file, "password generator: %d %d\n", password_generator.x, password_generator.y);
    fprintf(file, "password generator1: %d %d\n", password_generator1.x, password_generator1.y);
    fprintf(file, "password generator2: %d %d\n", password_generator2.x, password_generator2.y);
    fprintf(file, "tries: %d\n", tries);
    fprintf(file, "commited password: %d\n", commited_pass);

    fprintf(file, "level steps: %d\n", level_steps);

    fprintf(file, "visible map:\n");
    for (int i = 0; i < 34; i++)
    {
        for (int j = 0; j < 190; j++)
        {
            fprintf(file, "%d ", visible_map[i][j]);
        }
        fprintf(file, "\n");
    }

    fprintf(file, "visible map:\n");
    for (int i = 0; i < 34; i++)
    {
        for (int j = 0; j < 190; j++)
        {
            fprintf(file, "%d ", visible_map[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void load_map(int level)
{
    char username[100]; strcpy(username, current_user);
    char filename[200]; 
    sprintf(filename, "files/%s_%d", username, level);

    FILE *file = fopen(filename, "r");

    fscanf(file, " rooms:\n");
    int i = 0;
    while (i < room_num && fscanf(file, "%d %d %d %d %d %d\n", 
                &rooms[i].x, &rooms[i].y, 
                &rooms[i].width, &rooms[i].height, 
                &rooms[i].theme, &rooms[i].visible) == 6) 
    {
        i++;
    }

    fscanf(file, " corridor: %d\n", &corridor_index);
    i = 0;
    while (i < corridor_index && fscanf(file, "%d %d\n", 
                &corridor[i].x, &corridor[i].y) == 2) 
    {
        i++;
    }

    fscanf(file, " door: %d\n", &door_index);
    i = 0;
    while (i < door_index && fscanf(file, "%d %d\n", 
                &door[i].x, &door[i].y) == 2) 
    {
        i++;
    }

    fscanf(file, " food: %d\n", &food_index);
    i = 0;
    while (i < food_index && fscanf(file, "%d %d %d %d\n", 
                &food[i].x, &food[i].y, 
                &food[i].type, &food[i].lifetime) == 4) 
    {
        i++;
    }

    fscanf(file, " weapon: %d\n", &weapon_index);
    i = 0;
    while (i < weapon_index && fscanf(file, "%d %d %d\n", 
                &weapons[i].x, &weapons[i].y, 
                &weapons[i].type) == 3) 
    {
        i++;
    }

    fscanf(file, " enchant: %d\n", &enchant_index);
    i = 0;
    while (i < enchant_index && fscanf(file, "%d %d %d\n", 
                &enchants[i].x, &enchants[i].y, 
                &enchants[i].type) == 3) 
    {
        i++;
    }

    fscanf(file, " traps: %d\n", &trap_index);
    i = 0;
    while (i < trap_index && fscanf(file, "%d %d %d\n", 
                &traps[i].x, &traps[i].y, 
                &traps[i].display) == 3) 
    {
        i++;
    }

    fscanf(file, " hidden doors: %d\n", &hidden_doors_index);
    i = 0;
    while (i < hidden_doors_index && fscanf(file, "%d %d %d\n", 
                &hidden_doors[i].x, &hidden_doors[i].y, 
                &hidden_doors[i].display) == 3) 
    {
        i++;
    }

    fscanf(file, " monsters: %d\n", &monster_num);
    i = 0;
    while (i < monster_num && fscanf(file, "%d %d %d %d %d %d %d %d %d\n", 
                &monsters[i].x, &monsters[i].y, &monsters[i].active, &monsters[i].dead, &monsters[i].health, &monsters[i].max_steps,
                &monsters[i].room, &monsters[i].steps, &monsters[i].type) == 9) 
    {
        i++;
    }
     
    fscanf(file, " gold: %d\n", &gold_index);
    i = 0;
    while (i < gold_index && fscanf(file, "%d %d\n", 
                &gold[i].x, &gold[i].y) == 2) 
    {
        i++;
    }

    fscanf(file, " throwed_weapon: %d\n", &throwed_weapon_index);
    i = 0;
    while (i < throwed_weapon_index && fscanf(file, "%d %d %d\n", 
                &throwed_weapons[i].x, &throwed_weapons[i].y, &throwed_weapons[i].type) == 3) 
    {
        i++;
    }

    fscanf(file, " windows: %d\n", &windows_index);
    i = 0;
    while (i < windows_index && fscanf(file, "%d %d\n", 
                &windows[i].x, &windows[i].y) == 2) 
    {
        i++;
    }

    fscanf(file, " pillars: %d\n", &pillar_index);
    i = 0;
    while (i < pillar_index && fscanf(file, "%d %d\n", 
                &pillars[i].x, &pillars[i].y) == 2) 
    {
        i++;
    }


    fscanf(file, " ancient keys: %d\n", &ancient_keys_index);
    i = 0;
    while (i < ancient_keys_index && fscanf(file, "%d %d\n", 
                &ancient_keys[i].x, &ancient_keys[i].y) == 2) 
    {
        i++;
    }

    fscanf(file, " locked door: %d %d\n", &locked_door.x, &locked_door.y);
    fscanf(file, " password generator: %d %d\n", &password_generator.x, &password_generator.y);
    fscanf(file, " password generator1: %d %d\n", &password_generator1.x, &password_generator1.y);
    fscanf(file, " password generator2: %d %d\n", &password_generator2.x, &password_generator2.y);
    fscanf(file, " tries: %d\n", &tries);
    fscanf(file, " commited password: %d\n", &commited_pass);

    fscanf(file, " level steps: %d\n", &level_steps);

    fscanf(file, " visible map:\n");
    for (int i = 0; i < 34; i++) 
    {
        for (int j = 0; j < 190; j++) 
        {
            fscanf(file, " %d", &visible_map[i][j]);
        }
        fscanf(file, "\n");
    }
    
    fclose(file);
}

int level_finished()
{
    int flag = 1;
    for (int i = 0; i < room_num; i++)
    {
        if (rooms[i].visible == 0) flag = 0;
    }
    if ((flag) && (level_steps >= 400)) 
    {
        return 1;
    }
    return 0;
}
//-------------------------------------CHANGE_LEVEL------------------------------------------------//


//-------------------------------------SPECIAL_ROOMS------------------------------------------------//
int fight_room()
{
    close_audio();
    napms(200);
    init_audio();
    Mix_Music *music1 = Mix_LoadMUS("musics/music1.mp3");
    Mix_Music *music2 = Mix_LoadMUS("musics/music2.mp3");
    Mix_Music *music3 = Mix_LoadMUS("musics/music3.mp3");
    Mix_Music *music4 = Mix_LoadMUS("musics/music4.mp3");
    Mix_Music *music5 = Mix_LoadMUS("musics/music5.mp3");
    Mix_Music *fight_room_music = Mix_LoadMUS("/home/ali/Desktop/FOP/musics/fight_room_music.mp3");

    Mix_PlayMusic(fight_room_music, -1);

    int y = 26, x = 93;

    clear();
    rooms[100].x = 80; rooms[100].y = 12; rooms[100].width = 20; rooms[100].height = 15;

    monster fight_room_monsters[fight_room_monsters_count];
    for (int i = 0; i < fight_room_monsters_count; i++)
    {
        int mon_y, mon_x;
        do
        {
            mon_y = 13 + rand() % 6; 
            mon_x = 81 + rand() % 18;
        } while (mon_y == y && mon_x == x);
        fight_room_monsters[i].y = mon_y; fight_room_monsters[i].x = mon_x; fight_room_monsters[i].active = 1; fight_room_monsters[i].room = 100; // index for fight rooms
        fight_room_monsters[i].dead = 0; fight_room_monsters[i].max_steps = 1000000; fight_room_monsters[i].steps = 0;
        int p = rand() % 10;
        if (p == 0 || p == 1 || p == 2 || p == 3)
        {
            fight_room_monsters[i].type = 1; fight_room_monsters[i].health = 5;
        }
        else if (p == 4 || p == 5 || p == 6)
        {
            fight_room_monsters[i].type = 2; fight_room_monsters[i].health = 10;
        }
        else if (p == 7 || p == 8)
        {
            fight_room_monsters[i].type = 3; fight_room_monsters[i].health = 15;
        }
        else if (p == 9)
        {
            fight_room_monsters[i].type = 4; fight_room_monsters[i].health = 20;
        }
    }

    recently_damaged = 0;
    close_audio();
    init_audio();
    music1 = Mix_LoadMUS("musics/music1.mp3");
    music2 = Mix_LoadMUS("musics/music2.mp3");
    music3 = Mix_LoadMUS("musics/music3.mp3");
    music4 = Mix_LoadMUS("musics/music4.mp3");
    music5 = Mix_LoadMUS("musics/music5.mp3");
    fight_room_music = Mix_LoadMUS("musics/fight_room_music.mp3");
    Mix_PlayMusic(fight_room_music, -1);
    while (1)
    {
        clear();
        attron(COLOR_PAIR(32));
        for (int i = 0; i < 190; i++) mvaddch(20, i, '#');
        for (int i = 6; i < 40; i++) mvaddch(i, 90, '#');
        for (int i = 80; i < 100; i++) 
        {
            mvaddch(12, i, '-');
            mvaddch(27, i, '_');
        }
        for (int i = 12; i < 28; i++)
        {
            mvaddch(i, 80, '|');
            mvaddch(i, 100, '|');
        }

        attroff(COLOR_PAIR(32));
        attron(COLOR_PAIR(2));
        for (int i = 13; i < 27; i++)
        {
            for (int j = 81; j < 100; j++)
            {
                mvaddch(i, j, '.');
            }
        }
        attroff(COLOR_PAIR(2));

        for (int i = 0; i < fight_room_monsters_count; i++)
        {
            if (fight_room_monsters[i].dead == 0) 
            {
                int mon_y = fight_room_monsters[i].y, mon_x = fight_room_monsters[i].x;
                switch (fight_room_monsters[i].type)
                {
                    case 1: mvprintw(mon_y, mon_x, "D"); break;
                    case 2: mvprintw(mon_y, mon_x, "F"); break;
                    case 3: mvprintw(mon_y, mon_x, "G"); break;
                    case 4: mvprintw(mon_y, mon_x, "S"); break;
                }
            }
        }
        refresh();

        switch(PlayerSetting.color)
        {
            case 0: attron(COLOR_PAIR(31)); break;
            case 1: attron(COLOR_PAIR(32)); break;
            case 2: attron(COLOR_PAIR(33)); break;
        }
        mvprintw(y, x, "@");
        attroff(COLOR_PAIR(31)); attroff(COLOR_PAIR(32)); attroff(COLOR_PAIR(33));

        update_health();
        update_energy();
        show_current_weapon();
        show_current_enchant();
        update_monsters_health(fight_room_monsters, fight_room_monsters_count);
        spawn_weapon();
        check_collect(y, x);
        int c = getch();
        switch (c)
        {
            case 'w':
                if (possible(y - speed_index, x))
                {
                    y -= speed_index;
                    break;
                }
                break;
            case 's':
                if (possible(y + speed_index, x))
                {
                    y += speed_index; 
                    break;
                }
                break;
            case 'a':
                if (possible(y, x - speed_index))
                {
                    x -= speed_index;
                    break;
                }
                break;
            case 'd':
                if (possible(y, x + speed_index))
                {
                    x += speed_index;
                    break;
                }
                break;
            case 'e':
                if (possible(y - speed_index, x + speed_index))
                {
                    x += speed_index; y -= speed_index;
                    break;
                }
                break;
            case 'q':
                if (possible(y - speed_index, x - speed_index))
                {
                    x -= speed_index; y -= speed_index;
                    break;
                }
                break;
            case 'x':
                if (possible(y + speed_index, x + speed_index))
                {
                    x += speed_index; y += speed_index;
                    break;
                }
                break;
            case 'z':
                if (possible(y + speed_index, x - speed_index))
                {
                    x -= speed_index; y += speed_index;
                    break;
                }
                break;
            case 'i':
                if (c == 'i') clear();
                if (inventory()) break;

            case 32:
                if (c == 32) use_weapon(fight_room_monsters, fight_room_monsters_count, y, x);
                break;
            default: break;
            case 'u':
                auto_shoot(fight_room_monsters, fight_room_monsters_count, y, x);
                break;
        }


        if (c = 'w' || c == 's' || c == 'a' || c == 'd' || c == 'z' || c == 'x' || c == 'q' || c == 'e')
        {
            if (speed_count_down > 0) speed_count_down--;
            if (power_count_down > 0) power_count_down--;
            if (enchant_count_down > 0) enchant_count_down--;
            if (recently_damaged_count_down > 0) recently_damaged_count_down--;
            level_steps++;
        }

        if (recently_damaged_count_down <= 0) recently_damaged = 0;
        check_damage(fight_room_monsters, fight_room_monsters_count, y, x);
        if (gameover()) return 0;
        move_monsters(fight_room_monsters, fight_room_monsters_count, y, x);
        active_sleeping_monsters(fight_room_monsters, fight_room_monsters_count, y, x);

        int flag = 1;
        for (int i = 0; i < fight_room_monsters_count; i++)
        {
            if (fight_room_monsters[i].dead == 0) flag = 0;
        }
        if (flag)
        {
            in_fight_room = 0;
            clear();
            close_audio();
            napms(200);
            init_audio();
            music1 = Mix_LoadMUS("/home/ali/Desktop/FOP/musics/music1.mp3");
            music2 = Mix_LoadMUS("/home/ali/Desktop/FOP/musics/music2.mp3");
            music3 = Mix_LoadMUS("/home/ali/Desktop/FOP/musics/music3.mp3");
            music4 = Mix_LoadMUS("/home/ali/Desktop/FOP/musics/music4.mp3");
            music5 = Mix_LoadMUS("/home/ali/Desktop/FOP/musics/music5.mp3");
            switch (music_to_be_played)
            {
                case 0: Mix_PlayMusic(music1, -1); break;
                case 1: Mix_PlayMusic(music2, -1); break;
                case 2: Mix_PlayMusic(music3, -1); break;
                case 3: Mix_PlayMusic(music4, -1); break;
                case 4: Mix_PlayMusic(music5, -1); break;
            }
            return 1;
        }
    }
}

void nightmare_rooms()
{
    int y1, x1, y2, x2;
    for (int i = 0; i < room_num; i++)
    {
        if (rooms[i].theme == 3)
        {
            y1 = rooms[i].y;
            y2 = rooms[i].y + rooms[i].height;
            x1 = rooms[i].x;
            x2 = rooms[i].x + rooms[i].width;
        }
    }
    if (main_char.y >= y1 && main_char.y < y2 && main_char.x >= x1 && main_char.x <= x2)
    {
        in_nightmare_room = 1;
        int save_visible_map[34][190];
        for (int i = 0; i < 34; i++)
        {
            for (int j = 0; j < 190; j++)
            {
                save_visible_map[i][j] = visible_map[i][j];
                visible_map[i][j] = 0;
            }
        }
        while (main_char.y >= y1 && main_char.y < y2 && main_char.x >= x1 && main_char.x <= x2)
        {
            clear();
            for (int i = 0; i < 34; i++)
            {
                for (int j = 0; j < 190; j++)
                {
                    visible_map[i][j] = 0;
                }
            }
            for (int i = main_char.y - 1; i <= main_char.y + 1; i++)
            {
                for (int j = main_char.x - 2; j <= main_char.x + 2; j++)
                {
                    if (i >= y1 && i < y2 && j >= x1 && j <= x2)
                    {
                        visible_map[i][j] = 1;
                    }
                }
            }
            update_health();
            update_energy();
            update_score();
            mvprintw(36, 1, "LEVEL: %d", current_level);
            display_rooms();
            display_paths();
            spawn_food();
            spawn_weapon();
            spawn_enchant();
            spawn_gold();
            show_traps();
 
            switch(PlayerSetting.color)
            {
                case 0: attron(COLOR_PAIR(31)); break;
                case 1: attron(COLOR_PAIR(32)); break;
                case 2: attron(COLOR_PAIR(33)); break;
            }
            mvprintw(main_char.y, main_char.x, "@");
            attroff(COLOR_PAIR(31)); attroff(COLOR_PAIR(32)); attroff(COLOR_PAIR(33));
            refresh();
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
                default: break;
            }


            if (c = 'w' || c == 's' || c == 'a' || c == 'd' || c == 'z' || c == 'x' || c == 'q' || c == 'e')
            {
                if (count_down > 0) count_down--;
                if (speed_count_down > 0) speed_count_down--;
                if (power_count_down > 0) power_count_down--;
                if (enchant_count_down > 0) enchant_count_down--;
                if (steps_to_heal < reach_steps_to_heal) steps_to_heal++;
                if (recently_damaged_count_down > 0) recently_damaged_count_down--;
                level_steps++;
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

            for (int i = main_char.y - 1; i <= main_char.y + 1; i++)
            {
                for (int j = main_char.x - 2; j < main_char.x + 2; j++)
                {
                    visible_map[i][j] = 1;
                }
            }
            display_rooms();
            display_paths();
            spawn_food();
            spawn_weapon();
            spawn_enchant();
            spawn_gold();
            show_traps();
        }
        for (int i = 0; i < 34; i++)
        {
            for (int j = 0; j < 190; j++)
            {
                visible_map[i][j] = save_visible_map[i][j];
            }
        }
        in_nightmare_room = 0;
    } 
}

int enchant_room()
{
    clear();
    int y = main_char.y + 1, x = main_char.x;
    pair exit_door;
    exit_door.x = x; exit_door.y = y - 1;

    clear();
    rooms[101].x = x - 10; rooms[101].y = y - 5; rooms[101].width = 20; rooms[101].height = 10;
    enchant_room_enchants_index = rand() % 5 + 5;
    for (int i = 0; i < enchant_room_enchants_index; i++)
    {
        int enchant_y, enchant_x;
        do 
        {
            enchant_y = rooms[101].y + 1 + (rand() % (rooms[101].height - 2));
            enchant_x = rooms[101].x + 1 + (rand() % (rooms[101].width - 2));
        } while (enchant_y == exit_door.y);
        enchant_room_enchants[i].y = enchant_y; enchant_room_enchants[i].x = enchant_x;
        int p = rand() % 3;
        if (p == 0) enchant_room_enchants[i].type = 1;
        else if (p == 1) enchant_room_enchants[i].type = 2;
        else enchant_room_enchants[i].type = 3; 
    }

    recently_damaged = 0;
    time_t start_time, current_time;
    time(&start_time);
    init_pair(78, COLOR_CYAN, COLOR_BLACK);
    timeout(2000);
    while (1)
    {
        clear();
        time(&current_time);
        if (difftime(current_time, start_time) >= 4) 
        {
            if (health > 0) 
            {
                health--;
            }
            time(&start_time);
        }
        if (gameover()) return 0;
        attron(COLOR_PAIR(78));
        for (int i = rooms[101].x; i < rooms[101].x + rooms[101].width; i++) 
        {
            mvaddch(rooms[101].y, i, '-');
            mvaddch(rooms[101].y + rooms[101].height - 1, i, '_');
        }
        for (int i = rooms[101].y; i < rooms[101].y + rooms[101].height; i++)
        {
            mvaddch(i, rooms[101].x, '|');
            mvaddch(i, rooms[101].x + rooms[101].width, '|');
        }
        attroff(COLOR_PAIR(78));
        attron(COLOR_PAIR(32));
        for (int i = rooms[101].y + 1; i < rooms[101].y + rooms[101].height - 1; i++)
        {
            for (int j = rooms[101].x + 1; j < rooms[101].x + rooms[101].width; j++)
            {
                mvaddch(i, j, '.');
            }
        }
        attroff(COLOR_PAIR(32));
        for (int i = 0; i < enchant_room_enchants_index; i++)
        {
            if (enchant_room_enchants[i].x != 0)
            {
                switch (enchant_room_enchants[i].type)
                {
                    case 1: mvprintw(enchant_room_enchants[i].y, enchant_room_enchants[i].x, "🧪"); break;
                    case 2: mvprintw(enchant_room_enchants[i].y, enchant_room_enchants[i].x, "🗲"); break;
                    case 3: mvprintw(enchant_room_enchants[i].y, enchant_room_enchants[i].x, "🩸"); break;
                }
            }
        }
        refresh();

        switch(PlayerSetting.color)
        {
            case 0: attron(COLOR_PAIR(31)); break;
            case 1: attron(COLOR_PAIR(32)); break;
            case 2: attron(COLOR_PAIR(33)); break;
        }
        mvprintw(y, x, "@");
        attroff(COLOR_PAIR(31)); attroff(COLOR_PAIR(32)); attroff(COLOR_PAIR(33));
        attron(COLOR_PAIR(32));
        mvprintw(exit_door.y, exit_door.x, "?");
        attroff(COLOR_PAIR(32));
        update_health();
        update_energy();
        mvprintw(36, 1, "LEVEL: %d", current_level);
        show_current_weapon();
        show_current_enchant();
        check_collect(y, x);
        int c = getch();
        switch (c)
        {
            case 'w':
                if (possible(y - speed_index, x))
                {
                    y -= speed_index;
                    break;
                }
                break;
            case 's':
                if (possible(y + speed_index, x))
                {
                    y += speed_index; 
                    break;
                }
                break;
            case 'a':
                if (possible(y, x - speed_index))
                {
                    x -= speed_index;
                    break;
                }
                break;
            case 'd':
                if (possible(y, x + speed_index))
                {
                    x += speed_index;
                    break;
                }
                break;
            case 'e':
                if (possible(y - speed_index, x + speed_index))
                {
                    x += speed_index; y -= speed_index;
                    break;
                }
                break;
            case 'q':
                if (possible(y - speed_index, x - speed_index))
                {
                    x -= speed_index; y -= speed_index;
                    break;
                }
                break;
            case 'x':
                if (possible(y + speed_index, x + speed_index))
                {
                    x += speed_index; y += speed_index;
                    break;
                }
                break;
            case 'z':
                if (possible(y + speed_index, x - speed_index))
                {
                    x -= speed_index; y += speed_index;
                    break;
                }
                break;
            case 'i':
                if (c == 'i') clear();
                if (inventory()) break;
                break;
            default: break;
        }
        
        if (y == exit_door.y && x == exit_door.x)
        {
            clear();
            in_enchant_room = 0;
            timeout(timeout_interval);
            return 1;
        }
    }
}
//------------------------------------SPECIAL_ROOMS------------------------------------------------//

//-------------------------------------MENU------------------------------------------------//
int menu()
{
    refresh();
    timeout(-1);
    int startx, starty, width, height;
    WINDOW *menu_win;
    
    height = 6;
    width = 30;   
    starty = 12;           
    startx = 75;           

    menu_win = newwin(height, width, starty, startx);

    box(menu_win, 0, 0);

    wrefresh(menu_win);

    mvwprintw(menu_win, 0, (width - 10) / 2 + 1, " MENU ");

    mvwprintw(menu_win, 1, 1, "1. MAP");
    mvwprintw(menu_win, 2, 1, "2. SETTING");
    mvwprintw(menu_win, 3, 1, "3. INVENTORY");
    mvwprintw(menu_win, 4, 1, "4. SAVE AND EXIT");


    wrefresh(menu_win);

    wrefresh(menu_win);
    int c = getch();
    switch(c)
    {
        case '1':
            wclear(menu_win);
            wrefresh(menu_win);
            delwin(menu_win); 
            timeout(timeout_interval);
            return show_map();
            break;
        case '2':
            wclear(menu_win);
            wrefresh(menu_win);
            delwin(menu_win); 
            timeout(timeout_interval);
            return in_game_setting();
            break;
        case '3':
            wclear(menu_win);
            wrefresh(menu_win);
            delwin(menu_win); 
            timeout(timeout_interval);
            return inventory();
            break;
        case '4':
            if (!guest)
            {
                wclear(menu_win);
                wrefresh(menu_win);
                delwin(menu_win); 
                timeout(timeout_interval);
                return save_and_exit(current_level);
                break;
            }
        default:
            wclear(menu_win);
            wrefresh(menu_win);
            delwin(menu_win); 
            timeout(timeout_interval);
            return 1;
            break;
    }

    delwin(menu_win);   
}

int show_map()
{
    clear();
    refresh();
    int startx, starty, width, height;
    timeout(-1);
    WINDOW *map_win;
    
    height = LINES - 2;
    width = COLS - 4;   
    starty = 1;           
    startx = 2;           

    map_win = newwin(height, width, starty, startx);

    box(map_win, 0, 0);

    wrefresh(map_win);

    int save_visible_map[34][190];
    for (int i = 0; i < 34; i++)
    {
        for (int j = 0; j < 190; j++)
        {
            save_visible_map[i][j] = visible_map[i][j];
            visible_map[i][j] = 1;
        }
    }

    display_rooms();
    display_paths();
    display_windows();

    for (int i = 0; i < 34; i++)
    {
        for (int j = 0; j < 190; j++)
        {
            visible_map[i][j] = save_visible_map[i][j];
        }
    }

    getch();
    timeout(timeout_interval);
}

int in_game_setting()
{
    start_color();
    timeout(-1);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    Mix_Music *current_music;
    int current_music_index = music_to_be_played;
    switch (music_to_be_played)
    {
        case 0: current_music = Mix_LoadMUS("musics/music1.mp3"); break;
        case 1: current_music = Mix_LoadMUS("musics/music2.mp3"); break;
        case 2: current_music = Mix_LoadMUS("musics/music3.mp3"); break;
        case 3: current_music = Mix_LoadMUS("musics/music4.mp3"); break;
        case 4: current_music = Mix_LoadMUS("musics/music5.mp3"); break;
    }
    Mix_Music *music1 = Mix_LoadMUS("musics/music1.mp3");
    Mix_Music *music2 = Mix_LoadMUS("musics/music2.mp3");
    Mix_Music *music3 = Mix_LoadMUS("musics/music3.mp3");
    Mix_Music *music4 = Mix_LoadMUS("musics/music4.mp3");
    Mix_Music *music5 = Mix_LoadMUS("musics/music5.mp3");
    char difficulty[3][20] = {"EASY", "MEDIUM", "EXPERT"};
    char color[3][20] = {"DEFAULT", "RED", "BLUE"};
    char music[5][20] = {"MUSIC 1", "MUSIC 2", "MUSIC 3", "MUSIC 4", "MUSIC 5"};
    int current = 0;
    int previous_current;
    int difficulty_index = PlayerSetting.difficulty;;
    int color_index = PlayerSetting.color;
    int music_index = PlayerSetting.music;
    int music_changed = 0;
    int stop_music = 0;
    int music_ever_changed = 0;
    timeout(-1);
    while (1)
    {
        clear();
        if (music_changed == 1)
        {
            if (music_index == 0) Mix_PlayMusic(music1, -1);
            else if (music_index == 1) Mix_PlayMusic(music2, -1);
            else if (music_index == 2) Mix_PlayMusic(music3, -1);
            else if (music_index == 3) Mix_PlayMusic(music4, -1);
            else if (music_index == 4) Mix_PlayMusic(music5, -1);
        }
        if (stop_music)
        {
            Mix_PlayMusic(current_music, -1);
        }
        setting_border();
        mvprintw(12, 75, "DIFFICULTY");
        mvprintw(13, 75, "COLOR");
        mvprintw(14, 75, "SONG");
        refresh();
        if (current == 0)
        {
            attron(COLOR_PAIR(1));
        }
        for (int i = 0; i < 3; i++)
        {
            if (difficulty_index == i)
            {
                mvprintw(12, 90, "%s", difficulty[i]);
            }
        }
        attroff(COLOR_PAIR(1));
        if (current == 1)
        {
            attron(COLOR_PAIR(1));
        }
        for (int i = 0; i < 3; i++)
        {
            if (color_index == i)
            {
                mvprintw(13, 90, "%s", color[i]);
            }
        }
        attroff(COLOR_PAIR(1));
        if (current == 2)
        {
            attron(COLOR_PAIR(1));
        }
        for (int i = 0; i < 5; i++)
        {
            if (music_index == i)
            {
                mvprintw(14, 90, "%s", music[i]);
            }
        }
        attroff(COLOR_PAIR(1));
        refresh();
        int c = getch();
        switch (c)
        {
            case KEY_DOWN:
                previous_current = current;
                current = (current + 1 <= 2) ? current + 1 : 0;
                if (current == 2) 
                {
                    music_changed = 1;
                    stop_music = 0;
                }
                else if (previous_current == 2) 
                {
                    stop_music = 1;
                    music_changed = 0;
                }
                else 
                {
                    stop_music = 0;
                    music_changed = 0;
                }
                break;
            case KEY_UP:
                previous_current = current;
                current = (current - 1 >= 0) ? current - 1 : 2;
                if (current == 2) 
                {
                    music_changed = 1;
                    stop_music = 0;
                }
                else if (previous_current == 2) 
                {
                    stop_music = 1;
                    music_changed = 0;
                }
                else 
                {
                    stop_music = 0;
                    music_changed = 0;
                }
                break;
            case KEY_LEFT: 
                switch (current)
                {
                    case 0:
                        difficulty_index = (difficulty_index - 1 >= 0) ? difficulty_index - 1 : 2;
                        music_changed = 0;
                        break; 
                    case 1:
                        color_index = (color_index - 1 >= 0) ? color_index - 1 : 2;
                        music_changed = 0;
                        break;
                    case 2:
                        music_index = (music_index - 1 >= 0) ? music_index - 1 : 4;
                        music_changed = 1;
                        music_ever_changed = 1;
                        break;
                } 
                break;
            case KEY_RIGHT:
                switch (current)
                {
                    case 0:
                        difficulty_index = (difficulty_index + 1 <= 2) ? difficulty_index + 1 : 0;
                        music_changed = 0;
                        break;
                    case 1:
                        color_index = (color_index + 1 <= 2) ? color_index + 1 : 0;
                        music_changed = 0;
                        break;
                    case 2:
                        music_index = (music_index + 1 <= 4) ? music_index + 1 : 0;
                        music_changed = 1;
                        music_ever_changed = 1;
                        break;
                } 
                break;
            case '\n':
                PlayerSetting.difficulty = difficulty_index;
                PlayerSetting.color = color_index;
                PlayerSetting.music = music_index;
                music_to_be_played = PlayerSetting.music;
                game_difficulty = PlayerSetting.difficulty;
                main_char_color = PlayerSetting.color;
                switch (game_difficulty)
                {
                    case 0: interval_time = 15; timeout_interval = 5000; damage_interval = 3; heal_count_down = 40; food_lifetime = 300; reach_recently_damaged_count_down = 20; fight_room_monsters_count = 3; break;
                    case 1: interval_time = 10; timeout_interval = 2000; damage_interval = 3; heal_count_down = 50; food_lifetime = 200; reach_recently_damaged_count_down = 15; fight_room_monsters_count = 4; break;
                    case 2: interval_time = 10; timeout_interval = 1000; damage_interval = 3; heal_count_down = 60; food_lifetime = 100; reach_recently_damaged_count_down = 10; fight_room_monsters_count = 5; break;
                }

                timeout(timeout_interval);
                if (current_music_index != music_to_be_played)
                {
                    if (music_to_be_played == 0) Mix_PlayMusic(music1, -1);
                    else if (music_to_be_played == 1) Mix_PlayMusic(music2, -1);
                    else if (music_to_be_played == 2) Mix_PlayMusic(music3, -1);
                    else if (music_to_be_played == 3) Mix_PlayMusic(music4, -1);
                    else if (music_to_be_played == 4) Mix_PlayMusic(music5, -1);
                }
                recently_damaged_count_down = reach_recently_damaged_count_down;
                count_down = heal_count_down;
                return 1;
        }
    }  
}

int save_and_exit(int level)
{
    if (in_fight_room)
    {
        display_text("CANNOT SAVE IN FIGHT ROOM");
        refresh();
        napms(1000);
        flushinp();
        clear_text();
        refresh();
        return 0;
    }

    char username[100];
    strcpy(username, current_user);
    char filename[200];
    sprintf(filename, "files/%s_%d", username, level);
    FILE *file = fopen(filename, "w"); // rooms -> x y width height theme visible
    fprintf(file, "rooms:\n");

    for (int i = 0; i < room_num; i++)
    {
        fprintf(file, "%d %d %d %d %d %d\n", rooms[i].x, rooms[i].y, rooms[i].width, rooms[i].height, rooms[i].theme, rooms[i].visible);
    }

    fprintf(file, "corridor: %d\n", corridor_index);

    for (int i = 0; i < corridor_index; i++)
    {
        fprintf(file, "%d %d\n", corridor[i].x, corridor[i].y);
    }

    fprintf(file, "door: %d\n", door_index);

    for (int i = 0; i < door_index; i++)
    {
        fprintf(file, "%d %d\n", door[i].x, door[i].y);
    }
    
    fprintf(file, "food: %d\n", food_index); // food -> x y type lifetime
    for (int i = 0; i < food_index; i++)
    {
        fprintf(file, "%d %d %d %d\n", food[i].x, food[i].y, food[i].type, food[i].lifetime);
    }

    fprintf(file, "weapon: %d\n", weapon_index); // weapon -> x y type 
    for (int i = 0; i < weapon_index; i++)
    {
        fprintf(file, "%d %d %d\n", weapons[i].x, weapons[i].y, weapons[i].type);
    }

    fprintf(file, "enchant: %d\n", enchant_index); // enchants -> x y type 
    for (int i = 0; i < enchant_index; i++)
    {
        fprintf(file, "%d %d %d\n", enchants[i].x, enchants[i].y, enchants[i].type);
    }

    fprintf(file, "traps: %d\n", trap_index); // traps -> x y display
    for (int i = 0; i < trap_index; i++) 
    {
        fprintf(file, "%d %d %d\n", traps[i].x, traps[i].y, traps[i].display);
    }

    fprintf(file, "hidden doors: %d\n", hidden_doors_index); // traps -> x y display
    for (int i = 0; i < hidden_doors_index; i++) 
    {
        fprintf(file, "%d %d %d\n", hidden_doors[i].x, hidden_doors[i].y, hidden_doors[i].display);
    }

    fprintf(file, "monsters: %d\n", monster_num); // monsters -> x y active dead health max_steps room steps type
    for (int i = 0; i < monster_num; i++)
    {
        fprintf(file, "%d %d %d %d %d %d %d %d %d\n", monsters[i].x, monsters[i].y, monsters[i].active, monsters[i].dead, monsters[i].health, monsters[i].max_steps, monsters[i].room, monsters[i].steps, monsters[i].type);
    }

    fprintf(file, "gold: %d\n", gold_index); // gold -> x y
    for (int i = 0; i < gold_index; i++)
    {
        fprintf(file, "%d %d\n", gold[i].x, gold[i].y);
    }

    fprintf(file, "throwed_weapon: %d\n", throwed_weapon_index); //throwed_weapon -> x y type
    for (int i = 0; i < throwed_weapon_index; i++)
    {
        fprintf(file, "%d %d %d\n", throwed_weapons[i].x, throwed_weapons[i].y, throwed_weapons[i].type);
    }

    fprintf(file, "windows: %d\n", windows_index); //windows-> x y 
    for (int i = 0; i < windows_index; i++)
    {
        fprintf(file, "%d %d\n", windows[i].x, windows[i].y);
    }

    fprintf(file, "pillars: %d\n", pillar_index); //pillars-> x y 
    for (int i = 0; i < pillar_index; i++)
    {
        fprintf(file, "%d %d\n", pillars[i].x, pillars[i].y);
    }

    fprintf(file, "ancient keys: %d\n", ancient_keys_index); //ancient keys-> x y 
    for (int i = 0; i < ancient_keys_index; i++)
    {
        fprintf(file, "%d %d\n", ancient_keys[i].x, ancient_keys[i].y);
    }

    fprintf(file, "locked door: %d %d\n", locked_door.x, locked_door.y);
    fprintf(file, "password generator: %d %d\n", password_generator.x, password_generator.y);
    fprintf(file, "password generator1: %d %d\n", password_generator1.x, password_generator1.y);
    fprintf(file, "password generator2: %d %d\n", password_generator2.x, password_generator2.y);
    fprintf(file, "doombringer: %d\n", doombringer);
    fprintf(file, "tries: %d\n", tries);
    fprintf(file, "commited password: %d\n", commited_pass);

    fprintf(file, "level steps: %d\n", level_steps);
    fprintf(file, "max level: %d\n", max_level);
    fprintf(file, "current level: %d\n", current_level);
    fprintf(file, "health: %d\n", health);
    fprintf(file, "energy: %d\n", energy);
    fprintf(file, "score: %d\n", score);
    fprintf(file, "inventory food: ");
    fprintf(file, "%d %d %d %d\n", inventory_food[0], inventory_food[1], inventory_food[2], inventory_food[3]);
    fprintf(file, "inventory weapon: ");
    fprintf(file, "%d %d %d %d %d\n", inventory_weapon[0], inventory_weapon[1], inventory_weapon[2], inventory_weapon[3], inventory_weapon[4]);
    fprintf(file, "inventory enchant: ");
    fprintf(file, "%d %d %d\n", inventory_enchant[0], inventory_enchant[1], inventory_enchant[2]);
    fprintf(file, "y: %d x: %d\n", main_char.y, main_char.x);

    fprintf(file, "up stairs: %d\n", max_level == 4 ? 3 : max_level); //stairs -> x y
    for (int i = 0; i < (max_level == 4 ? 3 : max_level); i++)
    {
        fprintf(file, "%d %d\n", up_stairs[i].x, up_stairs[i].y);
    }
    fprintf(file, "down stairs: %d\n", max_level - 1); //stairs -> x y
    for (int i = 0; i < max_level - 1; i++)
    {
        fprintf(file, "%d %d\n", down_stairs[i].x, down_stairs[i].y);
    }

    fprintf(file, "visible map:\n");
    for (int i = 0; i < 34; i++)
    {
        for (int j = 0; j < 190; j++)
        {
            fprintf(file, "%d ", visible_map[i][j]);
        }
        fprintf(file, "\n");
    }

    fprintf(file, "visible map:\n");
    for (int i = 0; i < 34; i++)
    {
        for (int j = 0; j < 190; j++)
        {
            fprintf(file, "%d ", visible_map[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);

    return saving_screen();
}

void load_saved_game()
{
    for (int i = 0; i < player_count; i++)
    {
        if (strcmp(players[i].username, current_user) == 0)
        {
            current_level = players[i].last_game_last_level;
        }
    }

    printf("current level :%d\n", current_level);
    char filename[200];
    sprintf(filename, "files/%s_%d", current_user, current_level);
    FILE *file = fopen(filename, "r");

    fscanf(file, " rooms:\n");
    int i = 0;
    while (i < room_num && fscanf(file, "%d %d %d %d %d %d\n", 
                &rooms[i].x, &rooms[i].y, 
                &rooms[i].width, &rooms[i].height, 
                &rooms[i].theme, &rooms[i].visible) == 6) 
    {
        i++;
    }

    fscanf(file, " corridor: %d\n", &corridor_index);
    i = 0;
    while (i < corridor_index && fscanf(file, "%d %d\n", 
                &corridor[i].x, &corridor[i].y) == 2) 
    {
        i++;
    }

    fscanf(file, " door: %d\n", &door_index);
    i = 0;
    while (i < door_index && fscanf(file, "%d %d\n", 
                &door[i].x, &door[i].y) == 2) 
    {
        i++;
    }

    fscanf(file, " food: %d\n", &food_index);
    i = 0;
    while (i < food_index && fscanf(file, "%d %d %d %d\n", 
                &food[i].x, &food[i].y, 
                &food[i].type, &food[i].lifetime) == 4) 
    {
        i++;
    }

    fscanf(file, " weapon: %d\n", &weapon_index);
    i = 0;
    while (i < weapon_index && fscanf(file, "%d %d %d\n", 
                &weapons[i].x, &weapons[i].y, 
                &weapons[i].type) == 3) 
    {
        i++;
    }

    fscanf(file, " enchant: %d\n", &enchant_index);
    i = 0;
    while (i < enchant_index && fscanf(file, "%d %d %d\n", 
                &enchants[i].x, &enchants[i].y, 
                &enchants[i].type) == 3) 
    {
        i++;
    }

    fscanf(file, " traps: %d\n", &trap_index);
    i = 0;
    while (i < trap_index && fscanf(file, "%d %d %d\n", 
                &traps[i].x, &traps[i].y, 
                &traps[i].display) == 3) 
    {
        i++;
    }

    fscanf(file, " hidden doors: %d\n", &hidden_doors_index);
    i = 0;
    while (i < hidden_doors_index && fscanf(file, "%d %d %d\n", 
                &hidden_doors[i].x, &hidden_doors[i].y, 
                &hidden_doors[i].display) == 3) 
    {
        i++;
    }

    fscanf(file, " monsters: %d\n", &monster_num);
    i = 0;
    while (i < monster_num && fscanf(file, "%d %d %d %d %d %d %d %d %d\n", 
                &monsters[i].x, &monsters[i].y, &monsters[i].active, &monsters[i].dead, &monsters[i].health, &monsters[i].max_steps,
                &monsters[i].room, &monsters[i].steps, &monsters[i].type) == 9) 
    {
        i++;
    }
     
    fscanf(file, " gold: %d\n", &gold_index);
    i = 0;
    while (i < gold_index && fscanf(file, "%d %d\n", 
                &gold[i].x, &gold[i].y) == 2) 
    {
        i++;
    }

    fscanf(file, " throwed_weapon: %d\n", &throwed_weapon_index);
    i = 0;
    while (i < throwed_weapon_index && fscanf(file, "%d %d %d\n", 
                &throwed_weapons[i].x, &throwed_weapons[i].y, &throwed_weapons[i].type) == 3) 
    {
        i++;
    }

    fscanf(file, " windows: %d\n", &windows_index);
    i = 0;
    while (i < windows_index && fscanf(file, "%d %d\n", 
                &windows[i].x, &windows[i].y) == 2) 
    {
        i++;
    }

    fscanf(file, " pillars: %d\n", &pillar_index);
    i = 0;
    while (i < pillar_index && fscanf(file, "%d %d\n", 
                &pillars[i].x, &pillars[i].y) == 2) 
    {
        i++;
    }

    fscanf(file, " ancient keys: %d\n", &ancient_keys_index);
    i = 0;
    while (i < ancient_keys_index && fscanf(file, "%d %d\n", 
                &ancient_keys[i].x, &ancient_keys[i].y) == 2) 
    {
        i++;
    }

    fscanf(file, " locked door: %d %d\n", &locked_door.x, &locked_door.y);
    fscanf(file, " password generator: %d %d\n", &password_generator.x, &password_generator.y);
    fscanf(file, " password generator1: %d %d\n", &password_generator1.x, &password_generator1.y);
    fscanf(file, " password generator2: %d %d\n", &password_generator2.x, &password_generator2.y);
    fscanf(file, " doombringer: %d\n", &doombringer);
    fscanf(file, " tries: %d\n", &tries);
    fscanf(file, " commited password: %d\n", &commited_pass);

    fscanf(file, " level steps: %d\n", &level_steps);
    fscanf(file, " max level: %d\n", &max_level);
    fscanf(file, " current level: %d\n",&current_level);
    fscanf(file, " health: %d\n", &health);
    fscanf(file, " energy: %d\n", &energy);
    fscanf(file, " score: %d\n", &score);
    fscanf(file, " inventory food: ");
    for (int i = 0; i < 4; i++)
    {
        fscanf(file, "%d", &inventory_food[i]);
    } fscanf(file, "\n");
    fscanf(file, " inventory weapon: ");
    for (int i = 0; i < 5; i++)
    {
        fscanf(file, "%d", &inventory_weapon[i]);
    } fscanf(file, "\n");
    fscanf(file, " inventory enchant: ");
    for (int i = 0; i < 3; i++)
    {
        fscanf(file, "%d", &inventory_enchant[i]);
    } fscanf(file, "\n");
    fscanf(file, " y: %d x: %d\n", &main_char.y, &main_char.x);

    int trash;
    fscanf(file, "up stairs: %d\n", &trash);
    for (int i = 0; i < (max_level == 4 ? 3 : max_level); i++)
    {
        fscanf(file, "%d %d\n", &up_stairs[i].x, &up_stairs[i].y);
    }
    fscanf(file, "down stairs: %d\n", &trash);
    for (int i = 0; i < max_level - 1; i++)
    {
        fscanf(file, "%d %d\n", &down_stairs[i].x, &down_stairs[i].y);
    }


    fscanf(file, " visible map:\n");
    for (int i = 0; i < 34; i++) 
    {
        for (int j = 0; j < 190; j++) 
        {
            fscanf(file, " %d", &visible_map[i][j]);
        }
        fscanf(file, "\n");
    }

    fclose(file);
}
//-------------------------------------MENU------------------------------------------------//

//-------------------------------------KEY------------------------------------------------//
void use_ancient_key()
{
    int y = main_char.y, x = main_char.x;
    if (y >= locked_door.y - 1 && y <= locked_door.y + 1 && (x == locked_door.x - 1 || x == locked_door.x + 1) && is_locked == 1)
    {
        int p = rand() % 100;
        if (p < 40)
        {
            display_text("THE KEY HAS BROKEN!");
            napms(1000);
            flushinp();
            clear_text();
            inventory_keys[0]--;
            inventory_keys[1]++;
        }
        else
        {
            if (current_level == 3)
            {
                display_text("YOU HAVE COLLECTED THE FIRST PART OF 'DOOMBRINGET'");
                refresh();
                napms(1000);
                flushinp();
                clear_text();
            }
            else if (current_level == 4)
            {
                display_text("YOU HAVE COLLECTED THE SECOND PART OF 'DOOMBRINGET'");
                refresh();
                napms(1000);
                flushinp();
                clear_text();  
            }
            doombringer++;
            if (doombringer >= 2) add_doombringer();
            is_locked = 0;
            password_count_down = 0;
        }
    }
}
//-------------------------------------KEY------------------------------------------------//
#endif