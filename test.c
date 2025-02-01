#include <stdio.h>

int max_level = 1;
int current_level = 1;

int level_steps = 0;

int visible_map[34][190];

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
int room_num = 10;

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
weapon weapons[100];
int weapon_index = 0;
int inventory_weapon[5];

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

int main()
{
    char filename[200] = "files/alifathi_1";
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

    for (int i = 0; i < room_num; i++)
    {
        printf("%d %d %d %d %d %d\n", rooms[i].x, rooms[i].y, rooms[i].width, rooms[i].height, rooms[i].theme, rooms[i].visible);
    }
    return 1;

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