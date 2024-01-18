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
#else
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#endif

#include "basics/Renderer.h"

#define RENDER_WIDTH    19
#define RENDER_HEIGHT   16

#define ROAD_WIDTH      5
#define ROAD_LENGTH     RENDER_HEIGHT

typedef struct Globals {
    Renderer    *renderer;
} Globals;

#define outOfBounds(renderer, x, y) ((x) < 0 || (x) >= renderer->width || (y) < 0 || (y) >= renderer->height)

int random(int l, int r) {
    return rand() % (r - l + 1) + l;
}

int keyboardHit() {
    #ifdef _WIN32
        return kbhit();
    #else
        struct termios term;
        tcgetattr(0, &term);

        struct termios term2 = term;
        term2.c_lflag &= ~ICANON;
        tcsetattr(0, TCSANOW, &term2);

        int byteswaiting;
        ioctl(0, FIONREAD, &byteswaiting);

        tcsetattr(0, TCSANOW, &term);

        return byteswaiting > 0;
    #endif
}

int termGetch() {
    #ifdef _WIN32
        return getch();
    #else
        struct termios oldt, newt;
        int ch;
        int flags;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        
        flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

        ch = getchar();
        
        fcntl(STDIN_FILENO, F_SETFL, flags);
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        
        return ch;
    #endif
}

void initConsole() {
    setlocale(LC_ALL, "en_US.UTF-8");
    printf("\033[?25l\033[H\033[J");
}

void endConsole() {
    printf("\033[?25h\033[H\033[J");
}

#endif // GLOBALS