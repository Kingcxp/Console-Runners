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

#define ARROW_LEFT 75
#define ARROW_RIGHT 77
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ENTER 13
#else
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define ARROW_LEFT 68
#define ARROW_RIGHT 67
#define ARROW_UP 65
#define ARROW_DOWN 66
#define ENTER 10

static struct termios initial_settings, new_settings;
static int peek_character = -1;
#endif

#include "basics/Renderer.h"
#include "ScoreBoard.h"

#define TITLE L" Console Runners! "
#define AUTHOR L"By Kingcq"
#define VERSION L"v1.14.514"
#define COPYRIGHT L" Copyright @ 2024 Kingcq "

#define RENDER_WIDTH    31
#define RENDER_HEIGHT   23

#define ROAD_WIDTH      5
#define ROAD_LENGTH     16
#define GAME_OFFSETX    6
#define GAME_OFFSETY    5

typedef struct Globals {
    Renderer    *renderer;
    ScoreBoard  *scoreBoard;
} Globals;

#define outOfBounds(renderer, x, y) ((x) < 0 || (x) >= renderer->width || (y) < 0 || (y) >= renderer->height)

int randInt(int l, int r) {
    return rand() * rand() % (r - l + 1) + l;
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
    printf("\033[?25l\033[H\033[J");
}

void endConsole() {
    #ifndef _WIN32
        // close keyboard
        tcsetattr(0, TCSANOW, &initial_settings);
    #endif
    printf("\033[?25h\033[H\033[J");
}

#endif // GLOBALS