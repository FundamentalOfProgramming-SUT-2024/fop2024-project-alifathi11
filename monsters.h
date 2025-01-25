#ifndef MONSTERS_H
#define MONSTERS_H

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
        if (visible_map[y][x] == 1)
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

#endif