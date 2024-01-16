#ifndef GLOBALS_H
#define GLOBALS_H


typedef struct Vector2i {
    int x, y;
} Vector2i;

typedef struct Vector2f {
    float x, y;
} Vector2f;

typedef struct Rect {
    int x, y, w, h;
} Rect;

typedef struct FloatRect {
    float x, y, w, h;
} FloatRect;

typedef enum Color {
    Color_Escape,
    Color_Black,
    Color_DarkGray,
    Color_BlackUnderline,
    Color_BlackBlink,
    Color_Blue,
    Color_LightBlue,
    Color_BlueUnderline,
    Color_BlueBlink,
    Color_Green,
    Color_LightGreen,
    Color_GreenUnderline,
    Color_GreenBlink,
    Color_Cyan,
    Color_LightCyan,
    Color_CyanUnderline,
    Color_CyanBlink,
    Color_Red,
    Color_LightRed,
    Color_RedUnderline,
    Color_RedBlink,
    Color_Purple,
    Color_LightPurple,
    Color_PurpleUnderline,
    Color_PurpleBlink,
    Color_Brown,
    Color_Yellow,
    Color_YellowUnderline,
    Color_YellowBlink,
    Color_LightGray,
    Color_White,
    Color_GrayUnderline,
    Color_GrayBlink,
} Color;

const char *ANSI_Colors[] = {
    "\033[0m",
    "\033[0;30m",
    "\033[1;30m",
    "\033[4;30m",
    "\033[5;30m",
    "\033[0;34m",
    "\033[1;34m",
    "\033[4;34m",
    "\033[5;34m",
    "\033[0;32m",
    "\033[1;32m",
    "\033[4;32m",
    "\033[5;32m",
    "\033[0;36m",
    "\033[1;36m",
    "\033[4;36m",
    "\033[5;36m",
    "\033[0;31m",
    "\033[1;31m",
    "\033[4;31m",
    "\033[5;31m",
    "\033[0;35m",
    "\033[1;35m",
    "\033[4;35m",
    "\033[5;35m",
    "\033[0;33m",
    "\033[1;33m",
    "\033[4;33m",
    "\033[5;33m",
    "\033[0;37m",
    "\033[1;37m",
    "\033[4;37m",
    "\033[5;37m",
};

#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "basics/boxchar/boxchar.h"

typedef struct Globals {
    
} Globals;

#define outOfBounds(renderer, x, y) ((x) < 0 || (x) >= renderer->width || (y) < 0 || (y) >= renderer->height)

bool outOfTermBounds(int x, int y) {
    int termWidth, termHeight;
    bc_termsize(&termWidth, &termHeight);
    return (x < 0 || y < 0 || x >= termWidth || y >= termHeight);
}

#endif // GLOBALS_H