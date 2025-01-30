#ifndef MENUS_H
#define MENUS_H

#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <locale.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

int signup();
int login();
void sort();
int game_menu();
void draw_menu();
void signup_border();
void login_border();
int score_table();
int setting();
void setting_border();
int profile();
void save_new_user(char *username, char *email, char *password);
void load_players();
int check_username(char *username);
int check_password(char *password);
int check_email(char *email);
void error(const char *error_content);
void start_menu();
int init_audio();
void close_audio();
int check_for_login(char *username, char *password);
int welcome(char *username);
void save_changes();

typedef struct {
    char username[100];
    char email[100];
    char password[100];
    int score;
    int gold;
    int experience;
    int finished_games;
    int last_game_exists;
    int last_game_last_level;
} player;

typedef struct {
    int difficulty;
    int color;
    int music;
} player_setting;

player_setting PlayerSetting;

char current_user[100];
player players[300];
int player_count;

int has_returned = 0;


void start_menu()
{
    start_color();
    load_players();
    signup();
}

int game_menu()
{

    int saved_game_exists = 1;

    // for (int i = 0; i < player_count; i++)
    // {
    //     if (strcmp(players[i].username, current_user) == 0)
    //     {
    //         saved_game_exists = players[i].last_game_exists;
    //     }
    // }

    if (has_returned)
    {
        if (!init_audio()) 
        {
            printf("Failed to initialize audio!\n");
        }
        Mix_Music *menu_music = Mix_LoadMUS("musics/menu_music.mp3");
        Mix_PlayMusic(menu_music, -1);
    }

    
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    char prints[5][100] = {"NEW GAME", "SAVED GAME", "SCORE TABLE", "SETTING", "PROFILE"};
    int current = 0;
    while (1)
    {
        clear();
        curs_set(0);
        draw_menu();
        for (int i = 0; i < 5 ;i++)
        {
            if (i == current)
            {
                attron(COLOR_PAIR(1));
            }
            mvprintw(i + 12, 80, "%s", prints[i]);
            attroff(COLOR_PAIR(1));
        }
        refresh();
        
        int c = getch();
        switch (c)
        {
            case KEY_UP: 
                current = (current - 1 >= 0) ? (current - 1) : 4;
                break;
            case KEY_DOWN: 
                current = (current + 1 <= 4) ? (current + 1) : 0;
                break;
            case '\n':
                switch (current)
                {
                    case 0:
                        return 1;
                    case 1:
                        if (saved_game_exists) return 0;
                        break;
                    case 2:
                        clear();
                        return score_table();
                    case 3:
                        clear();
                        return setting();
                    case 4:
                        clear();
                        return profile();
                }
        }

    } 
}

int profile()
{
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    load_players();
    char email[100];
    char password[100];
    for (int i = 0; i < player_count; i++)
    {
        if (strcmp(players[i].username, current_user) == 0)
        {
            strcpy(email, players[i].email);
            strcpy(password, players[i].password);
            break;
        }
    }
    
    int current = 0;
    refresh();
    while (1)
    {
        clear();

        mvprintw(12, 70, "USERNAME");
        mvprintw(13, 70, "EMAIL");
        mvprintw(14, 70, "PASSWORD");
        //profile_border(); --> fit all in one border!
        if (current == 0)
            attron(COLOR_PAIR(1));
        mvprintw(12, 85, "%s", current_user);
        attroff(COLOR_PAIR(1));
        if (current == 1)
            attron(COLOR_PAIR(1));
        mvprintw(13, 85, "%s", email);
        attroff(COLOR_PAIR(1));
        if (current == 2)
            attron(COLOR_PAIR(1));
        mvprintw(14, 85, "%s", password);
        attroff(COLOR_PAIR(1));
        if (current == 3)
            attron(COLOR_PAIR(1));
        mvprintw(16, 80, "SAVE");
        attroff(COLOR_PAIR(1));
        refresh();
        int c = getch();
        switch (c)
        {
            case KEY_DOWN:
                current = (current + 1 <= 3) ? current + 1 : 0;
                break;
            case KEY_UP:
                current = (current - 1 >= 0) ? current - 1 : 3;
                break;
            case '\n':
                switch (current)
                {
                    case 0:
                        curs_set(1);
                        echo();
                        for (int i = 0; i < 100; i++)
                        {
                            mvaddch(12, 85 + i, ' ');
                        }
                        move(12, 85);
                        char new_username[100];
                        scanw("%s", new_username);
                        curs_set(0);
                        noecho();
                        //if (check_username(new_username))
                            strcpy(current_user, new_username);
                        //else
                        break;
                    case 1:
                        curs_set(1);
                        echo();
                        for (int i = 0; i < 100; i++)
                        {
                            mvaddch(13, 85 + i, ' ');
                        }
                        move(13, 85);
                        char new_email[100];
                        scanw("%s", new_email);
                        curs_set(0);
                        noecho();
                        //if (check_email(new_email))
                            strcpy(email, new_email);
                        //else
                        break;
                    case 2:
                        curs_set(1);
                        echo();
                        for (int i = 0; i < 100; i++)
                        {
                            mvaddch(14, 85 + i, ' ');
                        }
                        move(14, 85);
                        char new_password[100];
                        scanw("%s", new_password);
                        curs_set(0);
                        noecho();
                        //if (check_password(new_password))
                            strcpy(password, new_password);
                        //else
                        break;
                    case 3:
                        //save changes
                        has_returned = 0;
                        return game_menu();
                }
        }
    }
}

