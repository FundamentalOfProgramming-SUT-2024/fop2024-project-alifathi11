#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

int signup();
int login();
void signup_border();
void login_border();
int log_sign(int (*fptr[2])(), int i);

int main() 
{
    initscr();             
    keypad(stdscr, TRUE);    
    noecho();                
    curs_set(0); 
    int (*fptr[2])() = {&signup, &login};
    if (log_sign(fptr, 0))
        clear();
    game_menu();
    
    endwin();

}


void game_menu()
{
    char prints[5][100] = {"NEW GAME", "SAVED GAME", "SCORE TABLE", "SETTING", "PROFILE"};
    char username[100];
    char email[100];
    char password[100];
    int current = 1;
    while (1)
    {
        clear();
        curs_set(0);
        signup_border();
        if (current == 0)
        {
            attron(A_STANDOUT);
        }
        mvprintw(10, 80, "LOGIN");
        attroff(A_STANDOUT);
        for (int i = 1; i <= 4; i++)
        {
            if (i == current)
            {
                attron(A_STANDOUT);
            }
            mvprintw(i + 11, 80, "%s", prints[i]);
            attroff(A_STANDOUT);
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
                    return 0;
                }
                else if (current == 4)
                {
                    if (strlen(username) > 0 && strlen(email) > 0 && strlen(password) > 0)
                    {
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
                        //if (check_username(input))
                            strcpy(username, input);
                        // else
                    }
                    else if (current == 2)
                    {
                        // if (check_email(input))
                            strcpy(email, input);
                        // else
                    }
                    else if (current == 3)
                    {
                        // if (check_pass(input))
                            strcpy(password, input);
                        // else
                    }   
                }
                break;
        }

    } 
}


int signup()
{
    char prints[5][100] = {"", "USERNAME", "EMAIL", "PASSWORD", "SIGN UP"};
    char username[100];
    char email[100];
    char password[100];
    int current = 1;
    while (1)
    {
        clear();
        curs_set(0);
        signup_border();
        if (current == 0)
        {
            attron(A_STANDOUT);
        }
        mvprintw(10, 80, "LOGIN");
        attroff(A_STANDOUT);
        for (int i = 1; i <= 4; i++)
        {
            if (i == current)
            {
                attron(A_STANDOUT);
            }
            mvprintw(i + 11, 80, "%s", prints[i]);
            attroff(A_STANDOUT);
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
                    return 0;
                }
                else if (current == 4)
                {
                    if (strlen(username) > 0 && strlen(email) > 0 && strlen(password) > 0)
                    {
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
                        //if (check_username(input))
                            strcpy(username, input);
                        // else
                    }
                    else if (current == 2)
                    {
                        // if (check_email(input))
                            strcpy(email, input);
                        // else
                    }
                    else if (current == 3)
                    {
                        // if (check_pass(input))
                            strcpy(password, input);
                        // else
                    }   
                }
                break;
        }

    }
}

int login()
{
    char prints[4][100] = {"", "USERNAME", "PASSWORD", "LOGIN"};
    char username[100];
    char password[100];
    int current = 1;
    while (1)
    {
        clear();
        curs_set(0);
        login_border();
        if (current == 0)
        {
            attron(A_STANDOUT);
        }
        mvprintw(10, 80, "SIGN UP");
        attroff(A_STANDOUT);
        for (int i = 1; i <= 3; i++)
        {
            if (i == current)
            {
                attron(A_STANDOUT);
            }
            mvprintw(i + 11, 80, "%s", prints[i]);
            attroff(A_STANDOUT);
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
                    return 0;
                }
                else if (current == 3)
                {
                    if (strlen(username) > 0 && strlen(password) > 0)
                    {
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
                        //if (check_username(input))
                            strcpy(username, input);
                        // else
                    }
                    else if (current == 2)
                    {
                        // if (check_email(input))
                            strcpy(password, input);
                        // else
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

int log_sign(int (*fptr[2])(), int i)
{
    int reslut = (*fptr[i])();
    if (reslut == 0)
    {
        log_sign(fptr, (i + 1) % 2);
    }
    else
    {
        return 1;
    }
}
