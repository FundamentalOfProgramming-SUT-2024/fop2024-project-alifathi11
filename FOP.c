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

    if (game_menu())
    {
        clear();
        Mix_FreeMusic(menu_music);
        close_audio();
        new_game();   
    }
    else 
    {
        //saved_game();
    }

    endwin();
}