int setting()
{
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    Mix_Music *menu_music = Mix_LoadMUS("musics/menu_music.mp3");
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
            Mix_PlayMusic(menu_music, -1);
        }
        setting_border();
        mvprintw(10, 70, "DIFFICULTY");
        mvprintw(11, 70, "COLOR");
        mvprintw(12, 70, "SONG");
        refresh();
        if (current == 0)
        {
            attron(COLOR_PAIR(1));
        }
        for (int i = 0; i < 3; i++)
        {
            if (difficulty_index == i)
            {
                mvprintw(10, 90, "%s", difficulty[i]);
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
                mvprintw(11, 90, "%s", color[i]);
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
                mvprintw(12, 90, "%s", music[i]);
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
                if (music_ever_changed) has_returned = 1;
                return game_menu();
        }
    }
}

int score_table()
{
    load_players();
    sort();

    mvprintw(10, 50, "username");
    mvprintw(10, 60, "score");
    mvprintw(10, 70, "gold");
    mvprintw(10, 100, "finished games");
    for (int i = 0; i < player_count; i++)
    {
        mvprintw(11 + i, 50, "%s", players[i].username);
        mvprintw(11 + i, 60, "%d", players[i].score);
        mvprintw(11 + i, 70, "%d", players[i].gold);
        mvprintw(11 + i, 100, "%d", players[i].finished_games);
    }
    mvprintw(20, 100, "PRESS ANY KEY TO BACK");
    int c = getch();
    has_returned = 0;
    return game_menu();
}   

int signup()
{
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    char prints[5][100] = {"", "USERNAME", "EMAIL", "PASSWORD", "SIGN UP"};
    char username[100] = "";
    char email[100] = "";
    char password[100] = "";
    int current = 1;
    while (1)
    {
        clear();
        curs_set(0);
        signup_border();
        if (current == 0)
        {
            attron(COLOR_PAIR(1));
        }
        mvprintw(10, 80, "LOGIN");
        attroff(COLOR_PAIR(1));
        for (int i = 1; i <= 4; i++)
        {
            if (i == current)
            {
                attron(COLOR_PAIR(1));
            }
            mvprintw(i + 11, 80, "%s", prints[i]);
            attroff(COLOR_PAIR(1));
        }
        refresh();
        
        int c = getch();
        switch (c)
        {
            case KEY_UP: 
                current = (current - 1 >= 0) ? (current - 1) : 4;
                break;
            case KEY_DOWN: 
                current = (current + 1 <= 4) ? (current + 1) : 0;
                break;
            case '\n':
                if (current == 0)
                {
                    attroff(COLOR_PAIR(1));
                    return login();
                }
                else if (current == 4)
                {
                    if (check_password(password)&& check_email(email) && check_username(username))
                    {
                        strcpy(current_user, username);
                        save_new_user(username, email, password);
                        attroff(COLOR_PAIR(1));
                        return welcome(username);
                    }
                }
                else
                {
                    move(current + 11, 90);
                    curs_set(1);
                    echo(); 
                    char input[100];
                    getstr(input);
                    noecho();  
                    if (current == 1)
                    {
                        if (check_username(input))
                            strcpy(username, input);

                    }
                    else if (current == 2)
                    {
                        if (check_email(input))
                            strcpy(email, input);
                    }
                    else if (current == 3)
                    {
                        if (check_password(input))
                            strcpy(password, input);
                    }   
                }
                break;
        }

    }
}

