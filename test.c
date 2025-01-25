#include <stdio.h>

void load_players();
typedef struct {
    char username[100];
    char email[100];
    char password[100];
    int score;
    int gold;
    int experience;
    int finished_games;
} player;

player players[300];
int player_count;

int main()
{
    load_players();
    printf("%d", player_count);
}

void load_players()
{
    FILE *file = fopen("players.csv", "r");
    char line[300];
    fgets(line, 300, file);
    player_count = 0;
    while (fgets(line, 300, file))
    {
        for (int i = 0; i < 300; i++)
            if (line[i] == ',')
                line[i] = ' ';
        sscanf(line, "%s %s %s %d %d %d %d",
        players[player_count].username,
        players[player_count].email,
        players[player_count].password,
        &players[player_count].score,
        &players[player_count].gold,
        &players[player_count].experience,
        &players[player_count].finished_games);
        player_count++;
    }
}