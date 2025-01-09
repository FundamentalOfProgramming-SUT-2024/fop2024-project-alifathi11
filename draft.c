#include <stdio.h>
#include <string.h>

typedef struct {
    char username[100];
    char email[100];
    char password[100];
    int score;
    int gold;
    int experience;
    int finished_games;
} player;


int main()
{
    player players[200];
    FILE *file = fopen("players.csv", "r");
    char line[300];
    fgets(line, 300, file);
    int count = 0;
    while (fgets(line, 300, file))
    {
        for (int i = 0; i < 300; i++)
            if (line[i] == ',')
                line[i] = ' ';
        sscanf(line, "%s %s %s %d %d %d %d",
        players[count].username,
        players[count].email,
        players[count].password,
        &players[count].score,
        &players[count].gold,
        &players[count].experience,
        &players[count].finished_games);
        count++;
    }

    for (int i = 0; i < count; i++)
    {
        printf("%s\n", players[i].username);
        printf("%d\n", players[i].score);
        printf("%d\n", players[i].gold);
        printf("%d\n", players[i].experience);
        printf("%d\n", players[i].finished_games);
    }
}