int login()
{
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    char prints[4][100] = {"", "USERNAME", "PASSWORD", "LOGIN"};
    char username[100] = "";
    char password[100] = "";
    int current = 1;
    while (1)
    {
        clear();
        curs_set(0);
        login_border();
        if (current == 0)
        {
            attron(COLOR_PAIR(1));
        }
        mvprintw(10, 80, "SIGN UP");
        attroff(COLOR_PAIR(1));
        for (int i = 1; i <= 3; i++)
        {
            if (i == current)
            {
                attron(COLOR_PAIR(1));
            }
            mvprintw(i + 11, 80, "%s", prints[i]);
            attroff(COLOR_PAIR(1));
        }
        refresh();
        
        int c = getch();
        switch (c)
        {
            case KEY_UP: 
                current = (current - 1 >= 0) ? (current - 1) : 3;
                break;
            case KEY_DOWN: 
                current = (current + 1 <= 3) ? (current + 1) : 0;
                break;
            case '\n':
                if (current == 0)
                {
                    return signup();
                }
                else if (current == 3)
                {
                    if (check_for_login(username, password))
                    {
                        strcpy(current_user, username);
                        return 1;
                    }
                }
                else
                {
                    move(current + 11, 90);
                    curs_set(1);
                    echo(); 
                    char input[100];
                    getstr(input);
                    noecho();  // you can change here!
                    if (current == 1)
                    {
                        strcpy(username, input);
                    }
                    else if (current == 2)
                    {
                        strcpy(password, input);
                    }
                }
                break;
        }

    }
}

void signup_border()
{
    for (int i = 65; i < 120; i++)
    {
        mvaddch(9, i, '#');
        mvaddch(16, i, '#');
    }
    return;
}

void login_border()
{
    for (int i = 65; i < 120; i++)
    {
        mvaddch(9, i, '#');
        mvaddch(15, i, '#');
    }
    return;
}

void draw_menu()
{
    for (int i = 78; i <= 92; i++)
    {
        mvaddch(11, i, '-');
        mvaddch(17, i, '-');
    }
    for (int i = 11; i <= 17; i++)
    {
        mvaddch(i, 78, '|');
        mvaddch(i, 92, '|');
    }
}

void sort()
{
    for (int i = 0; i < player_count; i++)
    {
        int j = i;
        while (j > 0 && players[j].score > players[j - 1].score)
        {
            player swap = players[j];
            players[j] = players[j - 1];
            players[j - 1] = swap;
            j--;
        }
    }
}

void setting_border()
{
    for (int i = 65; i <= 105; i++)
    {
        mvaddch(9, i, '-');
        mvaddch(13, i, '-');
    }
    for (int i = 9; i <= 13; i++)
    {
        mvaddch(i, 65, '|');
        mvaddch(i, 105, '|');
    }
}

void save_new_user(char *username, char *email ,char *password)
{
    FILE *file = fopen("players.csv", "a");
    char *line = (char *) malloc(1000);
    sprintf(line, "%s, %s, %s, %d, %d, %d, %d, %d,", username, email, password, 0, 0, 0, 0, 0);
    fprintf(file, "%s\n", line);
    fclose(file);
    free(line);
    return;
}

int check_username(char *username)
{
    if (strlen(username) == 0)
    {
        error("PLEASE ENTER USERNAME");
        return 0;
    }

    if (strlen(username) < 5)
    {
        error("TOO SHORT");
        return 0;
    }

    for (int i = 0; i < strlen(username); i++)
    {
        if (username[i] == ' ')
        {
            error("USERNAME CAN'T CONTAIN SPACES");
            return 0;
        }
    }

    for (int i = 0; i < player_count; i++)
    {
        if (strncasecmp(players[i].username, username, 100) == 0)
        {
            error("USERNAME EXISTS");
            return 0;
        }
    }

    return 1;
}

