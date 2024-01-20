#ifndef GLOBALS
#define GLOBALS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>
#include <stdint.h>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ENTER 13

#define VERSION L"v1.14.514 (Windows x64 Build)"
#else
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define LEFT 68
#define RIGHT 67
#define UP 65
#define DOWN 66
#define ENTER 10

static struct termios initial_settings, new_settings;
static int peek_character = -1;

#define VERSION L"v1.14.514 (Linux x64 Build)"
#endif

#include "basics/Renderer.h"
#include "ScoreBoard.h"

#define TITLE L" Console Runners! "
#define COPYRIGHT L" Copyright @ 2024 Kingcq "

#define RENDER_WIDTH    31
#define RENDER_HEIGHT   24

#define BORDER_WIDTH    31
#define BORDER_HEIGHT   24

#define ROAD_WIDTH      5
#define ROAD_LENGTH     16
#define GAME_OFFSETX    6
#define GAME_OFFSETY    6

#define QUIT 113

typedef struct Globals {
    Renderer    *renderer;
    ScoreBoard  *scoreBoard;
} Globals;

#define outOfBounds(renderer, x, y) ((x) < 0 || (x) >= renderer->width || (y) < 0 || (y) >= renderer->height)

int randInt(int l, int r) {
    if (RAND_MAX <= 0x7fff) {
        return rand() * rand() % (r - l + 1) + l;
    }
    return rand() % (r - l + 1) + l;
}

int keyboardHit() {
    #ifdef _WIN32
        return kbhit();
    #else
        char ch;
        int nread;
        if(peek_character != -1) {
            return 1;
        }
        new_settings.c_cc[VMIN]=0;
        tcsetattr(0, TCSANOW, &new_settings);
        nread = read(0,&ch,1);
        new_settings.c_cc[VMIN]=1;
        tcsetattr(0, TCSANOW, &new_settings);
        if(nread == 1) {
            peek_character = ch;
            return 1;
        }
        return 0;
    #endif
}

int termGetch() {
    #ifdef _WIN32
        return getch();
    #else
        char ch;
        if(peek_character != -1) {
            ch = peek_character;
            peek_character = -1;
            return ch;
        }
        read(0,&ch,1);
        return ch;
    #endif
}

void initConsole() {
    #ifndef _WIN32
        // init keyboard
        tcgetattr(0,&initial_settings);
        new_settings = initial_settings;
        new_settings.c_lflag &= ~ICANON;
        new_settings.c_lflag &= ~ECHO;
        new_settings.c_lflag &= ~ISIG;
        new_settings.c_cc[VMIN] = 1;
        new_settings.c_cc[VTIME] = 0;
        tcsetattr(0, TCSANOW, &new_settings);
    #endif
    setlocale(LC_ALL, "en_US.UTF-8");
    wprintf(L"\033[?25l\033[1;1H\033[2J");
}

void endConsole() {
    #ifndef _WIN32
        // close keyboard
        tcsetattr(0, TCSANOW, &initial_settings);
    #endif
    setlocale(LC_ALL, "");
    wprintf(L"\033[?25h\033[1;1H\033[2J");
}

#endif // GLOBALS