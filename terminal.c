#include <stdio.h>
#include "terminal.h"

#ifdef _WIN32

#include <conio.h>
#include <windows.h>

void terminal_init(void)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    DWORD mode;

    if (GetConsoleMode(h, &mode))
    {
        mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(h, mode);
    }
}

void terminal_restore(void)
{
}

int terminal_getch(void)
{
    return _getch();
}

void terminal_clear(void)
{
    printf("\033[H\033[J");
}

#else

#include <termios.h>
#include <unistd.h>

static struct termios old_terminal;

void terminal_init(void)
{
    tcgetattr(STDIN_FILENO, &old_terminal);

    struct termios raw = old_terminal;
    raw.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void terminal_restore(void)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_terminal);
}

int terminal_getch(void)
{
    return getchar();
}

void terminal_clear(void)
{
    printf("\033[H\033[J");
}

#endif