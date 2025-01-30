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

int music_to_be_played;
int game_difficulty;
int main_char_color;



void newgmae()
{
    for (int i = 0; i < 34; i++)
    {
        for (int j = 0; j < 190; j++)
        {
            visible_map[i][j] = 0;
            map[i][j].ch = 0; map[i][j].color = 0;
        }
    }
}


void x()
{

}