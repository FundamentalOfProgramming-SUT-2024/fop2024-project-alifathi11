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
#include "map.h"


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
    cbreak();         
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

    int saved_game_exists = 0;
    for (int i = 0; i < player_count; i++)
    {
        if (strcmp(players[i].username, current_user) == 0)
        {
            saved_game_exists = players[i].last_game_exists;
        }
    }

    if (game_menu())
    {
        clear();
        Mix_FreeMusic(menu_music);
        close_audio();
        if (preparing(1, 1, 1) == 0) 
        {
            endwin();  
        }
        else if (preparing(1, 1, 1) == 1)
        {
            //victory();
            endwin();  
        }
        else if (preparing(1, 1, 1) == 2)
        {

            //saving_screen();
            endwin();  
        }
    }
    // else if (saved_game_exists == 1)
    // {
    //     // if (saved_game() == 0)
    //     // {
    //     //     endwin();
    //     // }
    //     // else if (saved_game() == 1)
    //     // {
    //     //     //vicroty();
    //     // }
    //     // else if (saved_game() == 2)
    //     // {
    //     //     //saving_screen
    //     // }
    // }

    //save_changes();
    endwin();
    return 1;
}