int check_email(char *email)
{
    int ad_flag = 0;
    int dot_flag = 0;
    int ad_index;
    int dot_index;
    if (strlen(email) == 0)
    {
        error("PLEASE ENTER YOUR EMAIL");
        return 0;
    }
    for (int i = 0; i < strlen(email); i++)
    {
        // some other restricitons
        if (email[i] == ' ')
        {
            error("INCORRECT FORMAT");
            return 0;
        }
        else if (email[i] == '@')
        {
            ad_flag++;
            ad_index = i;
        }
        else if(email[i] == '.')
        {
            dot_flag++;
            dot_index = i;
        }
    }

    if (dot_flag != 1 || ad_flag != 1 || ad_index > dot_index)
    {
        error("INCORRECT FORMAT");
        return 0;
    }

    for (int i = 0; i < player_count; i++)
    {
        if (strncasecmp(players[i].email, email, 100) == 0)
        {
            error("YOU HAVE AN ACCOUNT WITH THIS EMAIL");
            return 0;
        }
    }

    if (dot_index == strlen(email) - 1 || ad_index == 0 || dot_index == ad_index + 1)
    {
        error("INCORRECT FORMAT");
        return 0;
    }
    return 1;
}

int check_password(char *password)
{

    if (strlen(password) == 0)
    {
        error("PLEASE ENTER PASSWORD");
        return 0;
    }

    else if (strlen(password) < 7)
    {
        error("TOO SHORT");
        return 0;
    }
    int digit = 0;
    int upper = 0;
    int lower = 0;
    for (int i = 0; i < strlen(password); i++)
    {
        if (isdigit(password[i]))
        {
            digit++;
        }
        else if (islower(password[i]))
        {
            lower++;
        }
        else if (isupper(password[i]))
        {
            upper++;
        }
    }

    if (lower == 0)
    {
        error("ENTER AT LEAST ONE LOWERCASE CHARACTER");
        return 0;
    }
    if (upper == 0)
    {
        error("ENTER AT LEAST ONE UPPERCASE CHARACTER");
        return 0;
    }
    if (digit == 0)
    {
        error("ENTER AT LEAST ONE DIGIT");
        return 0;
    }

    return 1;
}

int check_for_login(char *username, char *password)
{
    int found = 0;
    for (int i = 0; i < player_count; i++)
    {
        if (strcasecmp(username, players[i].username) == 0) 
        {
            found = 1;
            if (strcmp(password, players[i].password) == 0) 
            {
                return welcome(username);
            } 
        }
        else 
        {
            error("PASSWORD IS NOT CORRECT");
            return 0;
        }
    }
    if (!found)
    {
        error("USERNAME DOESN'T EXIST");
        return 0;
    }

}

int welcome(char *username)
{
    clear();
    init_pair(100, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(100));
    mvprintw(15, 83, "WELCOME %s", username);
    mvprintw(16, 83, "GETTING READY...");
    for (int i = 0; i < 7; i++)
    {
        mvprintw(17, 86 + i, "▌");
        refresh();
        napms(1000);
    }
    attroff(COLOR_PAIR(100));
    flushinp();
    return 1;
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
        sscanf(line, "%s %s %s %d %d %d %d %d",
        players[player_count].username,
        players[player_count].email,
        players[player_count].password,
        &players[player_count].score,
        &players[player_count].gold,
        &players[player_count].finished_games,
        &players[player_count].last_game_exists,
        &players[player_count].last_game_last_level);
        player_count++;
    }
}

void error(const char *error_content) // must be changed
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    int win_height = 5, win_width = 50;
    int start_y = (rows - win_height) / 2;
    int start_x = (cols - win_width) / 2;

    WINDOW *error_win = newwin(win_height, win_width, start_y, start_x);
    box(error_win, 0, 0);

    mvwprintw(error_win, 2, (win_width - strlen(error_content)) / 2, "%s", error_content);
    mvwprintw(error_win, 4, (win_width - 22) / 2, "Press ESC to continue");

    wrefresh(error_win);

    int ch = getch();

    if (ch == 27)
        delwin(error_win);
}

int init_audio() 
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return 0;
    }
    return 1;
}

void close_audio() 
{
    Mix_CloseAudio();
    SDL_Quit();
}

void save_changes()
{
    FILE *file = fopen("players.csv", "w");
    fprintf(file, "username, email, password, score, gold, finished games, last_game_exists, last_game_last_level,\n");
    char *line = (char *) malloc(1000);
    for (int i = 0; i < player_count; i++)
    {
        sprintf(line, "%s, %s, %s, %d, %d, %d, %d, %d,", players[i].username, players[i].email, players[i].password, players[i].score, players[i].gold, players[i].finished_games, players[i].last_game_exists, players[i].last_game_last_level);
        fprintf(file, "%s\n", line);
    }
    fclose(file);
    free(line);
    return; 
}

#endif 