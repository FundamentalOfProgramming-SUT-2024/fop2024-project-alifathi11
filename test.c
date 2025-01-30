#include <stdio.h>
#include <string.h>

int max_level = 1;
int current_level = 1;

int level_steps;

int visible_map[34][190];

typedef struct {
    int x;
    int y;
} pair;

pair pillars[10]; 
int pillar_index = 0;

pair up_stairs[3];
int up_stairs_index = 0;
pair down_stairs[3];
int down_stairs_index = 0;

pair windows[10];
int windows_index = 0;

typedef struct {
    int y;
    int x;
    int width;
    int height;
    int theme; // 1 for normal, 2 for enchant, 3 for nightmare
    int visible;
} room;

room rooms[200];
int room_count;

pair main_char;
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

int fight_room_monsters_count;

int current_weapon = -1;

typedef struct {
    int y;
    int x;
    int type;  // 1 for dagger 2 for magic wand 3 for arrow
} throwed_weapon;

throwed_weapon throwed_weapons[100]; 
int throwed_weapon_index = 0;
throwed_weapon throwed_weapons_fight_room[100]; 
int throwed_weapon_fight_room_index = 0;

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
} trap;

trap traps[10];
int trap_index;

int in_fight_room = 0;

pair gold[20];
int gold_index = 0;

int score = 0;

void main()
{

    char filename[200] = "ali_2.txt";

    FILE *file = fopen(filename, "r");
    if (!file) return;

    fscanf(file, " rooms:\n");
    int i = 0;
    while (i < 6 && fscanf(file, "%d %d %d %d %d %d\n", 
                &rooms[i].x, &rooms[i].y, 
                &rooms[i].width, &rooms[i].height, 
                &rooms[i].theme, &rooms[i].visible) == 6) 
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
    printf("Trap index read: %d\n", trap_index);  // Debugging statement
    i = 0;
    while (i < trap_index) {
        int x, y, display;
        int result = fscanf(file, "%d %d %d\n", &x, &y, &display);
        if (result == 3) {
            printf("Trap %d: x=%d, y=%d, display=%d\n", i+1, x, y, display);  // Debugging statement
            traps[i].x = x;
            traps[i].y = y;
            traps[i].display = display;
            i++;
        } else {
            printf("Error reading trap data\n");  // Debugging statement
            break;
        }
    }
    return;
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

    fscanf(file, " visible map:\n");
    for (int i = 0; i < 34; i++) 
    {
        for (int j = 0; j < 190; j++) 
        {
            fscanf(file, " %d", &visible_map[i][j]);
        }
    }
    
    fclose(file);


    // printf("%d\n", trap_index);
    // for (int i = 0; i < trap_index; i++)
    // {
    //     printf("%d %d %d\n", traps[i].x, traps[i].y, traps[i].display);
    // }
}
